# Benchmark report: stageA

Generated 2026-11-14 03:51. 152 datasets, 47861 runs (47861 finished, 0 unfinished or failed).

Every score is the quartet score from one scorer (mqc score). Cross-checks: 1197 ASTRAL runs compared with the score ASTRAL printed, 304 of our trees re-scored with ASTRAL-III -q; 0 disagreements.

## 1. Overview: best score per dataset

Warm = our search started from ASTRAL's tree. Cold = started from our own orders, no ASTRAL input. Each ASTRAL column is its best run over seeds. 'yes' under optimal means the exact optimum was reached.

| dataset             | taxa | genes | exact optimum | ASTRAL-III | ASTRAL-IV  | ours warm  | ours cold  | our best vs ASTRAL-III | our best vs ASTRAL-IV | optimal?                                          |
|---------------------|------|-------|---------------|------------|------------|------------|------------|------------------------|-----------------------|---------------------------------------------------|
| sim14               | 14   | 10    | 4,812         | 4,803      | 4,812      | 4,812      | 4,812      | BEAT +9                | TIE                   | ASTRAL-III no, ASTRAL-IV yes, warm yes, cold yes  |
| primates            | 14   | 424   | 389,734       | 389,734    | 389,734    | 389,734    | 389,734    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r1      | 12   | 424   | 194,611       | 194,611    | 194,611    | 194,611    | 194,611    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r2      | 12   | 424   | 195,917       | 195,917    | 195,917    | 195,917    | 195,917    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r3      | 12   | 424   | 200,274       | 200,274    | 200,274    | 200,274    | 200,274    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r4      | 12   | 424   | 199,817       | 199,817    | 199,817    | 199,817    | 199,817    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r5      | 12   | 424   | 194,218       | 194,218    | 194,218    | 194,218    | 194,218    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r6      | 12   | 424   | 190,659       | 190,659    | 190,659    | 190,659    | 190,659    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r7      | 12   | 424   | 198,201       | 198,201    | 198,201    | 198,201    | 198,201    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r8      | 12   | 424   | 194,083       | 194,083    | 194,083    | 194,083    | 194,083    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r9      | 12   | 424   | 195,330       | 195,330    | 195,330    | 195,330    | 195,330    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n12.r10     | 12   | 424   | 186,334       | 186,334    | 186,334    | 186,334    | 186,334    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r1      | 14   | 424   | 366,273       | 366,273    | 366,273    | 366,273    | 366,273    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r2      | 14   | 424   | 391,680       | 391,680    | 391,680    | 391,680    | 391,680    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r3      | 14   | 424   | 393,756       | 393,756    | 393,756    | 393,756    | 393,756    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r4      | 14   | 424   | 376,561       | 376,561    | 376,561    | 376,561    | 376,561    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r5      | 14   | 424   | 375,173       | 375,173    | 375,173    | 375,173    | 375,173    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r6      | 14   | 424   | 375,783       | 375,783    | 375,783    | 375,783    | 375,783    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r7      | 14   | 424   | 384,012       | 384,012    | 384,012    | 384,012    | 384,012    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r8      | 14   | 424   | 393,900       | 393,900    | 393,900    | 393,900    | 393,900    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r9      | 14   | 424   | 403,242       | 403,242    | 403,242    | 403,242    | 403,242    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n14.r10     | 14   | 424   | 402,471       | 402,471    | 402,471    | 402,471    | 402,471    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r1      | 16   | 424   | 703,796       | 703,796    | 703,796    | 703,796    | 703,796    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r2      | 16   | 424   | 714,967       | 714,967    | 714,967    | 714,967    | 714,967    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r3      | 16   | 424   | 716,634       | 716,634    | 716,634    | 716,634    | 716,634    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r4      | 16   | 424   | 697,440       | 697,440    | 697,440    | 697,440    | 697,440    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r5      | 16   | 424   | 709,405       | 709,405    | 709,405    | 709,405    | 709,405    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r6      | 16   | 424   | 722,973       | 722,973    | 722,973    | 722,973    | 722,973    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r7      | 16   | 424   | 724,824       | 724,824    | 724,824    | 724,824    | 724,824    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r8      | 16   | 424   | 707,376       | 707,376    | 707,376    | 707,376    | 707,376    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r9      | 16   | 424   | 702,115       | 702,115    | 702,115    | 702,115    | 702,115    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| mammals.n16.r10     | 16   | 424   | 703,279       | 703,279    | 703,279    | 703,279    | 703,279    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r1          | 12   | 416   | 31,095        | 31,095     | 31,095     | 31,095     | 31,095     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r2          | 12   | 423   | 33,048        | 33,048     | 33,048     | 33,048     | 33,048     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r3          | 12   | 418   | 26,594        | 26,594     | 26,594     | 26,594     | 26,594     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r4          | 12   | 421   | 39,141        | 39,141     | 39,141     | 39,141     | 39,141     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r5          | 12   | 415   | 34,097        | 34,097     | 34,097     | 34,097     | 34,097     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r6          | 12   | 411   | 39,008        | 39,008     | 39,008     | 39,008     | 39,008     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r7          | 12   | 398   | 17,649        | 17,649     | 17,649     | 17,649     | 17,649     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r8          | 12   | 424   | 33,640        | 33,640     | 33,640     | 33,640     | 33,640     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r9          | 12   | 420   | 38,226        | 38,226     | 38,226     | 38,226     | 38,226     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n12.r10         | 12   | 422   | 21,546        | 21,546     | 21,546     | 21,546     | 21,546     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r1          | 14   | 421   | 72,234        | 72,234     | 72,234     | 72,234     | 72,234     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r2          | 14   | 424   | 102,844       | 102,844    | 102,844    | 102,844    | 102,844    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r3          | 14   | 420   | 63,911        | 63,911     | 63,911     | 63,911     | 63,911     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r4          | 14   | 424   | 71,156        | 71,156     | 71,156     | 71,156     | 71,156     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r5          | 14   | 423   | 75,957        | 75,957     | 75,957     | 75,957     | 75,957     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r6          | 14   | 424   | 91,941        | 91,941     | 91,941     | 91,941     | 91,941     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r7          | 14   | 424   | 112,147       | 112,147    | 112,147    | 112,147    | 112,147    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r8          | 14   | 417   | 50,220        | 50,220     | 50,220     | 50,220     | 50,220     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r9          | 14   | 424   | 95,100        | 95,100     | 95,100     | 95,100     | 95,100     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n14.r10         | 14   | 423   | 76,018        | 76,018     | 76,018     | 76,018     | 76,018     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r1          | 16   | 424   | 162,885       | 162,885    | 162,885    | 162,885    | 162,885    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r2          | 16   | 423   | 75,154        | 75,154     | 75,154     | 75,154     | 75,154     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r3          | 16   | 423   | 142,514       | 142,514    | 142,514    | 142,514    | 142,514    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r4          | 16   | 424   | 155,547       | 155,547    | 155,547    | 155,547    | 155,547    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r5          | 16   | 424   | 199,894       | 199,894    | 199,894    | 199,894    | 199,894    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r6          | 16   | 423   | 106,046       | 106,046    | 106,046    | 106,046    | 106,046    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r7          | 16   | 424   | 151,496       | 151,496    | 151,496    | 151,496    | 151,496    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r8          | 16   | 424   | 166,477       | 166,477    | 166,477    | 166,477    | 166,477    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r9          | 16   | 423   | 132,308       | 132,308    | 132,308    | 132,308    | 132,308    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp.n16.r10         | 16   | 424   | 148,219       | 148,219    | 148,219    | 148,219    | 148,219    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r1     | 12   | 416   | 30,095        | 30,095     | 30,095     | 30,095     | 30,095     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r2     | 12   | 423   | 31,641        | 31,641     | 31,641     | 31,641     | 31,641     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r3     | 12   | 418   | 25,696        | 25,696     | 25,696     | 25,696     | 25,696     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r4     | 12   | 421   | 38,025        | 38,025     | 38,025     | 38,025     | 38,025     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r5     | 12   | 415   | 32,168        | 32,168     | 32,168     | 32,168     | 32,168     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r6     | 12   | 411   | 37,118        | 37,118     | 37,118     | 37,118     | 37,118     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r7     | 12   | 398   | 17,228        | 17,228     | 17,228     | 17,228     | 17,228     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r8     | 12   | 424   | 31,859        | 31,859     | 31,859     | 31,859     | 31,859     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r9     | 12   | 420   | 36,515        | 36,515     | 36,515     | 36,515     | 36,515     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n12.r10    | 12   | 422   | 20,956        | 20,956     | 20,956     | 20,956     | 20,956     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r1     | 14   | 421   | 68,783        | 68,783     | 68,783     | 68,783     | 68,783     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r2     | 14   | 424   | 100,034       | 100,034    | 100,034    | 100,034    | 100,034    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r3     | 14   | 420   | 61,664        | 61,664     | 61,664     | 61,664     | 61,664     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r4     | 14   | 424   | 69,024        | 69,024     | 69,024     | 69,024     | 69,024     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r5     | 14   | 423   | 73,420        | 73,420     | 73,420     | 73,420     | 73,420     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r6     | 14   | 424   | 87,875        | 87,875     | 87,875     | 87,875     | 87,875     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r7     | 14   | 424   | 108,666       | 108,666    | 108,666    | 108,666    | 108,666    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r8     | 14   | 417   | 47,022        | 47,022     | 47,022     | 47,022     | 47,022     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r9     | 14   | 424   | 92,262        | 92,262     | 92,262     | 92,262     | 92,262     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n14.r10    | 14   | 423   | 73,352        | 73,352     | 73,352     | 73,352     | 73,352     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r1     | 16   | 424   | 156,356       | 156,356    | 156,356    | 156,356    | 156,356    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r2     | 16   | 423   | 72,071        | 72,071     | 72,071     | 72,071     | 72,071     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r3     | 16   | 423   | 138,910       | 138,910    | 138,910    | 138,910    | 138,910    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r4     | 16   | 424   | 151,799       | 151,799    | 151,799    | 151,799    | 151,799    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r5     | 16   | 424   | 191,049       | 191,049    | 191,049    | 191,049    | 191,049    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r6     | 16   | 423   | 101,004       | 101,004    | 101,004    | 101,004    | 101,004    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r7     | 16   | 424   | 145,922       | 145,922    | 145,922    | 145,922    | 145,922    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r8     | 16   | 424   | 162,312       | 162,312    | 162,312    | 162,312    | 162,312    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r9     | 16   | 423   | 127,473       | 127,473    | 127,473    | 127,473    | 127,473    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| 1kp-bs10.n16.r10    | 16   | 424   | 142,130       | 142,130    | 142,130    | 142,130    | 142,130    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r1   | 12   | 14446 | 3,374,563     | 3,374,563  | 3,374,563  | 3,374,563  | 3,374,563  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r2   | 12   | 14446 | 2,811,717     | 2,811,717  | 2,811,717  | 2,811,717  | 2,811,717  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r3   | 12   | 14446 | 3,767,921     | 3,767,921  | 3,767,921  | 3,767,921  | 3,767,921  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r4   | 12   | 14446 | 2,694,607     | 2,694,607  | 2,694,607  | 2,694,607  | 2,694,607  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r5   | 12   | 14446 | 3,069,555     | 3,069,555  | 3,069,555  | 3,069,555  | 3,069,555  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r6   | 12   | 14446 | 2,858,416     | 2,858,416  | 2,858,416  | 2,858,416  | 2,858,416  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r7   | 12   | 14446 | 2,847,261     | 2,847,261  | 2,847,261  | 2,847,261  | 2,847,261  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r8   | 12   | 14446 | 2,534,287     | 2,534,287  | 2,534,287  | 2,534,287  | 2,534,287  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r9   | 12   | 14446 | 2,822,668     | 2,822,668  | 2,822,668  | 2,822,668  | 2,822,668  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n12.r10  | 12   | 14446 | 2,590,670     | 2,590,670  | 2,590,670  | 2,590,670  | 2,590,670  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r1   | 14   | 14446 | 6,525,125     | 6,525,125  | 6,525,125  | 6,525,125  | 6,525,125  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r2   | 14   | 14446 | 6,322,186     | 6,322,186  | 6,322,186  | 6,322,186  | 6,322,186  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r3   | 14   | 14446 | 6,245,800     | 6,245,800  | 6,245,800  | 6,245,800  | 6,245,800  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r4   | 14   | 14446 | 5,981,657     | 5,981,657  | 5,981,657  | 5,981,657  | 5,981,657  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r5   | 14   | 14446 | 5,846,589     | 5,846,589  | 5,846,589  | 5,846,589  | 5,846,589  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r6   | 14   | 14446 | 5,746,440     | 5,746,440  | 5,746,440  | 5,746,440  | 5,746,440  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r7   | 14   | 14446 | 6,326,489     | 6,326,489  | 6,326,489  | 6,326,489  | 6,326,489  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r8   | 14   | 14446 | 6,481,486     | 6,481,486  | 6,481,486  | 6,481,486  | 6,481,486  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r9   | 14   | 14446 | 6,269,891     | 6,269,891  | 6,269,891  | 6,269,891  | 6,269,891  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n14.r10  | 14   | 14446 | 6,098,276     | 6,098,276  | 6,098,276  | 6,098,276  | 6,098,276  | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| avian-tent.n16.r1   | 16   | 14446 |               | 9,631,904  | 9,631,904  | 9,631,904  | 9,631,904  | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r2   | 16   | 14446 |               | 10,576,428 | 10,576,428 | 10,576,428 | 10,576,428 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r3   | 16   | 14446 |               | 14,269,076 | 14,269,076 | 14,269,076 | 14,269,076 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r4   | 16   | 14446 |               | 11,020,815 | 11,020,815 | 11,020,815 | 11,020,815 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r5   | 16   | 14446 |               | 13,676,877 | 13,676,877 | 13,676,877 | 13,676,877 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r6   | 16   | 14446 |               | 10,681,268 | 10,681,268 | 10,681,268 | 10,681,268 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r7   | 16   | 14446 |               | 12,053,714 | 12,053,714 | 12,053,714 | 12,053,714 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r8   | 16   | 14446 |               | 11,079,484 | 11,079,484 | 11,079,484 | 11,079,484 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r9   | 16   | 14446 |               | 13,160,600 | 13,160,600 | 13,160,600 | 13,160,600 | TIE                    | TIE                   |                                                   |
| avian-tent.n16.r10  | 16   | 14446 |               | 13,316,547 | 13,316,547 | 13,316,547 | 13,316,547 | TIE                    | TIE                   |                                                   |
| angiosperms.n12.r1  | 12   | 309   | 34,262        | 34,262     | 34,262     | 34,262     | 34,262     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r2  | 12   | 296   | 24,699        | 24,699     | 24,699     | 24,699     | 24,699     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r3  | 12   | 309   | 35,768        | 35,768     | 35,768     | 35,768     | 35,768     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r4  | 12   | 308   | 34,900        | 34,900     | 34,900     | 34,900     | 34,900     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r5  | 12   | 308   | 37,086        | 37,086     | 37,086     | 37,086     | 37,086     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r6  | 12   | 309   | 50,188        | 50,188     | 50,188     | 50,188     | 50,188     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r7  | 12   | 307   | 35,901        | 35,901     | 35,901     | 35,901     | 35,901     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r8  | 12   | 310   | 41,891        | 41,891     | 41,891     | 41,891     | 41,891     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r9  | 12   | 310   | 39,702        | 39,702     | 39,702     | 39,702     | 39,702     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n12.r10 | 12   | 310   | 49,088        | 49,088     | 49,088     | 49,088     | 49,088     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r1  | 14   | 310   | 94,689        | 94,689     | 94,689     | 94,689     | 94,689     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r2  | 14   | 310   | 50,168        | 50,168     | 50,168     | 50,168     | 50,168     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r3  | 14   | 310   | 94,534        | 94,534     | 94,534     | 94,534     | 94,534     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r4  | 14   | 310   | 119,520       | 119,520    | 119,520    | 119,520    | 119,520    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r5  | 14   | 309   | 75,661        | 75,661     | 75,661     | 75,661     | 75,661     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r6  | 14   | 310   | 65,084        | 65,084     | 65,084     | 65,084     | 65,084     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r7  | 14   | 310   | 50,820        | 50,820     | 50,820     | 50,820     | 50,820     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r8  | 14   | 310   | 111,535       | 111,535    | 111,535    | 111,535    | 111,535    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r9  | 14   | 310   | 91,090        | 91,090     | 91,090     | 91,090     | 91,090     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n14.r10 | 14   | 310   | 61,057        | 61,057     | 61,057     | 61,057     | 61,057     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r1  | 16   | 310   | 129,930       | 129,930    | 129,930    | 129,930    | 129,930    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r2  | 16   | 310   | 140,301       | 140,301    | 140,301    | 140,301    | 140,301    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r3  | 16   | 310   | 123,766       | 123,766    | 123,766    | 123,766    | 123,766    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r4  | 16   | 310   | 105,147       | 105,147    | 105,147    | 105,147    | 105,147    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r5  | 16   | 310   | 65,626        | 65,626     | 65,626     | 65,626     | 65,626     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r6  | 16   | 310   | 102,659       | 102,659    | 102,659    | 102,659    | 102,659    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r7  | 16   | 310   | 123,596       | 123,596    | 123,596    | 123,596    | 123,596    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r8  | 16   | 310   | 95,014        | 95,014     | 95,014     | 95,014     | 95,014     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r9  | 16   | 310   | 116,431       | 116,431    | 116,431    | 116,431    | 116,431    | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |
| angiosperms.n16.r10 | 16   | 308   | 87,573        | 87,573     | 87,573     | 87,573     | 87,573     | TIE                    | TIE                   | ASTRAL-III yes, ASTRAL-IV yes, warm yes, cold yes |

