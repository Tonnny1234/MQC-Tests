#!/usr/bin/env python3
"""Turn a config file into task lists (one shell command per line).

  python3 tools/make_tasks.py configs/smoke.json

writes  tasks/<name>.phase1.txt   ASTRAL baselines (and exact optima on small datasets)
        tasks/<name>.phase2.txt   our searches; warm starts read the phase-1 trees, so run phase 1 first
Every command is safe to run again: finished work is skipped and unfinished searches resume.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import ROOT, baseline_list, baseline_prefix, expand_datasets, load_config, rel, search_prefix


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    cfg = load_config(sys.argv[1])
    datasets = expand_datasets(cfg, create=True)
    if not datasets:
        sys.exit("no datasets found; check the 'genes' paths in the config")
    p1, p2 = [], []
    s = cfg.get("search", {})
    threads = cfg.get("astral4_threads", 1)
    for ds in datasets:
        table = os.path.join(ds["dir"], "table.bin")
        for sub in ("baseline", "search"):
            os.makedirs(os.path.join(ds["dir"], sub), exist_ok=True)
        for method, seed in baseline_list(cfg, ds):
            cmd = "python3 tools/run_baseline.py --method %s --genes %s --table %s --seed %d --out %s" % (
                method, rel(ds["genes"]), rel(table), seed, rel(baseline_prefix(ds, method, seed)))
            if method.startswith("astral4"):
                cmd += " --threads %d" % threads
            else:
                cmd += " --java-mem %s" % cfg.get("java_mem", "3g")
            cmd += " --timeout %d" % (cfg.get("exact_timeout", 7200) if method == "astral3-exact"
                                      else cfg.get("baseline_timeout", 3600))
            p1.append(cmd)
        starts = [("warm", w) for w in s.get("warm", [])] + [("cold", c) for c in s.get("cold", [])]
        for strategy in s.get("strategies", []):
            for track, start in starts:
                seeds = s.get("seeds", [1])
                if strategy == "dp" and start in ("caterpillar", "distance"):
                    seeds = seeds[:1]                     # deterministic start + no search: one run is enough
                for seed in seeds:
                    cmd = "bin/mqc search --genes %s --table %s --strategy %s --seed %d --time %s --out %s" % (
                        rel(ds["genes"]), rel(table), strategy, seed, s.get("time", 60), rel(search_prefix(ds, strategy, start, seed)))
                    if track == "warm":                   # start from the first-seed tree of that baseline
                        cmd += " --start tree --start-tree %s.tre --start-orients %d" % (rel(baseline_prefix(ds, start, 1)), s.get("warm_orients", 1))
                    else:
                        cmd += " --start %s" % start
                    cmd += " --tags track=%s,startname=%s" % (track, start)
                    p2.append(cmd)
    os.makedirs(os.path.join(ROOT, "tasks"), exist_ok=True)
    for name, lines in (("phase1", p1), ("phase2", p2)):
        path = os.path.join(ROOT, "tasks", "%s.%s.txt" % (cfg["name"], name))
        with open(path, "w") as f:
            f.write("\n".join(lines) + ("\n" if lines else ""))
        print("%-28s %5d tasks" % (rel(path), len(lines)))
    print("%d datasets: %s%s" % (len(datasets), ", ".join(d["name"] for d in datasets[:6]), " ..." if len(datasets) > 6 else ""))


if __name__ == "__main__":
    main()
