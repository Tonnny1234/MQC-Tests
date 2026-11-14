# Extra datasets

The three real datasets that ship with ASTRAL (mammals, 1KP, 1KP-BS10) need nothing here: `setup.sh`
downloads them into `ext/ASTRAL/Astral/test_data/`.

To add the larger published datasets, download the gene trees and save them in this folder under the
names below. Each file is plain Newick, one gene tree per line. `configs/stageA.json` and
`configs/stageB.json` already list these names and skip any that are missing.

| Save as                 | Dataset                                   | Where to get it |
|-------------------------|-------------------------------------------|-----------------|
| `data/avian_tent.tre`   | Avian, Jarvis et al. 2014: 48 taxa, 14,446 gene trees | Dryad doi:10.6076/D16W2H (ASTRAL-MP data) |
| `data/avian_uce.tre`    | Avian UCE loci: 48 taxa, 3,679 gene trees | Jarvis et al. 2014 data release |
| `data/angiosperms.tre`  | Angiosperms, Xi et al. 2014: 46 taxa, 310 gene trees | Dryad doi:10.6076/D10C7C (ASTRAL-II data) |
| `data/insects.tre`      | Insects, Misof et al. 2014: 144 taxa      | Dryad doi:10.6076/D14599 (ASTRAL-MP data) |

These archives were not opened while this package was written, so check the taxon and gene counts after
downloading:

    bin/mqc info --genes data/avian_tent.tre

Requirements for any gene-tree file: every taxon appears at most once per tree (multi-copy gene trees are
skipped), and names contain no spaces, commas, colons, semicolons or parentheses. Use best-estimate gene
trees, not bootstrap replicates. The explicit quartet table limits this engine to about 150 taxa.
