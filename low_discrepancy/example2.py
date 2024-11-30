# displays 10 terms of a 6-dimension low-discrepancy sequence

from lds import low_discrepancy_sequence


s = low_discrepancy_sequence(6)
for _ in range(10):
    print(next(s))
