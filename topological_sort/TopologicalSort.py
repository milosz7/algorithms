from graph.MatrixGraph import MatrixGraph
from collections import deque


class TopologicalSort:
    def __init__(self, *, graph_filename=None, graph_object=None, weighted_graph=True):
        self.queue = deque()
        if graph_filename:
            self.graph = MatrixGraph.read_from_file(graph_filename, weighted_graph)
        elif graph_object:
            self.graph = graph_object
        else:
            raise ValueError("Pass the filename or the graph object in the constructor!")

    def sort(self):
        result = []
        vertices = self.graph.get_vertices()
        in_degrees = []
        for vertex in range(vertices):
            in_degrees.append(len(self.graph.get_edges_to(vertex)))
            if in_degrees[vertex] == 0:
                self.queue.append(vertex)

        while self.queue:
            popped = self.queue.popleft()
            result.append(popped)
            edges_from_popped = self.graph.get_neighbours(popped)
            for to, _ in edges_from_popped:
                in_degrees[to] -= 1
                if in_degrees[to] == 0:
                    self.queue.append(to)

        if len(result) != vertices:
            return "ERROR - cycle detected"
        else:
            return result






