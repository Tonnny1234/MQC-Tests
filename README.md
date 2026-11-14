# mqc-bench

Search over circular orders with an exact O(M + n³) dynamic program per order, benchmarked against the
official ASTRAL-III and ASTRAL-IV on ASTRAL's own datasets.

Everything here was built and run before packaging: the 13-test suite passes, and on every dataset tried
our scorer gives exactly the quartet score that ASTRAL-III and ASTRAL-IV print (see "What was measured").
