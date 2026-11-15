# Benchmark report: stageB

Generated 2026-11-15 00:19. 5 datasets, 389 runs (389 finished, 0 unfinished or failed).

Every score is the quartet score from one scorer (mqc score). Cross-checks: 37 ASTRAL runs compared with the score ASTRAL printed, 0 of our trees re-scored with ASTRAL-III -q; 0 disagreements.

## 1. Overview: best score per dataset

Warm = our search started from ASTRAL's tree. Cold = started from our own orders, no ASTRAL input. Each ASTRAL column is its best run over seeds. 'yes' under optimal means the exact optimum was reached.

| dataset     | taxa | genes | exact optimum | ASTRAL-III  | ASTRAL-IV     | ours warm   | ours cold   | our best vs ASTRAL-III | our best vs ASTRAL-IV | optimal? |
|-------------|------|-------|---------------|-------------|---------------|-------------|-------------|------------------------|-----------------------|----------|
| mammals     | 37   | 424   |               | 25,526,915  | 25,526,915    | 25,526,915  | 25,526,915  | TIE                    | TIE                   |          |
| angiosperms | 46   | 310   |               | 11,553,053  | 11,553,053    | 11,553,053  | 11,553,053  | TIE                    | TIE                   |          |
| avian-tent  | 48   | 14446 |               |             | 1,231,992,828 |             |             |                        |                       |          |
| 1kp         | 103  | 424   |               | 339,023,690 | 339,023,690   | 339,023,690 | 339,023,690 | TIE                    | TIE                   |          |
| 1kp-bs10    | 103  | 424   |               | 326,972,173 | 326,972,173   | 326,972,173 | 326,972,173 | TIE                    | TIE                   |          |

Datasets won, tied and lost by each track against each ASTRAL (best run of each):

| comparison         | BEAT | TIE | BEHIND |
|--------------------|------|-----|--------|
| cold vs ASTRAL-III | 0    | 4   | 0      |
| cold vs ASTRAL-IV  | 0    | 4   | 0      |
| warm vs ASTRAL-III | 0    | 4   | 0      |
| warm vs ASTRAL-IV  | 0    | 4   | 0      |

## 3. Methods across all datasets

One row per method. W/T/L compares the method's best run on each dataset with the better ASTRAL. Gap is the average shortfall from the best score any method found, over all runs. Optimal counts runs on datasets with a known optimum.

| track    | method                | datasets | runs | W / T / L vs ASTRAL | runs >= ASTRAL | runs optimal | mean gap to best | median time to best | median run time |
|----------|-----------------------|----------|------|---------------------|----------------|--------------|------------------|---------------------|-----------------|
| baseline | ASTRAL-III            | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          |                     | 18 s            |
| baseline | ASTRAL-IV             | 5        | 15   | 0 / 5 / 0           | 15 / 15        |              | 0.0000%          |                     | 47 s            |
| baseline | ASTRAL-IV -R          | 5        | 10   | 0 / 5 / 0           | 10 / 10        |              | 0.0000%          |                     | 137 s           |
| warm     | anneal / astral3      | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 1.0 h           |
| warm     | anneal / astral4      | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 1.0 h           |
| warm     | dp / astral3          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.05 s              | 0.07 s          |
| warm     | dp / astral4          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.05 s              | 0.07 s          |
| warm     | ils / astral3         | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.08 s              | 1.0 h           |
| warm     | ils / astral4         | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.07 s              | 1.0 h           |
| warm     | multistart / astral3  | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 1.0 h           |
| warm     | multistart / astral4  | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 1.0 h           |
| warm     | vnd / astral3         | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 0.5 h           |
| warm     | vnd / astral4         | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.06 s              | 0.5 h           |
| cold     | anneal / distance     | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.21 s              | 1.0 h           |
| cold     | anneal / genetree     | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.8 h               | 1.0 h           |
| cold     | anneal / greedy       | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.8 h               | 1.0 h           |
| cold     | anneal / random       | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.6 h               | 1.0 h           |
| cold     | dp / distance         | 4        | 4    | 0 / 2 / 2           | 2 / 4          |              | 0.0468%          | 0.08 s              | 0.09 s          |
| cold     | dp / genetree         | 4        | 12   | 0 / 0 / 4           | 0 / 12         |              | 5.9336%          | 0.04 s              | 0.06 s          |
| cold     | dp / greedy           | 4        | 12   | 0 / 2 / 2           | 4 / 12         |              | 0.0263%          | 0.06 s              | 0.08 s          |
| cold     | dp / random           | 4        | 12   | 0 / 0 / 4           | 0 / 12         |              | 57.4055%         | 0.07 s              | 0.09 s          |
| cold     | ils / distance        | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.12 s              | 1.0 h           |
| cold     | ils / genetree        | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 20 s                | 1.0 h           |
| cold     | ils / greedy          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.63 s              | 1.0 h           |
| cold     | ils / random          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 40 s                | 1.0 h           |
| cold     | multistart / distance | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.13 s              | 1.0 h           |
| cold     | multistart / genetree | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 28 s                | 1.0 h           |
| cold     | multistart / greedy   | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.71 s              | 1.0 h           |
| cold     | multistart / random   | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 41 s                | 1.0 h           |
| cold     | vnd / distance        | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.11 s              | 0.5 h           |
| cold     | vnd / genetree        | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 21 s                | 0.5 h           |
| cold     | vnd / greedy          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 0.77 s              | 0.5 h           |
| cold     | vnd / random          | 4        | 12   | 0 / 4 / 0           | 12 / 12        |              | 0.0000%          | 38 s                | 0.5 h           |

