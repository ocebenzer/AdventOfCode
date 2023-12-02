sum_ids = 0

num_cubes = {
    "red": 12,
    "green": 13,
    "blue": 14
}

for line in open("day2.txt").readlines():
    tokens = line.split()
    line_id = int(tokens[1][:-1])
    # pairs of words after 2+
    num_words = len(tokens) // 2 - 1
    for i in range(num_words):
        number = int(tokens[2 + 2*i])
        color = tokens[2 + 2*i + 1][:-1] if i < num_words-1 else tokens[2 + 2*i + 1]
        if num_cubes[color] < number:
            line_id = 0 # inefficient but works
    sum_ids += line_id

print(sum_ids)
