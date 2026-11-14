"""Shared helpers for the benchmark tools. Standard library only; works on Python 3.6+."""
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MQC = os.path.join(ROOT, "bin", "mqc")


def astral3_jar():
    return os.environ.get("ASTRAL3_JAR", os.path.join(ROOT, "ext", "ASTRAL", "Astral", "astral.5.7.8.jar"))


def astral4_bin():
    return os.environ.get("ASTRAL4_BIN", os.path.join(ROOT, "ext", "ASTER", "bin", "astral4"))


def java():
    return os.environ.get("JAVA", "java")


def run(cmd, timeout=None, env=None):
    """Run a command; return (exit code, stdout, stderr). exit code -9 means it hit the timeout."""
    try:
        p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, timeout=timeout, env=env)
        return p.returncode, p.stdout, p.stderr
    except subprocess.TimeoutExpired as e:
        return -9, e.stdout or "", e.stderr or ""


def clean_env():
    env = dict(os.environ)
    env.pop("JAVA_TOOL_OPTIONS", None)
    return env


def rel(path):
    return os.path.relpath(path, ROOT)


def abspath(path):
    return path if os.path.isabs(path) else os.path.join(ROOT, path)


def load_config(path):
    with open(path) as f:
        cfg = json.load(f)
    cfg.setdefault("name", os.path.splitext(os.path.basename(path))[0])
    return cfg


def mqc_info(genes):
    code, out, err = run([MQC, "info", "--genes", genes])
    if code != 0:
        sys.exit("mqc info failed for %s: %s" % (genes, err))
    return json.loads(out)


def expand_datasets(cfg, create=False):
    """List every dataset of a config, including taxon-subsampled ones.

    Each entry: name, genes (absolute path), dir (results folder), n, k, parent.
    With create=True the subsampled gene-tree files are generated if missing.
    """
    out = []
    resdir = os.path.join(ROOT, "results", cfg["name"])
    workdir = os.path.join(ROOT, "work", cfg["name"])
    base = {}
    for d in cfg.get("datasets", []):
        genes = abspath(d["genes"])
        if not os.path.exists(genes):
            sys.stderr.write("note: dataset %s skipped, file not found: %s\n" % (d["name"], genes))
            continue
        info = mqc_info(genes)
        e = {"name": d["name"], "genes": genes, "dir": os.path.join(resdir, d["name"]), "n": info["n"], "k": info["k"], "parent": None}
        base[d["name"]] = e
        if not d.get("subsets_only"):
            out.append(e)
    sub = cfg.get("subsets")
    if sub:
        for parent in sub["from"]:
            if parent not in base:
                continue
            for size in sub["sizes"]:
                if size >= base[parent]["n"]:
                    continue
                for r in range(1, sub["replicates"] + 1):
                    name = "%s.n%d.r%d" % (parent, size, r)
                    genes = os.path.join(workdir, name + ".tre")
                    if create and not os.path.exists(genes):
                        os.makedirs(workdir, exist_ok=True)
                        seed = 1000 * size + r
                        code, _, err = run([MQC, "subsample", "--genes", base[parent]["genes"], "--ntaxa", str(size), "--seed", str(seed), "--out", genes])
                        if code != 0:
                            sys.exit("subsample failed: " + err)
                    if os.path.exists(genes):
                        info = mqc_info(genes)
                        out.append({"name": name, "genes": genes, "dir": os.path.join(resdir, name), "n": info["n"], "k": info["k"], "parent": parent})
    return out


def baseline_prefix(ds, method, seed):
    return os.path.join(ds["dir"], "baseline", "%s.s%d" % (method, seed))


def search_prefix(ds, strategy, start, seed):
    return os.path.join(ds["dir"], "search", "%s__%s__s%d" % (strategy, start, seed))


def baseline_list(cfg, ds):
    """(method, seed) pairs for a dataset; exact mode is added automatically for small datasets."""
    out = []
    for b in cfg.get("baselines", []):
        for s in b.get("seeds", [1]):
            out.append((b["method"], s))
    if ds["n"] <= cfg.get("exact_max_taxa", 0):
        out.append(("astral3-exact", 1))
    return out