## 4. Detail per dataset

mammals: 37 taxa, 424 gene trees. Best known score 25,526,915; better ASTRAL 25,526,915.

| track    | method                | runs | best       | median     | worst      | best vs ASTRAL     | median time to best | median run time | RF to ASTRAL-III tree |
|----------|-----------------------|------|------------|------------|------------|--------------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III            | 3    | 25,526,915 | 25,526,915 | 25,526,915 |                    |                     | 2.86 s          |                       |
| baseline | ASTRAL-IV             | 3    | 25,526,915 | 25,526,915 | 25,526,915 |                    |                     | 10 s            |                       |
| baseline | ASTRAL-IV -R          | 2    | 25,526,915 | 25,526,915 | 25,526,915 |                    |                     | 38 s            |                       |
| warm     | anneal / astral3      | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.9 h           | 0                     |
| warm     | anneal / astral4      | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.9 h           | 0                     |
| warm     | dp / astral3          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.01 s          | 0                     |
| warm     | dp / astral4          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.01 s          | 0                     |
| warm     | ils / astral3         | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| warm     | ils / astral4         | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| warm     | multistart / astral3  | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| warm     | multistart / astral4  | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| warm     | vnd / astral3         | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 5.28 s          | 0                     |
| warm     | vnd / astral4         | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 5.37 s          | 0                     |
| cold     | anneal / distance     | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.01 s              | 0.9 h           | 0                     |
| cold     | anneal / genetree     | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.5 h               | 0.9 h           | 0                     |
| cold     | anneal / greedy       | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.9 h           | 0                     |
| cold     | anneal / random       | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.2 h               | 0.9 h           | 0                     |
| cold     | dp / distance         | 1    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.01 s              | 0.02 s          | 0                     |
| cold     | dp / genetree         | 3    | 25,521,518 | 25,483,609 | 25,237,635 | BEHIND -5,397      | 0.00 s              | 0.01 s          | 2                     |
| cold     | dp / greedy           | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 0.01 s          | 0                     |
| cold     | dp / random           | 3    | 11,378,547 | 11,004,014 | 10,586,976 | BEHIND -14,148,368 | 0.00 s              | 0.01 s          | 68                    |
| cold     | ils / distance        | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.01 s              | 1.0 h           | 0                     |
| cold     | ils / genetree        | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.02 s              | 1.0 h           | 0                     |
| cold     | ils / greedy          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| cold     | ils / random          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.11 s              | 1.0 h           | 0                     |
| cold     | multistart / distance | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.01 s              | 1.0 h           | 0                     |
| cold     | multistart / genetree | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.02 s              | 1.0 h           | 0                     |
| cold     | multistart / greedy   | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 1.0 h           | 0                     |
| cold     | multistart / random   | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.10 s              | 1.0 h           | 0                     |
| cold     | vnd / distance        | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.01 s              | 5.34 s          | 0                     |
| cold     | vnd / genetree        | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.02 s              | 5.36 s          | 0                     |
| cold     | vnd / greedy          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.00 s              | 5.26 s          | 0                     |
| cold     | vnd / random          | 3    | 25,526,915 | 25,526,915 | 25,526,915 | TIE                | 0.13 s              | 6.47 s          | 0                     |

