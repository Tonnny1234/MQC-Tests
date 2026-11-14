# mqc-bench

Search over circular orders with an exact O(M + n³) dynamic program per order, benchmarked against the
official ASTRAL-III and ASTRAL-IV on ASTRAL's own datasets.

Everything here was built and run before packaging: the 13-test suite passes, and on every dataset tried
our scorer gives exactly the quartet score that ASTRAL-III and ASTRAL-IV print (see "What was measured").

## 1. What is in the folder

| Path | What it is |
|------|------------|
| `src/` | The C++ engine, `mqc`: quartet table, exact DP, incremental swaps, starting orders, search strategies |
| `tools/` | Python scripts: run ASTRAL, generate task lists, track progress, write the report |
| `tests/` | Test suite with an independent Python reference implementation |
| `configs/` | Benchmark definitions: `smoke`, `preview`, `stageA`, `stageB` |
| `slurm/` | Job scripts for the Campus Cluster |
| `data/` | Where extra datasets go (see `data/README.md`) |
| `examples/` | A real report produced by the `preview` config |
| `env.sh` | The one file you edit: account, partition, module names |
| `setup.sh` | One-time installation |

Python needs only the standard library (3.6 or newer). The engine needs g++ and, for ASTRAL-III, Java.

## 2. Run it on the Campus Cluster, step by step

Lines starting with `laptop$` are typed on your computer; `cluster$` on the cluster after `ssh`.

### Step 0. Upload and unpack

    laptop$  scp mqc-bench.zip tony6@cli-dtn.researchdata.illinois.edu:~/
    laptop$  ssh tony6@cc-login.campuscluster.illinois.edu
    cluster$ unzip mqc-bench.zip
    cluster$ cd mqc-bench

### Step 1. Install (about 2 minutes, on the login node)

    cluster$ module avail gcc
    cluster$ module avail java
    cluster$ nano env.sh          # put the module names you saw into the two "module load" lines
    cluster$ bash setup.sh

`setup.sh` builds `bin/mqc`, downloads ASTRAL-III and ASTRAL-IV from GitHub at pinned commits, builds
ASTRAL-IV, and runs the engine's self-test. It must end with `selftest: ... 0 failures` and a `java:` line.
If it prints `WARNING: java not found`, fix the Java line in `env.sh` and run it again.

### Step 2. Run the test suite as a job (about 2 minutes once it starts)

    cluster$ sbatch --partition=secondary slurm/tests.sbatch
    cluster$ squeue -u $USER                 # wait until the job is gone
    cluster$ tail -5 logs/tests.*.out

The last lines must read `Ran 13 tests in ...` and `OK`. Leave out `--partition=secondary` to use your own
`cs` partition instead; it is often full, so the shared queue usually starts sooner.

### Step 3. Smoke benchmark (2 tiny datasets, 54 runs, a few minutes)

Each benchmark has two phases. Phase 1 runs ASTRAL. Phase 2 runs our searches; the warm starts read
ASTRAL's trees, so phase 2 must wait for phase 1 (`--after`).

    cluster$ python3 tools/make_tasks.py configs/smoke.json
    cluster$ bash slurm/submit.sh tasks/smoke.phase1.txt --partition secondary --time 00:20:00
    pass 1: submitted job 12345678  (8 tasks ...)
    cluster$ bash slurm/submit.sh tasks/smoke.phase2.txt --partition secondary --time 00:20:00 --after 12345678
    cluster$ python3 tools/progress.py tasks/smoke.phase2.txt      # repeat until "done 46"
    cluster$ python3 tools/report.py configs/smoke.json

The report prints to the screen and is saved as `results/smoke/report.md`, `report.html` and
`results.csv`. To read the web page on your laptop:

    laptop$  scp tony6@cli-dtn.researchdata.illinois.edu:~/mqc-bench/results/smoke/report.html .

### Step 4. Stage A: small instances with known optimum (about 40 core-hours)

92 datasets: two 14-taxon sets plus random 12-, 14- and 16-taxon subsets of mammals, 1KP and 1KP-BS10,
each with ASTRAL's exact optimum. 9 strategies × 7 starting orders × 5 seeds on each.

    cluster$ python3 tools/make_tasks.py configs/stageA.json
    cluster$ bash slurm/submit.sh tasks/stageA.phase1.txt --partition secondary --time 01:00:00 --chunk 8
    cluster$ bash slurm/submit.sh tasks/stageA.phase2.txt --partition secondary --time 00:40:00 --after <phase-1 job id>
    cluster$ python3 tools/progress.py tasks/stageA.phase2.txt
    cluster$ python3 tools/report.py configs/stageA.json

