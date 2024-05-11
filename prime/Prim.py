from graph.MatrixGraph import MatrixGraph
from priority_queue.PriorityQueue import PriorityQueue


class Prim:
    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename, weighted=True)
        self.queue = PriorityQueue()
        self.mst = []
        self.visited = []

    def populate_queue(self, start):
        edges = self.graph.get_neighbours(start)

        for vertex_to, weight in edges:
            self.queue.push((start, vertex_to), weight)

    def run(self, start):
        self.visited.append(start)
        n_vertices = self.graph.get_vertices()

        self.populate_queue(start)

        while len(self.visited) < n_vertices:
            edge = self.queue.pop()
            (vertex_from, vertex_to), weight = edge
            if vertex_to not in self.visited:
                self.visited.append(vertex_to)
                self.mst.append(edge)
                self.populate_queue(vertex_to)

    def sum_weights(self):
        return sum([weight for _, weight in self.mst])
