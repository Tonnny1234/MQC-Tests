# Benchmark report: preview

Generated 2026-11-13 17:46. 13 datasets, 468 runs (468 finished, 0 unfinished or failed).

Every score is the quartet score from one scorer (mqc score). Cross-checks: 65 ASTRAL runs compared with the score ASTRAL printed, 26 of our trees re-scored with ASTRAL-III -q; 0 disagreements.

## 1. Overview: best score per dataset

Warm = our search started from ASTRAL's tree. Cold = started from our own orders, no ASTRAL input. Each ASTRAL column is its best run over seeds. 'yes' under optimal means the exact optimum was reached.

| dataset        | taxa | genes | exact optimum | ASTRAL-III | ASTRAL-IV | ours warm | ours cold | our best vs ASTRAL-III | our best vs ASTRAL-IV | optimal?                                          |
|----------------|------|-------|---------------|------------|-----------|-----------|-----------|------------------------|-----------------------|---------------------------------------------------|
| sim14          | 14   | 10    | 4,812         | 4,803      | 4,812     | 4,812     | 4,812     | BEAT +9                | TIE                   | ASTRAL-III no, ASTRAL-IV yes, warm yes, cold yes  |
| mammals.n12.r1 | 12   | 424   | 194,611       | 194,611    | 194,611   | 194,611   | 194,611   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r2 | 12   | 424   | 195,917       | 195,917    | 195,917   | 195,917   | 195,917   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r3 | 12   | 424   | 200,274       | 200,274    | 200,274   | 200,274   | 200,274   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r1 | 14   | 424   | 366,273       | 366,273    | 366,273   | 366,273   | 366,273   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r2 | 14   | 424   | 391,680       | 391,680    | 391,680   | 391,680   | 391,680   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r3 | 14   | 424   | 393,756       | 393,756    | 393,756   | 393,756   | 393,756   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r1     | 12   | 416   | 31,095        | 31,095     | 31,095    | 31,095    | 31,095    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r2     | 12   | 423   | 33,048        | 33,048     | 33,048    | 33,048    | 33,048    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r3     | 12   | 418   | 26,594        | 26,594     | 26,594    | 26,594    | 26,594    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r1     | 14   | 421   | 72,234        | 72,234     | 72,234    | 72,234    | 72,234    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r2     | 14   | 424   | 102,844       | 102,844    | 102,844   | 102,844   | 102,844   | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r3     | 14   | 420   | 63,911        | 63,911     | 63,911    | 63,911    | 63,911    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |

Datasets won, tied and lost by each track against each ASTRAL (best run of each):

| comparison         | BEAT | TIE | BEHIND |
|--------------------|------|-----|--------|
| cold vs ASTRAL-III | 1    | 12  | 0      |
| cold vs ASTRAL-IV  | 0    | 13  | 0      |
| warm vs ASTRAL-III | 1    | 12  | 0      |
| warm vs ASTRAL-IV  | 0    | 13  | 0      |

## 2. Subsampled datasets with known optimum

Each cell counts the instances where that method's best run reached the exact optimum.

| group            | instances | with exact optimum | ASTRAL-III optimal | ASTRAL-IV optimal | ours warm optimal | ours cold optimal | instances where we beat both ASTRALs |
|------------------|-----------|--------------------|--------------------|-------------------|-------------------|-------------------|--------------------------------------|
| 1kp, 12 taxa     | 3         | 3                  | 3 / 3              | 3 / 3             | 3 / 3             | 3 / 3             | 0                                    |
| 1kp, 14 taxa     | 3         | 3                  | 3 / 3              | 3 / 3             | 3 / 3             | 3 / 3             | 0                                    |
| mammals, 12 taxa | 3         | 3                  | 3 / 3              | 3 / 3             | 3 / 3             | 3 / 3             | 0                                    |
| mammals, 14 taxa | 3         | 3                  | 3 / 3              | 3 / 3             | 3 / 3             | 3 / 3             | 0                                    |

## 3. Methods across all datasets

One row per method. W/T/L compares the method's best run on each dataset with the better ASTRAL. Gap is the average shortfall from the best score any method found, over all runs. Optimal counts runs on datasets with a known optimum.

| track    | method                       | datasets | runs | W / T / L vs ASTRAL | runs >= ASTRAL | runs optimal | mean gap to best | median time to best | median run time |
|----------|------------------------------|----------|------|---------------------|----------------|--------------|------------------|---------------------|-----------------|
| baseline | ASTRAL-III                   | 13       | 26   | 0 / 12 / 1          | 24 / 26        | 24 / 26      | 0.0232%          |                     | 0.59 s          |
| baseline | ASTRAL-III exact             | 13       | 13   | 0 / 13 / 0          | 13 / 13        | 13 / 13      | 0.0000%          |                     | 4.60 s          |
| baseline | ASTRAL-IV                    | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          |                     | 0.19 s          |
| warm     | anneal / astral3             | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 2.71 s          |
| warm     | dp / astral3                 | 13       | 26   | 0 / 13 / 0          | 25 / 26        | 25 / 26      | 0.0040%          | 0.00 s              | 0.01 s          |
| warm     | pairswap-first / astral3     | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.01 s          |
| warm     | vnd / astral3                | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | anneal / caterpillar         | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 2.71 s          |
| cold     | anneal / greedy              | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 2.71 s          |
| cold     | anneal / random              | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.01 s              | 2.71 s          |
| cold     | dp / caterpillar             | 13       | 13   | 0 / 10 / 3          | 10 / 13        | 10 / 13      | 0.1558%          | 0.00 s              | 0.01 s          |
| cold     | dp / greedy                  | 13       | 26   | 0 / 12 / 1          | 22 / 26        | 22 / 26      | 0.1041%          | 0.00 s              | 0.01 s          |
| cold     | dp / random                  | 13       | 26   | 0 / 0 / 13          | 0 / 26         | 0 / 26       | 49.0970%         | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / caterpillar | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / greedy      | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / random      | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.01 s          |
| cold     | vnd / caterpillar            | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | vnd / greedy                 | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | vnd / random                 | 13       | 26   | 0 / 13 / 0          | 26 / 26        | 26 / 26      | 0.0000%          | 0.00 s              | 0.02 s          |

## 5. Checks

All scorers agree, no result exceeds an exact optimum, and every run finished.
