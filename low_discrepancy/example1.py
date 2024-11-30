# plots 200 terms from a 2-dimensional low-discrepancy sequence on a 40x20 grid

import sys
import time

from lds import low_discrepancy_sequence

size = 20
for _ in range(size):
    print()

s = low_discrepancy_sequence(2)
for _ in range(200):
    (x, y) = next(s)
    sys.stdout.write("\x1b7\x1b[%d;%df%s\x1b8" % (int(y * size) + 2, int(x * size * 2), 'o'))
    sys.stdout.flush()
    time.sleep(0.05)
