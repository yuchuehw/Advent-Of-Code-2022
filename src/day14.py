data = """498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9"""

occupied = set()

LARGEST_Y = 0

for row in data.split("\n"):
    row = [tuple(map(int,_.split(","))) for _ in row.split(" -> ")]
    while len(row)-1:
        p1 = row.pop(0)
        p2 = row[0]
        LARGEST_Y = max(LARGEST_Y,p1[1],p2[1])
        range1 = range(p1[0],p2[0]+1) if p1[0]<p2[0]else range(p2[0],p1[0]+1)
        range2 = range(p1[1],p2[1]+1) if p1[1]<p2[1]else range(p2[1],p1[1]+1)
        occupied.update({(x,y)for x in range1 for y in range2})
    
    
sand = 0
while True:
    sand += 1
    current_position = (500,-1)
    found = False
    while True:
        targets = [(current_position[0]+dx,current_position[1]+dy) for dx, dy in [(0,1),(-1,1),(1,1)]]
        for target in targets:
            if target not in occupied:
                current_position = target
                break
        else:
            occupied.add(current_position)
            break
        if target[1] > LARGEST_Y:
            found = True
            break
    
    if found:
        print(sand-1)
        break
