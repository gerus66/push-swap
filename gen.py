#!/usr/bin/python3

import random
import sys

n = int(sys.argv[1])
random.seed()
ar = []
for _ in range(n):
    new = random.randint(-n, n)
    if new not in ar:
        ar.append(new)

print(' '.join(map(str, ar)))
