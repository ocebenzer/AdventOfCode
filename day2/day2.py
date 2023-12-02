sum_ids = 0

min_cubes = {
    "red": 0,
    "green": 0,
    "blue": 0
}

for line in open("day2.txt").readlines():
    tokens = line.split()
    line_id = int(tokens[1][:-1])
    # pairs of words after 2+
    num_words = len(tokens) // 2 - 1
    for i in range(num_words):
        number = int(tokens[2 + 2*i])
        color = tokens[2 + 2*i + 1][:-1] if i < num_words-1 else tokens[2 + 2*i + 1]
        min_cubes[color] = max(min_cubes[color], number)
    sum_ids += min_cubes["red"] * min_cubes["green"] * min_cubes["blue"]
    min_cubes = {
        "red": 0,
        "green": 0,
        "blue": 0
    }

print(sum_ids)
