#!/bin/bash
#SBATCH --job-name=mqc-tests
#SBATCH --account=cs-sariel
#SBATCH --partition=cs
#SBATCH --time=00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=4G
#SBATCH --output=logs/tests.%j.out
# Runs the whole test suite on a compute node. Submit from the project folder:
#   sbatch slurm/tests.sbatch                         (your own partition)
#   sbatch --partition=secondary slurm/tests.sbatch   (shared queue, usually starts sooner)
cd "$SLURM_SUBMIT_DIR"
source env.sh
make
python3 tests/run_tests.py
