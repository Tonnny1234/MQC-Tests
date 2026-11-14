#!/bin/bash
# setup.sh - one-time installation. Run on a login node:   bash setup.sh
# Builds our engine, downloads the official ASTRAL-III and ASTRAL-IV sources at pinned commits, builds
# ASTRAL-IV, and runs the engine's self-test. Safe to run again.
set -e
cd "$(dirname "$0")"
source env.sh
ASTRAL3_COMMIT=068a4b2497f61c866c4727bfbfd78b4361ba27c8
ASTER_COMMIT=ddc3dc6b28b20cecfec18cede8c6247decc82b77

fetch() {   # fetch <url> <dir> <commit>: shallow clone, then pin the exact commit
    if [ ! -d "$2/.git" ]; then git clone --quiet --depth 1 "$1" "$2"; fi
    if git -C "$2" fetch --quiet --depth 1 origin "$3" 2>/dev/null && git -C "$2" checkout --quiet "$3" 2>/dev/null; then
        echo "   pinned to commit ${3:0:7}"
    else
        echo "   WARNING: could not pin commit ${3:0:7}; using $(git -C "$2" rev-parse --short HEAD)"
    fi
}

echo "== 1/4  building our engine (bin/mqc)"
make
echo "== 2/4  ASTRAL-III (github.com/smirarab/ASTRAL)"
mkdir -p ext logs tasks results work
fetch https://github.com/smirarab/ASTRAL.git ext/ASTRAL $ASTRAL3_COMMIT
[ -f ext/ASTRAL/Astral/astral.5.7.8.jar ] || (cd ext/ASTRAL && unzip -q -o Astral.5.7.8.zip)
echo "== 3/4  ASTRAL-IV (github.com/chaoszhang/ASTER)"
fetch https://github.com/chaoszhang/ASTER.git ext/ASTER $ASTER_COMMIT
mkdir -p ext/ASTER/bin
# built without -march=native so the binary also runs on compute nodes with a different CPU
[ -x ext/ASTER/bin/astral4 ] || g++ -std=gnu++11 -O2 -pthread ext/ASTER/src/astral.cpp -o ext/ASTER/bin/astral4
echo "== 4/4  checks"
bin/mqc selftest --trials 40
if "${JAVA:-java}" -version >/dev/null 2>&1; then
    echo "java: $("${JAVA:-java}" -version 2>&1 | grep -m1 -i version)"
else
    echo "WARNING: java not found. Run 'module avail java', put the right 'module load ...' line in env.sh, and run setup.sh again."
fi
ls -1 ext/ASTRAL/Astral/test_data/*.tre | sed 's/^/   dataset: /'
echo
echo "Setup finished. Next:  sbatch slurm/tests.sbatch     (runs the test suite as a job)"