angiosperms: 46 taxa, 310 gene trees. Best known score 11,553,053; better ASTRAL 11,553,053.

| track    | method                | runs | best       | median     | worst      | best vs ASTRAL    | median time to best | median run time | RF to ASTRAL-III tree |
|----------|-----------------------|------|------------|------------|------------|-------------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III            | 3    | 11,553,053 | 11,553,053 | 11,553,053 |                   |                     | 5.15 s          |                       |
| baseline | ASTRAL-IV             | 3    | 11,553,053 | 11,553,053 | 11,553,053 |                   |                     | 5.49 s          |                       |
| baseline | ASTRAL-IV -R          | 2    | 11,553,053 | 11,553,053 | 11,553,053 |                   |                     | 22 s            |                       |
| warm     | anneal / astral3      | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 0.9 h           | 0                     |
| warm     | anneal / astral4      | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 0.9 h           | 0                     |
| warm     | dp / astral3          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 0.01 s          | 0                     |
| warm     | dp / astral4          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 0.02 s          | 0                     |
| warm     | ils / astral3         | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 1.0 h           | 0                     |
| warm     | ils / astral4         | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 1.0 h           | 0                     |
| warm     | multistart / astral3  | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 1.0 h           | 0                     |
| warm     | multistart / astral4  | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 1.0 h           | 0                     |
| warm     | vnd / astral3         | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 21 s            | 0                     |
| warm     | vnd / astral4         | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.00 s              | 21 s            | 0                     |
| cold     | anneal / distance     | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.7 h               | 0.9 h           | 0                     |
| cold     | anneal / genetree     | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.7 h               | 0.9 h           | 0                     |
| cold     | anneal / greedy       | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.7 h               | 0.9 h           | 0                     |
| cold     | anneal / random       | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.4 h               | 0.9 h           | 0                     |
| cold     | dp / distance         | 1    | 11,546,946 | 11,546,946 | 11,546,946 | BEHIND -6,107     | 0.01 s              | 0.02 s          | 6                     |
| cold     | dp / genetree         | 3    | 10,875,137 | 10,716,757 | 10,610,337 | BEHIND -677,916   | 0.00 s              | 0.01 s          | 56                    |
| cold     | dp / greedy           | 3    | 11,553,053 | 11,551,299 | 11,542,011 | TIE               | 0.00 s              | 0.02 s          | 0                     |
| cold     | dp / random           | 3    | 5,974,375  | 5,338,288  | 5,282,833  | BEHIND -5,578,678 | 0.00 s              | 0.01 s          | 86                    |
| cold     | ils / distance        | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.06 s              | 1.0 h           | 0                     |
| cold     | ils / genetree        | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.36 s              | 1.0 h           | 0                     |
| cold     | ils / greedy          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.03 s              | 1.0 h           | 0                     |
| cold     | ils / random          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.53 s              | 1.0 h           | 0                     |
| cold     | multistart / distance | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.06 s              | 1.0 h           | 0                     |
| cold     | multistart / genetree | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.35 s              | 1.0 h           | 0                     |
| cold     | multistart / greedy   | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.03 s              | 1.0 h           | 0                     |
| cold     | multistart / random   | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.66 s              | 1.0 h           | 0                     |
| cold     | vnd / distance        | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.06 s              | 21 s            | 0                     |
| cold     | vnd / genetree        | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.33 s              | 22 s            | 0                     |
| cold     | vnd / greedy          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.04 s              | 29 s            | 0                     |
| cold     | vnd / random          | 3    | 11,553,053 | 11,553,053 | 11,553,053 | TIE               | 0.53 s              | 22 s            | 0                     |

