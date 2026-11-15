# Results

Benchmark of a circular-order dynamic program against ASTRAL-III and ASTRAL-IV on real
phylogenomic datasets. Every tree is scored by the same quartet scorer, and scores are
cross-checked against ASTRAL's own.

**Summary.** Across 156 real datasets and 48,250 runs, the method matches ASTRAL
everywhere and beats it once. It reaches the same answer 100-220x faster on the datasets
tested. On the 142 instances where the true optimum is computable, every method finds it.

## What was run

| Stage | Datasets | Runs | Question |
|---|---|---|---|
| A | 152 at 12-16 taxa, from mammals, 1KP, 1KP-BS10, angiosperms, avian | 47,861 | Does ASTRAL ever miss the exact optimum? Which strategies work? |
| B | mammals (37), angiosperms (46), avian (48), 1KP (103), 1KP-BS10 (103) | 389 | Can anything beat ASTRAL where optimality cannot be verified? |

Datasets are those used in the ASTRAL papers: Song et al. 2012 (mammals), Wickett et al.
2014 (1KP), Xi et al. 2014 (angiosperms), Jarvis et al. 2014 (avian).

## Stage A: ASTRAL is effectively optimal at 12-16 taxa

On all 142 instances with a verified optimum, ASTRAL-III, ASTRAL-IV and this method all
reach it. Individual runs are not perfectly reliable:

| Method | Single runs optimal | Miss rate |
|---|---|---|
| ASTRAL-III | 423 / 426 | 0.70% |
| ASTRAL-IV | 425 / 426 | 0.23% |
| ASTRAL-IV `-R` | 142 / 142 | 0% |

`anneal`, `ils` and `multistart` were optimal in all 4,970 runs each, from every starting
order including random. `vnd` missed twice in 4,970.

The one win across both stages is ASTRAL's simulated 14-taxon dataset, where ASTRAL-III
scores 4,792-4,803 by seed and this method reaches the optimum of 4,812. ASTRAL-IV also
finds it.

## Stage B: identical trees at 37-103 taxa

All five strategies, all starting orders, all seeds tie with both ASTRALs on all four
completed datasets - and the Robinson-Foulds distance to ASTRAL-III's tree is 0 in every
case. Not merely equal scores: identical topologies.

| Dataset | Taxa | Genes | Score (all methods) |
|---|---|---|---|
| mammals | 37 | 424 | 25,526,915 |
| angiosperms | 46 | 310 | 11,553,053 |
| 1KP | 103 | 424 | 339,023,690 |
| 1KP-BS10 | 103 | 424 | 326,972,173 |

Avian TENT (48 taxa, 14,446 gene trees) is incomplete: ASTRAL-III did not finish within
11 hours, consistent with the 32 hours reported in its own paper. ASTRAL-IV completed it
in 0.5 hours, scoring 1,231,992,828.

## Speed

A single DP call on a data-derived circular order, with no search at all:

| Dataset | ASTRAL-III | ASTRAL-IV | DP alone | Result |
|---|---|---|---|---|
| mammals | 2.86 s | 10 s | 0.02 s | ties |
| angiosperms | 5.15 s | 5.49 s | 0.02 s | ties |
| 1KP-BS10 | 38 s | 54 s | 0.17 s | ties |
| 1KP | 44 s | 49 s | 0.27 s | 0.002% short |

Caveats: DP times exclude building the quartet weight table, which is cached across runs;
ASTRAL-III times include JVM startup. Search methods reach the same score in 0.01-3 s of
time-to-best but have no stopping rule, so they consume their full budget.

## The starting order carries the method

The DP is exact for a given circular order, so running it alone measures what the order is
worth. Mean shortfall from the best score found, at 37-103 taxa:

| Starting order | Mean gap | Ties ASTRAL |
|---|---|---|
| random | 57.41% | 0 / 12 |
| gene-tree leaf order | 5.93% | 0 / 12 |
| distance-based tour | 0.047% | 2 / 4 |
| greedy insertion | 0.026% | 4 / 12 |

At 12-16 taxa the same ladder runs from 42.9% (random) to 0.021% (distance). The
deterministic caterpillar construction, whose only proven guarantee is 1/3 of the total
weight, lands within 1.13% in practice.

## Validation

- An independent reimplementation in Python, plus brute force over all trees for n <= 9
- 304 output trees re-scored with `astral -q`: zero disagreements
- 1,234 ASTRAL runs checked against the scores ASTRAL printed: zero disagreements
- No result anywhere exceeds a verified exact optimum
- 48,250 runs, zero failures

## Limitations

- The explicit quartet table limits this implementation to roughly 150 taxa
- Ten avian 16-taxon instances have no verified optimum; exact mode did not finish
- Avian TENT lacks an ASTRAL-III baseline for the same reason
- Gene trees with a repeated taxon are skipped

## Reproducing

See `README.md`. `configs/stageA.json` and `configs/stageB.json` define the runs;
`results/stageA/` and `results/stageB/` hold the full reports and per-run CSVs.
