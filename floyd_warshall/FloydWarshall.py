from graph.MatrixGraph import MatrixGraph
import math


class FloydWarshall:
    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename, weighted=True)
        self.size = self.graph.get_vertices()
        self.paths_matrix = [
            [0 if x == y else math.inf for x in range(self.size)]
            for y in range(self.size)
        ]

    def traverse(self):
        for i in range(self.size):
            for j in range(self.size):
                weight = self.graph.get_edge(i, j)
                if weight != 0:
                    self.paths_matrix[i][j] = weight

        for i in range(self.size):
            for j in range(self.size):
                for k in range(self.size):
                    path_jk = self.paths_matrix[j][k]
                    path_ji = self.paths_matrix[j][i]
                    path_ik = self.paths_matrix[i][k]
                    if path_jk > path_ji + path_ik:
                        self.paths_matrix[j][k] = path_ji + path_ik

        return self.paths_matrix
