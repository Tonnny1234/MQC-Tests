#!/usr/bin/env python3
"""Show how far a task file has got:   python3 tools/progress.py tasks/stageB.phase2.txt [--list]

done        the result file exists and the run finished
unfinished  the run was cut by a time limit and saved a checkpoint (resubmit the task file to resume)
failed      a baseline ended with an error (see its .log file)
missing     not started yet, or still running
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    counts = {"done": 0, "unfinished": 0, "failed": 0, "missing": 0}
    shown = []
    for line in open(sys.argv[1]):
        parts = line.split()
        if "--out" not in parts:
            continue
        prefix = os.path.join(ROOT, parts[parts.index("--out") + 1])
        state = "missing"
        if os.path.exists(prefix + ".json"):
            try:
                j = json.load(open(prefix + ".json"))
                state = "done" if j.get("finished") else ("unfinished" if j.get("tool") == "mqc" else "failed")
            except ValueError:
                state = "missing"
        counts[state] += 1
        if state != "done":
            shown.append("%-10s %s" % (state, os.path.relpath(prefix, ROOT)))
    total = sum(counts.values())
    print("%s: %d tasks | done %d | unfinished %d | failed %d | missing %d" % (
        sys.argv[1], total, counts["done"], counts["unfinished"], counts["failed"], counts["missing"]))
    if "--list" in sys.argv:
        print("\n".join(shown))


if __name__ == "__main__":
    main()