Datasets won, tied and lost by each track against each ASTRAL (best run of each):

| comparison         | BEAT | TIE | BEHIND |
|--------------------|------|-----|--------|
| cold vs ASTRAL-III | 1    | 151 | 0      |
| cold vs ASTRAL-IV  | 0    | 152 | 0      |
| warm vs ASTRAL-III | 1    | 151 | 0      |
| warm vs ASTRAL-IV  | 0    | 152 | 0      |

## 2. Subsampled datasets with known optimum

Each cell counts the instances where that method's best run reached the exact optimum.

| group                | instances | with exact optimum | ASTRAL-III optimal | ASTRAL-IV optimal | ours warm optimal | ours cold optimal | instances where we beat both ASTRALs |
|----------------------|-----------|--------------------|--------------------|-------------------|-------------------|-------------------|--------------------------------------|
| 1kp, 12 taxa         | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| 1kp, 14 taxa         | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| 1kp, 16 taxa         | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| 1kp-bs10, 12 taxa    | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| 1kp-bs10, 14 taxa    | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| 1kp-bs10, 16 taxa    | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| angiosperms, 12 taxa | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| angiosperms, 14 taxa | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| angiosperms, 16 taxa | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| avian-tent, 12 taxa  | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| avian-tent, 14 taxa  | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| avian-tent, 16 taxa  | 10        | 0                  |                    |                   |                   |                   | 0                                    |
| mammals, 12 taxa     | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| mammals, 14 taxa     | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |
| mammals, 16 taxa     | 10        | 10                 | 10 / 10            | 10 / 10           | 10 / 10           | 10 / 10           | 0                                    |