avian-tent: 48 taxa, 14446 gene trees. Best known score 1,231,992,828; better ASTRAL 1,231,992,828.

| track    | method       | runs | best          | median        | worst         | best vs ASTRAL | median time to best | median run time | RF to ASTRAL-III tree |
|----------|--------------|------|---------------|---------------|---------------|----------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-IV    | 3    | 1,231,992,828 | 1,231,992,828 | 1,231,992,828 |                |                     | 0.5 h           |                       |
| baseline | ASTRAL-IV -R | 2    | 1,231,992,828 | 1,231,992,828 | 1,231,992,828 |                |                     | 1.9 h           |                       |

1kp: 103 taxa, 424 gene trees. Best known score 339,023,690; better ASTRAL 339,023,690.

| track    | method                | runs | best        | median      | worst       | best vs ASTRAL      | median time to best | median run time | RF to ASTRAL-III tree |
|----------|-----------------------|------|-------------|-------------|-------------|---------------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III            | 3    | 339,023,690 | 339,023,690 | 339,023,690 |                     |                     | 44 s            |                       |
| baseline | ASTRAL-IV             | 3    | 339,023,690 | 339,023,690 | 339,023,690 |                     |                     | 49 s            |                       |
| baseline | ASTRAL-IV -R          | 2    | 339,023,690 | 339,023,690 | 339,023,690 |                     |                     | 192 s           |                       |
| warm     | anneal / astral3      | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| warm     | anneal / astral4      | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| warm     | dp / astral3          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.15 s              | 0.17 s          | 0                     |
| warm     | dp / astral4          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.15 s              | 0.17 s          | 0                     |
| warm     | ils / astral3         | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.16 s              | 1.0 h           | 0                     |
| warm     | ils / astral4         | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.17 s              | 1.0 h           | 0                     |
| warm     | multistart / astral3  | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.11 s              | 1.0 h           | 0                     |
| warm     | multistart / astral4  | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| warm     | vnd / astral3         | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.15 s              | 1.0 h           | 0                     |
| warm     | vnd / astral4         | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| cold     | anneal / distance     | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | anneal / genetree     | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | anneal / greedy       | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | anneal / random       | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 0.8 h               | 1.0 h           | 0                     |
| cold     | dp / distance         | 1    | 338,567,773 | 338,567,773 | 338,567,773 | BEHIND -455,917     | 0.17 s              | 0.20 s          | 2                     |
| cold     | dp / genetree         | 3    | 314,641,559 | 310,649,192 | 305,509,145 | BEHIND -24,382,131  | 0.16 s              | 0.18 s          | 130                   |
| cold     | dp / greedy           | 3    | 339,016,685 | 339,011,063 | 338,718,317 | BEHIND -7,005       | 0.24 s              | 0.27 s          | 10                    |
| cold     | dp / random           | 3    | 139,274,361 | 136,578,826 | 133,561,128 | BEHIND -199,749,329 | 0.15 s              | 0.17 s          | 198                   |
| cold     | ils / distance        | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 2.96 s              | 1.0 h           | 0                     |
| cold     | ils / genetree        | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 82 s                | 1.0 h           | 0                     |
| cold     | ils / greedy          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 5.34 s              | 1.0 h           | 0                     |
| cold     | ils / random          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 83 s                | 1.0 h           | 0                     |
| cold     | multistart / distance | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 3.95 s              | 1.0 h           | 0                     |
| cold     | multistart / genetree | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 75 s                | 1.0 h           | 0                     |
| cold     | multistart / greedy   | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 5.30 s              | 1.0 h           | 0                     |
| cold     | multistart / random   | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 85 s                | 1.0 h           | 0                     |
| cold     | vnd / distance        | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 2.97 s              | 1.0 h           | 0                     |
| cold     | vnd / genetree        | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 57 s                | 1.0 h           | 0                     |
| cold     | vnd / greedy          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 4.20 s              | 1.0 h           | 0                     |
| cold     | vnd / random          | 3    | 339,023,690 | 339,023,690 | 339,023,690 | TIE                 | 88 s                | 1.0 h           | 0                     |

