instructions = """addx 1
noop
addx 5
addx -1
addx 5
addx 1
noop
noop
addx 2
addx 5
addx 2
addx 1
noop
addx -21
addx 26
addx -6
addx 8
noop
noop
addx 7
noop
noop
noop
addx -37
addx 13
addx -6
addx -2
addx 5
addx 25
addx 2
addx -24
addx 2
addx 5
addx 5
noop
noop
addx -2
addx 2
addx 5
addx 2
addx 7
addx -2
noop
addx -8
addx 9
addx -36
noop
noop
addx 5
addx 6
noop
addx 25
addx -24
addx 3
addx -2
noop
addx 3
addx 6
noop
addx 9
addx -8
addx 5
addx 2
addx -7
noop
addx 12
addx -10
addx 11
addx -38
addx 22
addx -15
addx -3
noop
addx 32
addx -25
addx -7
addx 11
addx 5
addx 10
addx -9
addx 17
addx -12
addx 2
noop
addx 2
addx -15
addx 22
noop
noop
noop
addx -35
addx 7
addx 21
addx -25
noop
addx 3
addx 2
noop
addx 7
noop
addx 3
noop
addx 2
addx 9
addx -4
addx -2
addx 5
addx 2
addx -2
noop
addx 7
addx 2
addx -39
addx 2
noop
addx 1
noop
addx 5
addx 24
addx -20
addx 1
addx 5
noop
noop
addx 4
noop
addx 1
noop
addx 4
addx 3
noop
addx 2
noop
noop
addx 1
addx 2
noop
addx 3
noop
noop"""

value = 1
old_value = 1

cycle = 1
seen = 0


answer = 0

for i in instructions.split("\n"):
    if " " not in i:
        cycle += 1
    else:
        old_value = value
        value += int(i[i.index(" ")+1:])
        cycle += 2
    if cycle >=20 and (cycle-20)%40 == 0:
        seen = cycle
        answer += cycle*value
        print(cycle*value)
    elif cycle >=21 and (cycle-21)%40 == 0 and (cycle-1) != seen:
        answer += (cycle-1)*old_value
        print((cycle-1)*old_value)
print(answer)
