# Benchmark report: smoke

Generated 2026-11-13 19:04. 2 datasets, 54 runs (54 finished, 0 unfinished or failed).

Every score is the quartet score from one scorer (mqc score). Cross-checks: 8 ASTRAL runs compared with the score ASTRAL printed, 4 of our trees re-scored with ASTRAL-III -q; 0 disagreements.

## 1. Overview: best score per dataset

Warm = our search started from ASTRAL's tree. Cold = started from our own orders, no ASTRAL input. Each ASTRAL column is its best run over seeds. 'yes' under optimal means the exact optimum was reached.

| dataset  | taxa | genes | exact optimum | ASTRAL-III | ASTRAL-IV | ours warm | ours cold | our best vs ASTRAL-III | our best vs ASTRAL-IV | optimal?                                          |
|----------|------|-------|---------------|------------|-----------|-----------|-----------|------------------------|-----------------------|---------------------------------------------------|
| sim14    | 14   | 10    | 4,812         | 4,803      | 4,812     | 4,812     | 4,812     | BEAT +9                | TIE                   | ASTRAL-III no, ASTRAL-IV yes, warm yes, cold yes  |
| primates | 14   | 424   | 389,734       | 389,734    | 389,734   | 389,734   | 389,734   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |

Datasets won, tied and lost by each track against each ASTRAL (best run of each):

| comparison         | BEAT | TIE | BEHIND |
|--------------------|------|-----|--------|
| cold vs ASTRAL-III | 1    | 1   | 0      |
| cold vs ASTRAL-IV  | 0    | 2   | 0      |
| warm vs ASTRAL-III | 1    | 1   | 0      |
| warm vs ASTRAL-IV  | 0    | 2   | 0      |

## 3. Methods across all datasets

One row per method. W/T/L compares the method's best run on each dataset with the better ASTRAL. Gap is the average shortfall from the best score any method found, over all runs. Optimal counts runs on datasets with a known optimum.

| track    | method                       | datasets | runs | W / T / L vs ASTRAL | runs >= ASTRAL | runs optimal | mean gap to best | median time to best | median run time |
|----------|------------------------------|----------|------|---------------------|----------------|--------------|------------------|---------------------|-----------------|
| baseline | ASTRAL-III                   | 2        | 2    | 0 / 1 / 1           | 1 / 2          | 1 / 2        | 0.0935%          |                     | 0.80 s          |
| baseline | ASTRAL-III exact             | 2        | 2    | 0 / 2 / 0           | 2 / 2          | 2 / 2        | 0.0000%          |                     | 8.95 s          |
| baseline | ASTRAL-IV                    | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          |                     | 0.27 s          |
| warm     | dp / astral3                 | 2        | 4    | 0 / 2 / 0           | 3 / 4          | 3 / 4        | 0.0260%          | 0.00 s              | 0.02 s          |
| warm     | pairswap-first / astral3     | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.03 s          |
| warm     | vnd / astral3                | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.07 s          |
| cold     | dp / caterpillar             | 2        | 2    | 0 / 1 / 1           | 1 / 2          | 1 / 2        | 0.0520%          | 0.00 s              | 0.02 s          |
| cold     | dp / greedy                  | 2        | 4    | 0 / 1 / 1           | 2 / 4          | 2 / 4        | 0.4000%          | 0.00 s              | 0.02 s          |
| cold     | dp / random                  | 2        | 4    | 0 / 0 / 2           | 0 / 4          | 0 / 4        | 35.0923%         | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / caterpillar | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.03 s          |
| cold     | pairswap-first / greedy      | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.04 s          |
| cold     | pairswap-first / random      | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.04 s          |
| cold     | vnd / caterpillar            | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.03 s          |
| cold     | vnd / greedy                 | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.03 s          |
| cold     | vnd / random                 | 2        | 4    | 0 / 2 / 0           | 4 / 4          | 4 / 4        | 0.0000%          | 0.00 s              | 0.03 s          |

## 4. Detail per dataset

sim14: 14 taxa, 10 gene trees. Best known score 4,812; better ASTRAL 4,812; exact optimum 4,812.

| track    | method                       | runs | best  | median | worst | best vs ASTRAL | median time to best | median run time | RF to ASTRAL-III tree |
|----------|------------------------------|------|-------|--------|-------|----------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III                   | 1    | 4,803 | 4,803  | 4,803 |                |                     | 0.56 s          |                       |
| baseline | ASTRAL-III exact             | 1    | 4,812 | 4,812  | 4,812 |                |                     | 5.45 s          |                       |
| baseline | ASTRAL-IV                    | 2    | 4,812 | 4,812  | 4,812 |                |                     | 0.02 s          |                       |
| warm     | dp / astral3                 | 2    | 4,812 | 4,809  | 4,807 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| warm     | pairswap-first / astral3     | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.02 s          | 4                     |
| warm     | vnd / astral3                | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.06 s          | 4                     |
| cold     | dp / caterpillar             | 1    | 4,807 | 4,807  | 4,807 | BEHIND -5      | 0.00 s              | 0.01 s          | 2                     |
| cold     | dp / greedy                  | 2    | 4,781 | 4,773  | 4,766 | BEHIND -31     | 0.00 s              | 0.01 s          | 12                    |
| cold     | dp / random                  | 2    | 3,999 | 3,745  | 3,492 | BEHIND -813    | 0.00 s              | 0.00 s          | 18                    |
| cold     | pairswap-first / caterpillar | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.02 s          | 4                     |
| cold     | pairswap-first / greedy      | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 0.03 s          | 4                     |
| cold     | pairswap-first / random      | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 0.02 s          | 4                     |
| cold     | vnd / caterpillar            | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.04 s          | 4                     |
| cold     | vnd / greedy                 | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.04 s          | 4                     |
| cold     | vnd / random                 | 2    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.04 s          | 4                     |

primates: 14 taxa, 424 gene trees. Best known score 389,734; better ASTRAL 389,734; exact optimum 389,734.

| track    | method                       | runs | best    | median  | worst   | best vs ASTRAL  | median time to best | median run time | RF to ASTRAL-III tree |
|----------|------------------------------|------|---------|---------|---------|-----------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III                   | 1    | 389,734 | 389,734 | 389,734 |                 |                     | 1.03 s          |                       |
| baseline | ASTRAL-III exact             | 1    | 389,734 | 389,734 | 389,734 |                 |                     | 12 s            |                       |
| baseline | ASTRAL-IV                    | 2    | 389,734 | 389,734 | 389,734 |                 |                     | 0.53 s          |                       |
| warm     | dp / astral3                 | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.03 s          | 0                     |
| warm     | pairswap-first / astral3     | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.04 s          | 0                     |
| warm     | vnd / astral3                | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.07 s          | 0                     |
| cold     | dp / caterpillar             | 1    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.03 s          | 0                     |
| cold     | dp / greedy                  | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | dp / random                  | 2    | 226,566 | 202,578 | 178,591 | BEHIND -163,168 | 0.00 s              | 0.02 s          | 18                    |
| cold     | pairswap-first / caterpillar | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.04 s          | 0                     |
| cold     | pairswap-first / greedy      | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.04 s          | 0                     |
| cold     | pairswap-first / random      | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.06 s          | 0                     |
| cold     | vnd / caterpillar            | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.03 s          | 0                     |
| cold     | vnd / greedy                 | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.03 s          | 0                     |
| cold     | vnd / random                 | 2    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.03 s          | 0                     |

## 5. Checks

All scorers agree, no result exceeds an exact optimum, and every run finished.