1kp-bs10: 103 taxa, 424 gene trees. Best known score 326,972,173; better ASTRAL 326,972,173.

| track    | method                | runs | best        | median      | worst       | best vs ASTRAL      | median time to best | median run time | RF to ASTRAL-III tree |
|----------|-----------------------|------|-------------|-------------|-------------|---------------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III            | 3    | 326,972,173 | 326,972,173 | 326,972,173 |                     |                     | 38 s            |                       |
| baseline | ASTRAL-IV             | 3    | 326,972,173 | 326,972,173 | 326,972,173 |                     |                     | 54 s            |                       |
| baseline | ASTRAL-IV -R          | 2    | 326,972,173 | 326,972,173 | 326,972,173 |                     |                     | 137 s           |                       |
| warm     | anneal / astral3      | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| warm     | anneal / astral4      | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.12 s              | 1.0 h           | 0                     |
| warm     | dp / astral3          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.10 s              | 0.12 s          | 0                     |
| warm     | dp / astral4          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.12 s              | 0.14 s          | 0                     |
| warm     | ils / astral3         | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.16 s              | 1.0 h           | 0                     |
| warm     | ils / astral4         | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.16 s              | 1.0 h           | 0                     |
| warm     | multistart / astral3  | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.11 s              | 1.0 h           | 0                     |
| warm     | multistart / astral4  | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.13 s              | 1.0 h           | 0                     |
| warm     | vnd / astral3         | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.16 s              | 1.0 h           | 0                     |
| warm     | vnd / astral4         | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.17 s              | 1.0 h           | 0                     |
| cold     | anneal / distance     | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.21 s              | 1.0 h           | 0                     |
| cold     | anneal / genetree     | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | anneal / greedy       | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | anneal / random       | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.9 h               | 1.0 h           | 0                     |
| cold     | dp / distance         | 1    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.15 s              | 0.17 s          | 0                     |
| cold     | dp / genetree         | 3    | 307,175,877 | 300,246,667 | 297,748,710 | BEHIND -19,796,296  | 0.08 s              | 0.10 s          | 122                   |
| cold     | dp / greedy           | 3    | 326,965,758 | 326,965,214 | 326,627,614 | BEHIND -6,415       | 0.17 s              | 0.19 s          | 12                    |
| cold     | dp / random           | 3    | 130,959,033 | 128,167,921 | 125,291,226 | BEHIND -196,013,140 | 0.16 s              | 0.18 s          | 198                   |
| cold     | ils / distance        | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.16 s              | 1.0 h           | 0                     |
| cold     | ils / genetree        | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 61 s                | 1.0 h           | 0                     |
| cold     | ils / greedy          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 5.76 s              | 1.0 h           | 0                     |
| cold     | ils / random          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 102 s               | 1.0 h           | 0                     |
| cold     | multistart / distance | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.20 s              | 1.0 h           | 0                     |
| cold     | multistart / genetree | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 71 s                | 1.0 h           | 0                     |
| cold     | multistart / greedy   | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 7.40 s              | 1.0 h           | 0                     |
| cold     | multistart / random   | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 101 s               | 1.0 h           | 0                     |
| cold     | vnd / distance        | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 0.14 s              | 1.0 h           | 0                     |
| cold     | vnd / genetree        | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 75 s                | 1.0 h           | 0                     |
| cold     | vnd / greedy          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 5.96 s              | 1.0 h           | 0                     |
| cold     | vnd / random          | 3    | 326,972,173 | 326,972,173 | 326,972,173 | TIE                 | 83 s                | 1.0 h           | 0                     |

## 5. Checks

All scorers agree, no result exceeds an exact optimum, and every run finished.