## 3. Methods across all datasets

One row per method. W/T/L compares the method's best run on each dataset with the better ASTRAL. Gap is the average shortfall from the best score any method found, over all runs. Optimal counts runs on datasets with a known optimum.

| track    | method                       | datasets | runs | W / T / L vs ASTRAL | runs >= ASTRAL | runs optimal | mean gap to best | median time to best | median run time |
|----------|------------------------------|----------|------|---------------------|----------------|--------------|------------------|---------------------|-----------------|
| baseline | ASTRAL-III                   | 152      | 447  | 0 / 151 / 1         | 444 / 447      | 423 / 426    | 0.0029%          |                     | 1.02 s          |
| baseline | ASTRAL-III exact             | 142      | 142  | 0 / 142 / 0         | 142 / 142      | 142 / 142    | 0.0000%          |                     | 53 s            |
| baseline | ASTRAL-IV                    | 152      | 456  | 0 / 152 / 0         | 455 / 456      | 425 / 426    | 0.0009%          |                     | 0.30 s          |
| baseline | ASTRAL-IV -R                 | 152      | 152  | 0 / 152 / 0         | 152 / 152      | 142 / 142    | 0.0000%          |                     | 1.16 s          |
| warm     | anneal / astral3             | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 9.02 s          |
| warm     | dp / astral3                 | 152      | 760  | 0 / 152 / 0         | 757 / 760      | 707 / 710    | 0.0004%          | 0.00 s              | 0.00 s          |
| warm     | ils / astral3                | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| warm     | multistart / astral3         | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| warm     | pairswap-best / astral3      | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.01 s          |
| warm     | pairswap-first / astral3     | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.01 s          |
| warm     | reorient / astral3           | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.01 s          |
| warm     | tabu / astral3               | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| warm     | vnd / astral3                | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | anneal / bestrandom          | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.45 s              | 9.02 s          |
| cold     | anneal / caterpillar         | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.02 s              | 9.02 s          |
| cold     | anneal / distance            | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 9.02 s          |
| cold     | anneal / genetree            | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.41 s              | 9.02 s          |
| cold     | anneal / greedy              | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 9.02 s          |
| cold     | anneal / random              | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.03 s              | 9.02 s          |
| cold     | dp / bestrandom              | 152      | 760  | 0 / 0 / 152         | 0 / 760        | 0 / 710      | 23.6027%         | 0.00 s              | 0.01 s          |
| cold     | dp / caterpillar             | 152      | 152  | 0 / 73 / 79         | 73 / 152       | 70 / 142     | 1.1322%          | 0.00 s              | 0.00 s          |
| cold     | dp / distance                | 152      | 152  | 0 / 135 / 17        | 135 / 152      | 128 / 142    | 0.0209%          | 0.00 s              | 0.01 s          |
| cold     | dp / genetree                | 152      | 760  | 0 / 76 / 76         | 149 / 760      | 149 / 710    | 5.4882%          | 0.00 s              | 0.00 s          |
| cold     | dp / greedy                  | 152      | 760  | 0 / 150 / 2         | 653 / 760      | 626 / 710    | 0.0284%          | 0.00 s              | 0.00 s          |
| cold     | dp / random                  | 152      | 760  | 0 / 0 / 152         | 0 / 760        | 0 / 710      | 42.9083%         | 0.00 s              | 0.00 s          |
| cold     | ils / bestrandom             | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | ils / caterpillar            | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | ils / distance               | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | ils / genetree               | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | ils / greedy                 | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | ils / random                 | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / bestrandom      | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / caterpillar     | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / distance        | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / genetree        | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / greedy          | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | multistart / random          | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 10 s            |
| cold     | pairswap-best / bestrandom   | 152      | 760  | 0 / 151 / 1         | 715 / 760      | 681 / 710    | 0.1040%          | 0.01 s              | 0.02 s          |
| cold     | pairswap-best / caterpillar  | 152      | 760  | 0 / 152 / 0         | 719 / 760      | 681 / 710    | 0.0268%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-best / distance     | 152      | 760  | 0 / 152 / 0         | 752 / 760      | 707 / 710    | 0.0012%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-best / genetree     | 152      | 760  | 0 / 152 / 0         | 694 / 760      | 657 / 710    | 0.1557%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-best / greedy       | 152      | 760  | 0 / 152 / 0         | 745 / 760      | 701 / 710    | 0.0041%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-best / random       | 152      | 760  | 0 / 152 / 0         | 706 / 760      | 669 / 710    | 0.1227%          | 0.01 s              | 0.02 s          |
| cold     | pairswap-first / bestrandom  | 152      | 760  | 0 / 152 / 0         | 685 / 760      | 651 / 710    | 0.1480%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / caterpillar | 152      | 760  | 0 / 152 / 0         | 710 / 760      | 678 / 710    | 0.0296%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / distance    | 152      | 760  | 0 / 152 / 0         | 752 / 760      | 707 / 710    | 0.0017%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / genetree    | 152      | 760  | 0 / 152 / 0         | 692 / 760      | 658 / 710    | 0.1667%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / greedy      | 152      | 760  | 0 / 152 / 0         | 746 / 760      | 702 / 710    | 0.0036%          | 0.00 s              | 0.01 s          |
| cold     | pairswap-first / random      | 152      | 760  | 0 / 152 / 0         | 671 / 760      | 639 / 710    | 0.2295%          | 0.00 s              | 0.01 s          |
| cold     | reorient / bestrandom        | 152      | 760  | 0 / 152 / 0         | 756 / 760      | 707 / 710    | 0.0011%          | 0.00 s              | 0.01 s          |
| cold     | reorient / caterpillar       | 152      | 760  | 0 / 152 / 0         | 758 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.01 s          |
| cold     | reorient / distance          | 152      | 760  | 0 / 151 / 1         | 754 / 760      | 709 / 710    | 0.0006%          | 0.00 s              | 0.01 s          |
| cold     | reorient / genetree          | 152      | 760  | 0 / 152 / 0         | 754 / 760      | 708 / 710    | 0.0001%          | 0.00 s              | 0.01 s          |
| cold     | reorient / greedy            | 152      | 760  | 0 / 152 / 0         | 755 / 760      | 707 / 710    | 0.0006%          | 0.00 s              | 0.01 s          |
| cold     | reorient / random            | 152      | 760  | 0 / 152 / 0         | 756 / 760      | 709 / 710    | 0.0005%          | 0.00 s              | 0.01 s          |
| cold     | tabu / bestrandom            | 152      | 760  | 0 / 152 / 0         | 743 / 760      | 698 / 710    | 0.0940%          | 0.01 s              | 10 s            |
| cold     | tabu / caterpillar           | 152      | 760  | 0 / 152 / 0         | 748 / 760      | 701 / 710    | 0.0103%          | 0.00 s              | 10 s            |
| cold     | tabu / distance              | 152      | 760  | 0 / 152 / 0         | 757 / 760      | 708 / 710    | 0.0008%          | 0.00 s              | 10 s            |
| cold     | tabu / genetree              | 152      | 760  | 0 / 152 / 0         | 744 / 760      | 697 / 710    | 0.0474%          | 0.00 s              | 10 s            |
| cold     | tabu / greedy                | 152      | 760  | 0 / 152 / 0         | 752 / 760      | 706 / 710    | 0.0014%          | 0.00 s              | 10 s            |
| cold     | tabu / random                | 152      | 760  | 0 / 152 / 0         | 744 / 760      | 699 / 710    | 0.0605%          | 0.01 s              | 10 s            |
| cold     | vnd / bestrandom             | 152      | 760  | 0 / 152 / 0         | 759 / 760      | 709 / 710    | 0.0005%          | 0.00 s              | 0.02 s          |
| cold     | vnd / caterpillar            | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | vnd / distance               | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.03 s          |
| cold     | vnd / genetree               | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | vnd / greedy                 | 152      | 760  | 0 / 152 / 0         | 760 / 760      | 710 / 710    | 0.0000%          | 0.00 s              | 0.02 s          |
| cold     | vnd / random                 | 152      | 760  | 0 / 152 / 0         | 759 / 760      | 709 / 710    | 0.0005%          | 0.00 s              | 0.02 s          |