`submit.sh` packs the 28,244 phase-2 commands into 883 array tasks by itself, to stay under the cluster's
limit of 1,000 queued jobs.

### Step 5. Stage B: the full real datasets (up to about 400 core-hours)

Mammals (37 taxa), 1KP (103 taxa) and 1KP-BS10, plus any dataset you add to `data/`. Each search gets one
hour. Searches that hit a job's time limit save a checkpoint; `--repeat 2` submits a second pass that
resumes them.

    cluster$ python3 tools/make_tasks.py configs/stageB.json
    cluster$ bash slurm/submit.sh tasks/stageB.phase1.txt --partition secondary --time 03:00:00 --mem-per-cpu 16G
    cluster$ bash slurm/submit.sh tasks/stageB.phase2.txt --partition secondary --time 01:30:00 --repeat 2 --after <phase-1 job id>
    cluster$ python3 tools/progress.py tasks/stageB.phase2.txt --list
    cluster$ python3 tools/report.py configs/stageB.json

To give searches more time or more seeds, edit `"time"` (seconds) and `"seeds"` in `configs/stageB.json`,
run `make_tasks.py` again and resubmit. Finished runs are never repeated.

### Everyday commands

| Task | Command |
|------|---------|
| What is queued or running | `squeue -u $USER` |
| How far a task file has got | `python3 tools/progress.py tasks/<name>.txt` (add `--list` to see which are not done) |
| Output of one array task | `less logs/<taskfile name>/<jobid>_<index>.out` |
| Cancel a whole submission | `scancel <jobid>` |
| Resume after a cancel or time limit | submit the same task file again |
| Use your own nodes instead | replace `--partition secondary` by `--partition cs`; `--time` may then go up to 7 days |
| Fill one whole 32-core node per array task | add `--cpus 32 --chunk 320` (32 commands at a time, 320 per task) |
| See the exact sbatch command first | add `--dry-run` |

The shared `secondary` queue stops jobs after 4 hours, so keep `--time` at or below `04:00:00` there.

## 3. Reading the report

1. **Overview.** One row per dataset: the exact optimum when known, the best ASTRAL-III and ASTRAL-IV
   scores over their seeds, our best warm-start and cold-start scores, and a verdict: `BEAT +x`, `TIE` or
   `BEHIND -x` quartets.
2. **Subsampled datasets.** How often each method reached the exact optimum.
3. **Methods across all datasets.** Wins / ties / losses against ASTRAL, share of runs at least as good
   as ASTRAL, share of runs that are optimal, mean gap to the best known score, and time.
4. **Detail per dataset.** Best, median and worst score per method, and the Robinson-Foulds distance
   between our best tree and ASTRAL-III's tree.
5. **Checks.** Any disagreement between scorers, any score above an exact optimum, any unfinished run.
   The report command exits with an error if a check fails.

"Warm" means the search started from ASTRAL's tree; "cold" means it started from one of our own orders
with no ASTRAL input. Scores are raw quartet scores, the quantity ASTRAL maximizes.

## 4. The engine: `bin/mqc`

    bin/mqc search --genes G --out PREFIX --strategy vnd --start greedy --seed 1 --time 600
    bin/mqc score  --genes G --trees some_trees.tre
    bin/mqc help

`search` writes `PREFIX.tre` (best tree) and `PREFIX.json` (score, time, trajectory, best order). Before
writing, it re-scores its own tree with a separate routine and refuses to write if the two disagree.

| `--strategy` | Plan ID | What it does |
|--------------|---------|--------------|
| `dp` | – | Only the exact DP on the starting order |
| `reorient` | N0 | DP, then re-orient the best tree and repeat (never gets worse) |
| `pairswap-first` | A1 | Try every pair swap, take each improvement, repeat until none helps |
| `pairswap-best` | A2 | Score every pair swap, take the best one, repeat |
| `vnd` | A3 | Ladder of moves: re-orient, adjacent swaps, pair swaps, insertions, block moves, reversals, clade moves |
| `anneal` | A4 | Simulated annealing over orders, then a `vnd` polish from the best order |
| `ils` | A6 | `vnd`, random kick, `vnd` again; keep if not worse |
| `tabu` | A7 | Best sampled pair swap each step, even if worse; recent swaps are forbidden |
| `multistart` | A8 | `vnd` from fresh starting orders until time runs out |

