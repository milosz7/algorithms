from MatrixGraph import MatrixGraph
from PriorityQueue import PriorityQueue
import math


class Dijkstra:
    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename, weighted=True)
        self.vertices = self.graph.get_vertices()

    def run(self, start):
        distances = [math.inf] * self.vertices
        precedents = [None] * self.vertices
        distances[start] = 0
        precedents[start] = start
        queue = PriorityQueue()

        for i in range(self.vertices):
            queue.push(i, distances[i])

        while not queue.is_empty():
            current, distance = queue.pop()

            for vertex, _ in self.graph.get_neighbours(current):
                edge = self.graph.get_edge(current, vertex)
                alt = distances[current] + edge

                if alt < distances[vertex]:
                    distances[vertex] = alt
                    precedents[vertex] = current
                    queue.update_priority(vertex, alt)

        return distances, self.get_paths(start, precedents)

    def get_paths(self, start, precedents):
        paths = {}
        for i in range(self.vertices):
            if i == start:
                paths[str(i)] = []
                continue

            current_vertex = precedents[i]
            current_path = [current_vertex]

            if precedents[i] is None:
                paths[str(i)] = None
            else:
                while current_vertex is not start:
                    current_vertex = precedents[current_vertex]
                    current_path.append(current_vertex)
                paths[str(i)] = current_path

        return paths


