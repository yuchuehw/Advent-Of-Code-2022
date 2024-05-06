from collections import defaultdict
import itertools
import functools

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
    data = """Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
    Valve BB has flow rate=13; tunnels lead to valves CC, AA
    Valve CC has flow rate=2; tunnels lead to valves DD, BB
    Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
    Valve EE has flow rate=3; tunnels lead to valves FF, DD
    Valve FF has flow rate=0; tunnels lead to valves EE, GG
    Valve GG has flow rate=0; tunnels lead to valves FF, HH
    Valve HH has flow rate=22; tunnel leads to valve GG
    Valve II has flow rate=0; tunnels lead to valves AA, JJ
    Valve JJ has flow rate=21; tunnel leads to valve II"""

    Nodes, Flow, Distance = parse_data(data)
    floyd_warshall(Nodes, Distance)
    print(search(Flow, Distance))

if __name__ == "__main__":
    main()
