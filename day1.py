import sys
from functools import reduce

lines = []

for line in sys.stdin:
    if line == "done\n": break
    lines.append([int(char) for char in line if char.isdigit()])

numbers = list(map(lambda chars: chars[0] * 10 + chars[-1], lines))

print(reduce(lambda a, b: a + b, numbers))
