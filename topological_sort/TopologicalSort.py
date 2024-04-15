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
        for vertex in range(vertices):
            n_edges = len(self.graph.get_edges_to(vertex))
            if n_edges == 0:
                self.queue.append(vertex)

        while self.queue:
            popped = self.queue.popleft()
            result.append(popped)
            edges_from_popped = self.graph.get_neighbours(popped)
            for to, _ in edges_from_popped:
                self.graph.remove_edge(popped, to)
                if len(self.graph.get_edges_to(to)) == 0:
                    self.queue.append(to)

        if self.graph.count_edges():
            return "ERROR - cycle detected"
        else:
            return result






