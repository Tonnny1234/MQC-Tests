#!/usr/bin/env python3
"""Control experiment: give ASTRAL-III the search space of one of our orders.

For the circular order stored in a search result, write its n rotated caterpillar trees and pass them to
ASTRAL-III as extra trees (-e). Every arc of the order then becomes a candidate cluster, so ASTRAL solves at
least the problem our DP solves for that order. If ASTRAL now matches our score, the gain came from finding
the order, not from the DP.

  python3 tools/astral_hybrid.py --result results/.../search/vnd__random__s1.json --out /tmp/hybrid
"""
import argparse
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import MQC, abspath, astral3_jar, clean_env, java, run


def caterpillar(order):
    t = "(%s,%s)" % (order[0], order[1])
    for x in order[2:-1]:
        t = "(%s,%s)" % (t, x)
    return "(%s,%s);" % (t, order[-1])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--result", required=True, help="a search result .json (it stores the best order)")
    ap.add_argument("--out", required=True, help="output prefix")
    a = ap.parse_args()
    with open(a.result) as f:
        res = json.load(f)
    order, genes = res["order"], abspath(res["genes"])
    extra = a.out + ".extra.tre"
    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    with open(extra, "w") as f:
        for r in range(len(order)):
            f.write(caterpillar(order[r:] + order[:r]) + "\n")
    tree = a.out + ".tre"
    code, out, err = run([java(), "-jar", astral3_jar(), "-i", genes, "-e", extra, "-o", tree, "-t", "0"], env=clean_env())
    m = re.findall(r"Final quartet score is:\s*(\d+)", err + out)
    if code != 0 or not m:
        sys.exit("ASTRAL failed: " + (err.strip().splitlines() or [""])[-1])
    code, out2, _ = run([MQC, "score", "--genes", genes, "--trees", tree])
    ours = int(out2.split()[0])
    print(json.dumps({"our_search_score": res["score"], "astral3_with_order_arcs": int(m[-1]), "rescored_by_mqc": ours, "tree_file": tree}, indent=2))


if __name__ == "__main__":
    main()
