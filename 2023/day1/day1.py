import re
from functools import reduce

forward_list = [
    r"\d",
    r"one",
    r"two",
    r"three",
    r"four",
    r"five",
    r"six",
    r"seven",
    r"eight",
    r"nine"
]

backward_list = list(map(lambda str: str[::-1], forward_list))
backward_list[0] = r"\d"

forward = re.compile("|".join(forward_list))
backward = re.compile("|".join(backward_list))

total = 0

for line in open("day1.txt").readlines():
    first_match = forward.search(line).group()
    first = int(first_match) if first_match.isdigit() else forward_list.index(first_match)
    last_match = backward.search(line[::-1]).group()
    last = int(last_match) if last_match.isdigit() else backward_list.index(last_match)
    total += int(first) * 10 + int(last)

print(total)
