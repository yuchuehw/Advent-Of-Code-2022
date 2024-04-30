from collections import namedtuple

Point = namedtuple("Point", "x y")
data = """Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3"""

GRID_BOUNDARY = {
    "minX": float("inf"),
    "maxX": float("-inf"),
    "minY": float("inf"),
    "maxY": float("-inf"),
}

sensor_beacon = []

for row in data.split("\n"):
    sensor_x = int(row.split("x=")[1].split(",")[0])
    sensor_y = int(row.split("y=")[1].split(":")[0])
    beacon_x = int(row.split("x=")[2].split(",")[0])
    beacon_y = int(row.split("y=")[2])
    
    sensor = Point(sensor_x, sensor_y)
    beacon = Point(beacon_x, beacon_y)
    
    GRID_BOUNDARY["minX"] = min(GRID_BOUNDARY["minX"], sensor.x, beacon.x)
    GRID_BOUNDARY["minY"] = min(GRID_BOUNDARY["minY"], sensor.y, beacon.y)
    GRID_BOUNDARY["maxX"] = max(GRID_BOUNDARY["maxX"], sensor.x, beacon.x)
    GRID_BOUNDARY["maxY"] = max(GRID_BOUNDARY["maxY"], sensor.y, beacon.y)
    sensor_beacon.append((sensor, beacon))

FIXED_Y = 10 

l = list(range(GRID_BOUNDARY["minX"], GRID_BOUNDARY["maxX"] + 1))
