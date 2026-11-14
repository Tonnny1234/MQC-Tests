#!/usr/bin/env python3
"""Test suite.   python3 tests/run_tests.py [-v]

Part 1  engine against an independent Python reference and brute force (always runs)
Part 2  engine against the real ASTRAL-III and ASTRAL-IV programs (skipped if they are not installed)
Part 3  the whole pipeline: task lists -> runs -> report
"""
import json
import os
import random
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ref
from common import MQC, astral3_jar, astral4_bin, clean_env, java

TEST_DATA = os.path.join(ROOT, "ext", "ASTRAL", "Astral", "test_data")


def sh(cmd, check=True, env=None):
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, cwd=ROOT, env=env)
    if check and p.returncode != 0:
        raise AssertionError("command failed: %s\n%s" % (" ".join(cmd), p.stderr[-2000:]))
    return p


def mqc(*args, **kw):
    return sh([MQC] + [str(a) for a in args], **kw)


def have_java():
    try:
        return os.path.exists(astral3_jar()) and subprocess.run([java(), "-version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=clean_env()).returncode == 0
    except OSError:
        return False


class Small(object):
    """A small random instance with every reference quantity precomputed."""

    def __init__(self, n, k, seed, tmp):
        rng = random.Random(seed)
        self.taxa = ["Sp_%02d-x" % i for i in range(n)]
        self.genes = os.path.join(tmp, "genes_n%d_s%d.tre" % (n, seed))
        lines = ref.make_gene_trees(self.taxa, k, rng)
        with open(self.genes, "w") as f:
            f.write("\n".join(lines) + "\n")
        self.W = ref.weights(lines, self.taxa)
        self.trees = ref.all_trees(self.taxa)
        self.scores = [ref.score(self.W, t) for t in self.trees]
        self.opt = max(self.scores)
        self.total = sum(sum(w) for w in self.W.values())


class EngineTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.mkdtemp(prefix="mqc_test_")
        cls.inst = [Small(6, 12, 1, cls.tmp), Small(7, 15, 2, cls.tmp), Small(7, 4, 3, cls.tmp)]

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def test_01_selftest(self):
        out = mqc("selftest", "--trials", 80).stdout
        self.assertIn(" 0 failures", out)

    def test_02_scorer_matches_reference(self):
        """mqc score == reference score for every tree on 6 taxa and a sample on 7 (messy Newick, missing taxa, polytomies)."""
        for I in self.inst:
            idx = list(range(len(I.trees))) if len(I.trees) <= 105 else random.Random(5).sample(range(len(I.trees)), 150)
            path = os.path.join(self.tmp, "trees.tre")
            with open(path, "w") as f:
                f.write("\n".join(ref.newick_of(I.trees[i]) for i in idx) + "\n")
            got = [l.split() for l in mqc("score", "--genes", I.genes, "--trees", path).stdout.strip().splitlines()]
            self.assertEqual([int(g[0]) for g in got], [I.scores[i] for i in idx])
            self.assertEqual(int(got[0][1]), I.total)

    def test_03_dp_is_optimal_for_every_order(self):
        """For every circular order: DP value == best reference score among compatible trees, and its tree is one of them."""
        for I in self.inst:
            orders = ref.all_orders(I.taxa)
            path = os.path.join(self.tmp, "orders.txt")
            with open(path, "w") as f:
                f.write("\n".join(" ".join(o) for o in orders) + "\n")
            lines = mqc("eval", "--genes", I.genes, "--orders", path).stdout.strip().splitlines()
            self.assertEqual(len(lines), len(orders))
            best_over_orders = 0
            for o, line in zip(orders, lines):
                val, nw = line.split("\t")
                want = max(s for t, s in zip(I.trees, I.scores) if ref.compatible(t, o))
                self.assertEqual(int(val), want, "order %s" % (o,))
                tree = ref.parse(nw)
                self.assertTrue(ref.compatible(tree, o))
                self.assertEqual(ref.score(I.W, tree), want)
                best_over_orders = max(best_over_orders, int(val))
            self.assertEqual(best_over_orders, I.opt, "best order must give the global optimum")

    def test_04_every_strategy_and_start(self):
        """Each strategy x start runs, reports a score no larger than the true optimum, and its tree really has that score."""
        I = self.inst[1]
        strategies = ["dp", "reorient", "pairswap-first", "pairswap-best", "vnd", "anneal", "ils", "tabu", "multistart"]
        starts = ["random", "genetree", "distance", "caterpillar", "greedy", "bestrandom"]
        reached = 0
        for i, st in enumerate(strategies):
            for j, start in enumerate(starts):
                if (i + j) % 2 and st not in ("dp", "vnd"):
                    continue                                  # half of the grid keeps the test quick
                out = os.path.join(self.tmp, "run_%s_%s" % (st, start))
                mqc("search", "--genes", I.genes, "--strategy", st, "--start", start, "--seed", 3, "--time", 1, "--out", out)
                with open(out + ".json") as f:
                    j_ = json.load(f)
                self.assertTrue(j_["finished"])
                self.assertLessEqual(j_["score"], I.opt)
                self.assertGreaterEqual(j_["score"], j_["start_score"])
                self.assertEqual(ref.score(I.W, ref.parse(open(out + ".tre").read())), j_["score"])
                if start == "caterpillar":
                    self.assertGreaterEqual(3 * j_["start_score"], I.total)
                if st != "dp":
                    reached += j_["score"] == I.opt
        self.assertGreater(reached, 10, "searches should usually find the optimum of a 7-taxon instance")

    def test_05_warm_start_never_below_tree(self):
        I = self.inst[0]
        rng = random.Random(9)
        for _ in range(5):
            i = rng.randrange(len(I.trees))
            tpath, out = os.path.join(self.tmp, "start.tre"), os.path.join(self.tmp, "warm%d" % i)
            with open(tpath, "w") as f:
                f.write(ref.newick_of(I.trees[i]) + "\n")
            mqc("search", "--genes", I.genes, "--strategy", "dp", "--start", "tree", "--start-tree", tpath, "--seed", i, "--out", out)
            self.assertGreaterEqual(json.load(open(out + ".json"))["score"], I.scores[i])

    def test_06_checkpoint_and_resume(self):
        I = self.inst[1]
        out = os.path.join(self.tmp, "resume")
        cmd = ["search", "--genes", I.genes, "--strategy", "tabu", "--start", "random", "--seed", 1, "--time", 3, "--max-run", 1, "--out", out]
        mqc(*cmd)
        first = json.load(open(out + ".json"))
        self.assertFalse(first["finished"])
        self.assertTrue(os.path.exists(out + ".ckpt"))
        for _ in range(6):
            mqc(*cmd)
            last = json.load(open(out + ".json"))
            if last["finished"]:
                break
        self.assertTrue(last["finished"])
        self.assertGreaterEqual(last["resumes"], 1)
        self.assertGreaterEqual(last["score"], first["score"])
        self.assertFalse(os.path.exists(out + ".ckpt"))
        self.assertIn("already finished", mqc(*cmd).stderr)

    def test_07_table_cache_subsample_rf(self):
        I = self.inst[1]
        tab = os.path.join(self.tmp, "t.bin")
        mqc("table", "--genes", I.genes, "--out", tab)
        tpath = os.path.join(self.tmp, "one.tre")
        with open(tpath, "w") as f:
            f.write(ref.newick_of(I.trees[0]) + "\n" + ref.newick_of(I.trees[40]) + "\n")
        a = mqc("score", "--genes", I.genes, "--trees", tpath).stdout
        b = mqc("score", "--genes", I.genes, "--trees", tpath, "--table", tab).stdout
        self.assertEqual(a, b)
        sub = os.path.join(self.tmp, "sub.tre")
        mqc("subsample", "--genes", I.genes, "--ntaxa", 5, "--seed", 4, "--out", sub)
        self.assertEqual(json.loads(mqc("info", "--genes", sub).stdout)["n"], 5)
        t1, t2 = os.path.join(self.tmp, "a.tre"), os.path.join(self.tmp, "b.tre")
        open(t1, "w").write(ref.newick_of(I.trees[0]) + "\n")
        open(t2, "w").write(ref.newick_of(I.trees[40]) + "\n")
        self.assertEqual(mqc("rf", "--genes", I.genes, "--tree1", t1, "--tree2", t1).stdout.split()[0], "0")
        self.assertGreater(int(mqc("rf", "--genes", I.genes, "--tree1", t1, "--tree2", t2).stdout.split()[0]), 0)


@unittest.skipUnless(have_java() and os.path.isdir(TEST_DATA), "ASTRAL-III or Java not available (run setup.sh)")
class AstralTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.mkdtemp(prefix="mqc_astral_")

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def astral(self, genes, out, *extra):
        import re
        p = sh([java(), "-jar", astral3_jar(), "-i", genes, "-o", out, "-t", "0"] + list(extra), env=clean_env())
        return int(re.findall(r"Final quartet score is:\s*(\d+)", p.stderr)[-1])

    def ours(self, genes, tree):
        return int(mqc("score", "--genes", genes, "--trees", tree).stdout.split()[0])

    def check_dataset(self, name):
        genes = os.path.join(TEST_DATA, name)
        d, x = os.path.join(self.tmp, name + ".default.tre"), os.path.join(self.tmp, name + ".exact.tre")
        s_default, s_exact = self.astral(genes, d), self.astral(genes, x, "-x")
        self.assertEqual(self.ours(genes, d), s_default, "our scorer must agree with ASTRAL's printed score")
        self.assertEqual(self.ours(genes, x), s_exact)
        best = 0
        for seed in (1, 2, 3):
            out = os.path.join(self.tmp, "%s.cold%d" % (name, seed))
            mqc("search", "--genes", genes, "--strategy", "vnd", "--start", "random", "--seed", seed, "--time", 30, "--out", out)
            sc = json.load(open(out + ".json"))["score"]
            self.assertLessEqual(sc, s_exact, "nothing may score above the exact optimum")
            best = max(best, sc)
        self.assertEqual(best, s_exact, "cold search should reach the exact optimum on 14 taxa")
        out = os.path.join(self.tmp, name + ".warm")
        mqc("search", "--genes", genes, "--strategy", "dp", "--start", "tree", "--start-tree", d, "--out", out)
        self.assertGreaterEqual(json.load(open(out + ".json"))["score"], s_default, "DP from ASTRAL's tree can never lose")
        q = os.path.join(self.tmp, name + ".q.tre")
        self.assertEqual(self.astral(genes, q, "-q", os.path.join(self.tmp, "%s.cold1.tre" % name)), json.load(open(os.path.join(self.tmp, "%s.cold1.json" % name)))["score"],
                         "ASTRAL -q must give our tree the score we report")
        return s_default, s_exact

    def test_10_simulated_14_taxa(self):
        s_default, s_exact = self.check_dataset("simulated_14taxon.gene.tre")
        self.assertEqual(s_exact, 4812)                       # the value in ASTRAL's own tutorial

    def test_11_primates(self):
        self.check_dataset("song_primates.424.gene.tre")

    def test_12_mammals_scores_agree(self):
        genes = os.path.join(TEST_DATA, "song_mammals.424.gene.tre")
        d = os.path.join(self.tmp, "mammals.tre")
        s = self.astral(genes, d)
        self.assertEqual(self.ours(genes, d), s)
        out = os.path.join(self.tmp, "mammals.warm")
        mqc("search", "--genes", genes, "--strategy", "reorient", "--start", "tree", "--start-tree", d, "--time", 20, "--out", out)
        self.assertGreaterEqual(json.load(open(out + ".json"))["score"], s)

    @unittest.skipUnless(os.path.exists(astral4_bin()), "ASTRAL-IV not built (run setup.sh)")
    def test_13_astral4_scores_agree(self):
        import re
        genes = os.path.join(TEST_DATA, "song_mammals.424.gene.tre")
        t = os.path.join(self.tmp, "a4.tre")
        p = sh([astral4_bin(), "-u", "0", "-o", t, genes])
        self.assertEqual(self.ours(genes, t), int(re.findall(r"^Score:\s*(\d+)", p.stderr + p.stdout, flags=re.M)[-1]))

    def test_14_control_astral_with_our_arcs(self):
        """ASTRAL-III given the arcs of our best order must reach at least our score."""
        genes = os.path.join(TEST_DATA, "simulated_14taxon.gene.tre")
        out = os.path.join(self.tmp, "ctl")
        mqc("search", "--genes", genes, "--strategy", "vnd", "--start", "greedy", "--seed", 1, "--time", 20, "--out", out)
        p = sh([sys.executable, "tools/astral_hybrid.py", "--result", out + ".json", "--out", os.path.join(self.tmp, "hyb")])
        r = json.loads(p.stdout)
        self.assertGreaterEqual(r["astral3_with_order_arcs"], r["our_search_score"])
        self.assertEqual(r["astral3_with_order_arcs"], r["rescored_by_mqc"])


@unittest.skipUnless(have_java() and os.path.exists(astral4_bin()) and os.path.isdir(TEST_DATA), "needs ASTRAL-III and ASTRAL-IV (run setup.sh)")
class PipelineTests(unittest.TestCase):
    def test_20_config_to_report(self):
        cfg = {"name": "unittest", "exact_max_taxa": 10, "exact_timeout": 300,
               "datasets": [{"name": "sim14", "genes": "ext/ASTRAL/Astral/test_data/simulated_14taxon.gene.tre"}],
               "subsets": {"from": ["sim14"], "sizes": [8], "replicates": 2},
               "baselines": [{"method": "astral3", "seeds": [1]}, {"method": "astral4", "seeds": [1]}],
               "search": {"strategies": ["dp", "vnd"], "warm": ["astral3"], "cold": ["random", "greedy"], "seeds": [1], "time": 5}}
        path = os.path.join(ROOT, "configs", "unittest.json")
        try:
            with open(path, "w") as f:
                json.dump(cfg, f)
            for d in ("results", "work"):
                shutil.rmtree(os.path.join(ROOT, d, "unittest"), ignore_errors=True)
            sh([sys.executable, "tools/make_tasks.py", "configs/unittest.json"])
            for phase in ("phase1", "phase2"):
                sh([sys.executable, "tools/run_local.py", "tasks/unittest.%s.txt" % phase, "-j", "2"])
            sh([sys.executable, "tools/run_local.py", "tasks/unittest.phase2.txt"])     # second pass: everything is skipped
            p = sh([sys.executable, "tools/report.py", "configs/unittest.json"])
            self.assertIn("sim14.n8.r1", p.stdout)
            self.assertIn("All scorers agree", p.stdout)
            for f in ("results.csv", "report.md", "report.html"):
                self.assertTrue(os.path.getsize(os.path.join(ROOT, "results", "unittest", f)) > 200)
        finally:
            for f in [path] + [os.path.join(ROOT, "tasks", "unittest.%s.txt" % ph) for ph in ("phase1", "phase2")]:
                if os.path.exists(f):
                    os.remove(f)
            for d in ("results", "work"):
                shutil.rmtree(os.path.join(ROOT, d, "unittest"), ignore_errors=True)


if __name__ == "__main__":
    if not os.path.exists(MQC):
        sys.exit("bin/mqc not found: run `make` first")
    unittest.main(verbosity=2, warnings="ignore")