## 4. Detail per dataset

sim14: 14 taxa, 10 gene trees. Best known score 4,812; better ASTRAL 4,812; exact optimum 4,812.

| track    | method                       | runs | best  | median | worst | best vs ASTRAL | median time to best | median run time | RF to ASTRAL-III tree |
|----------|------------------------------|------|-------|--------|-------|----------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III                   | 3    | 4,803 | 4,792  | 4,779 |                |                     | 0.51 s          |                       |
| baseline | ASTRAL-III exact             | 1    | 4,812 | 4,812  | 4,812 |                |                     | 7.16 s          |                       |
| baseline | ASTRAL-IV                    | 3    | 4,812 | 4,812  | 4,793 |                |                     | 0.02 s          |                       |
| baseline | ASTRAL-IV -R                 | 1    | 4,812 | 4,812  | 4,812 |                |                     | 0.05 s          |                       |
| warm     | anneal / astral3             | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.06 s              | 9.03 s          | 4                     |
| warm     | dp / astral3                 | 5    | 4,812 | 4,807  | 4,807 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| warm     | ils / astral3                | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| warm     | multistart / astral3         | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| warm     | pairswap-best / astral3      | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| warm     | pairswap-first / astral3     | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| warm     | reorient / astral3           | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| warm     | tabu / astral3               | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| warm     | vnd / astral3                | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | anneal / bestrandom          | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.63 s              | 9.03 s          | 4                     |
| cold     | anneal / caterpillar         | 5    | 4,812 | 4,812  | 4,812 | TIE            | 1.24 s              | 9.03 s          | 4                     |
| cold     | anneal / distance            | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.29 s              | 9.03 s          | 4                     |
| cold     | anneal / genetree            | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.81 s              | 9.03 s          | 4                     |
| cold     | anneal / greedy              | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.70 s              | 9.03 s          | 4                     |
| cold     | anneal / random              | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.17 s              | 9.02 s          | 4                     |
| cold     | dp / bestrandom              | 5    | 4,558 | 4,282  | 4,174 | BEHIND -254    | 0.00 s              | 0.01 s          | 14                    |
| cold     | dp / caterpillar             | 1    | 4,807 | 4,807  | 4,807 | BEHIND -5      | 0.00 s              | 0.00 s          | 2                     |
| cold     | dp / distance                | 1    | 4,726 | 4,726  | 4,726 | BEHIND -86     | 0.00 s              | 0.00 s          | 14                    |
| cold     | dp / genetree                | 5    | 4,441 | 4,346  | 4,245 | BEHIND -371    | 0.00 s              | 0.00 s          | 20                    |
| cold     | dp / greedy                  | 5    | 4,792 | 4,781  | 4,747 | BEHIND -20     | 0.00 s              | 0.00 s          | 8                     |
| cold     | dp / random                  | 5    | 3,999 | 3,774  | 3,492 | BEHIND -813    | 0.00 s              | 0.00 s          | 18                    |
| cold     | ils / bestrandom             | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | ils / caterpillar            | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | ils / distance               | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | ils / genetree               | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | ils / greedy                 | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | ils / random                 | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / bestrandom      | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / caterpillar     | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / distance        | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / genetree        | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / greedy          | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | multistart / random          | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | pairswap-best / bestrandom   | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.01 s              | 0.02 s          | 4                     |
| cold     | pairswap-best / caterpillar  | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-best / distance     | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 0.01 s          | 4                     |
| cold     | pairswap-best / genetree     | 5    | 4,812 | 4,812  | 4,788 | TIE            | 0.01 s              | 0.02 s          | 4                     |
| cold     | pairswap-best / greedy       | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.01 s              | 0.01 s          | 4                     |
| cold     | pairswap-best / random       | 5    | 4,812 | 4,812  | 4,782 | TIE            | 0.01 s              | 0.02 s          | 4                     |
| cold     | pairswap-first / bestrandom  | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-first / caterpillar | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-first / distance    | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-first / genetree    | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-first / greedy      | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | pairswap-first / random      | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / bestrandom        | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / caterpillar       | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / distance          | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / genetree          | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / greedy            | 5    | 4,812 | 4,812  | 4,792 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | reorient / random            | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.01 s          | 4                     |
| cold     | tabu / bestrandom            | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 10 s            | 4                     |
| cold     | tabu / caterpillar           | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 10 s            | 4                     |
| cold     | tabu / distance              | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 10 s            | 4                     |
| cold     | tabu / genetree              | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.02 s              | 10 s            | 4                     |
| cold     | tabu / greedy                | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.01 s              | 10 s            | 4                     |
| cold     | tabu / random                | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.02 s              | 10 s            | 4                     |
| cold     | vnd / bestrandom             | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | vnd / caterpillar            | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | vnd / distance               | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | vnd / genetree               | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | vnd / greedy                 | 5    | 4,812 | 4,812  | 4,812 | TIE            | 0.00 s              | 0.03 s          | 4                     |
| cold     | vnd / random                 | 5    | 4,812 | 4,812  | 4,793 | TIE            | 0.00 s              | 0.03 s          | 4                     |

