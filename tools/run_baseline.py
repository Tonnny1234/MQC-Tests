#!/usr/bin/env python3
"""Run one ASTRAL baseline and record its tree, time and quartet score.

Methods:  astral3         ASTRAL-III 5.7.8, default heuristic search
          astral3-exact   ASTRAL-III exact mode (-x); only feasible up to about 18 taxa
          astral4         ASTRAL-IV (ASTER), default
          astral4-R       ASTRAL-IV with more search rounds (-R)
Writes PREFIX.tre, PREFIX.log and PREFIX.json. Does nothing if PREFIX.json already exists.
"""
import argparse
import json
import os
import re
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import MQC, astral3_jar, astral4_bin, clean_env, java, run


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--method", required=True, choices=["astral3", "astral3-exact", "astral4", "astral4-R"])
    ap.add_argument("--genes", required=True)
    ap.add_argument("--out", required=True, help="output prefix")
    ap.add_argument("--table", default="")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--threads", type=int, default=1)
    ap.add_argument("--timeout", type=float, default=None, help="seconds; the run is abandoned after this")
    ap.add_argument("--java-mem", default="3g")
    a = ap.parse_args()

    jpath, tree, log = a.out + ".json", a.out + ".tre", a.out + ".log"
    if os.path.exists(jpath):
        print("already done: " + jpath)
        return
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    if a.method.startswith("astral3"):
        if not os.path.exists(astral3_jar()):
            sys.exit("ASTRAL-III jar not found at %s (run setup.sh or set ASTRAL3_JAR)" % astral3_jar())
        cmd = [java(), "-Xmx" + a.java_mem, "-jar", astral3_jar(), "-i", a.genes, "-o", tree, "-t", "0", "-s", str(a.seed)]
        if a.method == "astral3-exact":
            cmd.append("-x")
        pattern = r"Final quartet score is:\s*(\d+)"
    else:
        if not os.path.exists(astral4_bin()):
            sys.exit("ASTRAL-IV binary not found at %s (run setup.sh or set ASTRAL4_BIN)" % astral4_bin())
        cmd = [astral4_bin(), "-t", str(a.threads), "--seed", str(a.seed), "-u", "0", "-o", tree]
        if a.method == "astral4-R":
            cmd.append("-R")
        cmd.append(a.genes)
        pattern = r"^Score:\s*(\d+)"

    t0 = time.time()
    code, out, err = run(cmd, timeout=a.timeout, env=clean_env())
    wall = time.time() - t0
    with open(log, "w") as f:
        f.write(" ".join(cmd) + "\n" + out + err)
    res = {"tool": a.method, "genes": a.genes, "seed": a.seed, "threads": a.threads, "elapsed": wall,
           "finished": code == 0 and os.path.exists(tree), "exit_code": code, "tree_file": tree}
    m = re.findall(pattern, err + out, flags=re.M)
    if m:
        res["reported_score"] = int(m[-1])
    if res["finished"]:
        cmd2 = [MQC, "score", "--genes", a.genes, "--trees", tree] + (["--table", a.table] if a.table else [])
        c2, o2, e2 = run(cmd2)
        if c2 == 0 and o2.split():
            f = o2.split()
            res["score"], res["total_weight"], res["normalized"] = int(f[0]), int(f[1]), float(f[2])
            res["score_mismatch"] = "reported_score" in res and res["reported_score"] != res["score"]
        else:
            res["finished"] = False
            res["error"] = "could not score the tree: " + e2.strip()
    elif code == -9:
        res["error"] = "timed out after %.0f s" % a.timeout
    else:
        res["error"] = (err.strip().splitlines() or ["failed"])[-1]
    with open(jpath + ".part", "w") as f:
        json.dump(res, f, indent=2)
    os.rename(jpath + ".part", jpath)
    print("%s seed %d: %s in %.1fs" % (a.method, a.seed, res.get("score", res.get("error")), wall))


if __name__ == "__main__":
    main()
