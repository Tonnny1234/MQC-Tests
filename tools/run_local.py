#!/usr/bin/env python3
"""Run a task file on this machine, without Slurm. For small tests only (never for big runs on a login node).

  python3 tools/run_local.py tasks/smoke.phase1.txt [-j 2]
"""
import argparse
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def one(cmd):
    p = subprocess.run(cmd, shell=True, cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    return cmd, p.returncode, p.stdout


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("taskfile")
    ap.add_argument("-j", "--jobs", type=int, default=1)
    a = ap.parse_args()
    cmds = [l.strip() for l in open(a.taskfile) if l.strip()]
    failed = 0
    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        for i, (cmd, code, out) in enumerate(ex.map(one, cmds), 1):
            last = (out.strip().splitlines() or [""])[-1]
            print("[%d/%d] %s %s" % (i, len(cmds), "ok  " if code == 0 else "FAIL", last[:150]))
            if code != 0:
                failed += 1
                print("       command: " + cmd)
    print("%d tasks, %d failed" % (len(cmds), failed))
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
