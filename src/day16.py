#!/usr/bin/env python3
from collections import defaultdict
import functools
import itertools
import sys

def parse_data(data):
    Nodes = set()
    Flow = {}
    Distance = defaultdict(lambda: float('inf'))

    for d in data.replace("valves","valve").split("\n"):
        node = d.split()[1]
        rate = int(d[d.index("=")+1:d.index(";")])
        neighbors = d[d.rfind("valve ")+len("valve "):].split(", ")

        Nodes.add(node)
        Flow[node] = rate
        for neighbor in neighbors:
            Distance[neighbor,node] = 1

    return Nodes, Flow, Distance

def floyd_warshall(Nodes, Distance):
    for k, i, j in itertools.product(Nodes, Nodes, Nodes):
        Distance[i,j] = min(Distance[i,j], Distance[i,k] + Distance[k,j])

def search(Flow, Distance):
    @functools.cache
    def aux(time=30, current='AA', unseen=frozenset(Flow)):
        candidates = [node for node in unseen if Distance[current,node]<time]
        if not candidates:
            return 0
        return max(Flow[node] * (time_left := time-Distance[current,node]-1) + 
            aux(time_left, node, unseen-{node}) for node in candidates)
    return aux()

def main():
    filename = sys.argv[1] if len(sys.argv) > 1 else "input.txt"

    with open(filename, "r", encoding="utf8") as f:
        data = f.read().strip()

    Nodes, Flow, Distance = parse_data(data)
    floyd_warshall(Nodes, Distance)
    print(search(Flow, Distance))

if __name__ == "__main__":
    main()
