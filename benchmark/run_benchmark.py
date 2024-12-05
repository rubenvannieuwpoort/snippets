#!/usr/bin/env python3

import sys
import subprocess
from typing import Iterator


def generate_params() -> Iterator[list[str]]:
    for i in range(10, 29):
        size = 1 << i
        times = (10 * 1024 * 1024 * 1024) // size
        yield [str(times), str(size)]


all_params = list(generate_params())

for i, params in enumerate(all_params):
    if sys.argv[1] == '-h':
        print(params[1], end='')
    else:
        print(float(subprocess.run([sys.argv[1], *params], capture_output=True, text=True).stdout), end='')

    if i != len(all_params) - 1:
        print(';', end='')

print()