primates: 14 taxa, 424 gene trees. Best known score 389,734; better ASTRAL 389,734; exact optimum 389,734.

| track    | method                       | runs | best    | median  | worst   | best vs ASTRAL  | median time to best | median run time | RF to ASTRAL-III tree |
|----------|------------------------------|------|---------|---------|---------|-----------------|---------------------|-----------------|-----------------------|
| baseline | ASTRAL-III                   | 3    | 389,734 | 389,734 | 389,734 |                 |                     | 0.95 s          |                       |
| baseline | ASTRAL-III exact             | 1    | 389,734 | 389,734 | 389,734 |                 |                     | 12 s            |                       |
| baseline | ASTRAL-IV                    | 3    | 389,734 | 389,734 | 389,734 |                 |                     | 0.51 s          |                       |
| baseline | ASTRAL-IV -R                 | 1    | 389,734 | 389,734 | 389,734 |                 |                     | 2.01 s          |                       |
| warm     | anneal / astral3             | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 9.02 s          | 0                     |
| warm     | dp / astral3                 | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| warm     | ils / astral3                | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| warm     | multistart / astral3         | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| warm     | pairswap-best / astral3      | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| warm     | pairswap-first / astral3     | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| warm     | reorient / astral3           | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| warm     | tabu / astral3               | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| warm     | vnd / astral3                | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | anneal / bestrandom          | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.74 s              | 9.02 s          | 0                     |
| cold     | anneal / caterpillar         | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 9.02 s          | 0                     |
| cold     | anneal / distance            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 9.02 s          | 0                     |
| cold     | anneal / genetree            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 9.02 s          | 0                     |
| cold     | anneal / greedy              | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 9.02 s          | 0                     |
| cold     | anneal / random              | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.01 s              | 9.02 s          | 0                     |
| cold     | dp / bestrandom              | 5    | 300,934 | 273,508 | 244,895 | BEHIND -88,800  | 0.00 s              | 0.01 s          | 20                    |
| cold     | dp / caterpillar             | 1    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | dp / distance                | 1    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | dp / genetree                | 5    | 389,734 | 389,734 | 332,157 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | dp / greedy                  | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | dp / random                  | 5    | 226,566 | 187,998 | 164,326 | BEHIND -163,168 | 0.00 s              | 0.00 s          | 18                    |
| cold     | ils / bestrandom             | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | ils / caterpillar            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | ils / distance               | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | ils / genetree               | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | ils / greedy                 | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | ils / random                 | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / bestrandom      | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / caterpillar     | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / distance        | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / genetree        | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / greedy          | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | multistart / random          | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | pairswap-best / bestrandom   | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.01 s              | 0.02 s          | 0                     |
| cold     | pairswap-best / caterpillar  | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-best / distance     | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-best / genetree     | 5    | 389,734 | 389,734 | 359,134 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-best / greedy       | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-best / random       | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.01 s              | 0.02 s          | 0                     |
| cold     | pairswap-first / bestrandom  | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-first / caterpillar | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-first / distance    | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-first / genetree    | 5    | 389,734 | 389,734 | 359,134 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-first / greedy      | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | pairswap-first / random      | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | reorient / bestrandom        | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | reorient / caterpillar       | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | reorient / distance          | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | reorient / genetree          | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | reorient / greedy            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.00 s          | 0                     |
| cold     | reorient / random            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.01 s          | 0                     |
| cold     | tabu / bestrandom            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.01 s              | 10 s            | 0                     |
| cold     | tabu / caterpillar           | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | tabu / distance              | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | tabu / genetree              | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | tabu / greedy                | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 10 s            | 0                     |
| cold     | tabu / random                | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.01 s              | 10 s            | 0                     |
| cold     | vnd / bestrandom             | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | vnd / caterpillar            | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | vnd / distance               | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | vnd / genetree               | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | vnd / greedy                 | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |
| cold     | vnd / random                 | 5    | 389,734 | 389,734 | 389,734 | TIE             | 0.00 s              | 0.02 s          | 0                     |

## 5. Checks

All scorers agree, no result exceeds an exact optimum, and every run finished.