| `--start` | Plan ID | Starting order |
|-----------|---------|----------------|
| `tree` with `--start-tree F` | S1, S3, S10 | Random orientation of a given tree (ASTRAL's, or one of ours) |
| `tree` with `--start-orients K` | S2 | Best of K orientations |
| `genetree` | S4 | Leaf order of a gene tree |
| `distance` | S5 | Short tour through the average gene-tree distances |
| `random` | S6 | Random order |
| `caterpillar` | S7 | Deterministic order whose caterpillar already scores at least a third of the total |
| `greedy` | S8 | Taxa inserted one at a time where the fewest quartets cross |
| `bestrandom` | S9 | Best of 32 random orders |

Control experiment (plan ID A9): `python3 tools/astral_hybrid.py --result <search>.json --out <prefix>`
hands ASTRAL-III every arc of our best order as extra candidate clusters.

## 5. Adding datasets and writing configs

Put gene trees in `data/` (see `data/README.md`) and list them in a config:

    {"name": "avian-tent", "genes": "data/avian_tent.tre"}

Config fields: `datasets`; `subsets` (`from`, `sizes`, `replicates`) to create taxon-subsampled copies;
`"subsets_only": true` on a dataset to use only its subsets; `exact_max_taxa` to run ASTRAL's exact mode
on datasets up to that size; `baselines` (methods and seeds); `search` (`strategies`, `warm`, `cold`,
`seeds`, `time` in seconds). Missing dataset files are skipped with a note.

## 6. Tests

    python3 tests/run_tests.py

- **Engine vs independent reference.** A separate Python implementation reads quartets off bipartitions
  and enumerates every tree. Checked: the scorer on every 6-taxon tree, the DP against brute force for
  every circular order on 6 and 7 taxa, every strategy and start, warm starts, checkpoint and resume.
- **Engine vs ASTRAL.** Our scorer equals the score ASTRAL-III and ASTRAL-IV print; ASTRAL `-q` gives our
  trees the score we report; nothing exceeds ASTRAL's exact optimum; the cold search reaches the exact
  optimum on both 14-taxon sets; ASTRAL-III with our order's arcs reaches our score.
- **Pipeline.** Config to task lists to runs to report, including resubmission.

`bin/mqc selftest` alone runs randomized internal checks (incremental swap equals full rebuild, DP equals
brute force, rotation and mirror invariance, the one-third guarantee) without needing any data.

## 7. What was measured while building this (2-core sandbox, not the cluster)

| Dataset | Taxa | Genes | ASTRAL-III | ASTRAL-IV | Exact | Ours |
|---------|------|-------|-----------|-----------|-------|------|
| simulated_14taxon | 14 | 10 | 4,792 or 4,803 by seed | 4,812 | 4,812 | 4,812 from every start tried |
| song_primates | 14 | 424 | 389,734 | 389,734 | 389,734 | 389,734 |
| song_mammals | 37 | 424 | 25,526,915 | 25,526,915 | – | 25,526,915, warm and cold |
| 1KP | 103 | 424 | 339,023,690 | 339,023,690 | – | 339,023,690 from ASTRAL's tree; cold runs were not taken to convergence |

- On 12 random 12- and 14-taxon subsets of mammals and 1KP, ASTRAL-III, ASTRAL-IV and our searches all
  reached the exact optimum. The only instance where anything differed is the simulated 14-taxon set,
  where ASTRAL-III misses the optimum and ASTRAL-IV and we find it.
- Speed at 103 taxa: table built in 0.6 s, one full DP about 0.1 s, one swap evaluation about 25 ms.
  At 37 taxa `vnd` converges in about 3.5 s.
- ASTRAL-III exact mode took about 5–35 s at 14 taxa, 95 s at 16 taxa, and more than 15 minutes at 18.
  That is why stage A stops at 16.

## 8. Limits and things not included

- **About 150 taxa at most.** The table stores all C(n,4) four-taxon sets.
- **One copy of each taxon per gene tree.** Trees with a repeated taxon are skipped and counted in
  `skipped_trees`.
- **Annealed Gibbs sampler (plan A5) is not in the C++ engine.** It lost to restarts in the earlier
  Python experiment; that Python version is the only implementation.
- **No upper-bound pruning of swaps.** The plan floated it; it is not implemented.
- **`pairswap-best` and `tabu` are slow above about 60 taxa**, because every step scores many swaps.
- **ASTRAL-III depends on its seed** (4,792 vs 4,803 above), so the configs run several seeds and the
  report uses its best.
- **Large published datasets are not bundled.** The Dryad archives named in `data/README.md` were not
  opened while writing this.
- **Not yet run on the Campus Cluster.** Module names in `env.sh` and the Python version there are the
  likeliest things to need a tweak.
