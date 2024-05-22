from graph.MatrixGraph import MatrixGraph
import random
from collections import Counter


class MaxCut:
    def __init__(self, graph_filename, iterations=1000):
        self.graph = MatrixGraph.read_from_file(graph_filename)
        self.n = self.graph.get_vertices()
        self.subset_map = [False] * self.n
        self.iterations = iterations

    def _run(self):
        for i in range(self.n):
            to_assign = random.choice((0, 1))
            if to_assign == 0:
                self.subset_map[i] = True

        unsolved = True
        while unsolved:
            unsolved = False
            for v in range(self.n):
                edges = self.graph.get_neighbours(v)
                vertices_to = [edge[0] for edge in edges]
                vertex_set = self.subset_map[v]
                same_graph = [vertex for vertex in vertices_to if self.subset_map[vertex] == vertex_set]
                crossing_graph = [vertex for vertex in vertices_to if self.subset_map[vertex] != vertex_set]
                if len(same_graph) > len(crossing_graph):
                    self.subset_map[v] = not vertex_set
                    unsolved = True

    def reset(self):
        self.subset_map = [False] * self.n

    def solve(self):
        best_value = -1
        results = []
        for _ in range(self.iterations):
            print(f'Iteration {_}')
            self.subset_map = [False] * self.n
            self._run()
            current_value = self.count_cut()
            results.append(current_value)
            if current_value > best_value:
                best_value = current_value
        final_subsets = [1 if vertex else 0 for vertex in self.subset_map]
        self.reset()
        return best_value, final_subsets

    def count_cut(self):
        cut = 0
        for v in range(self.n):
            current_subset = self.subset_map[v]
            edges = self.graph.get_neighbours(v)
            vertices_to = [edge[0] for edge in edges]
            for vertex in vertices_to:
                if current_subset != self.subset_map[vertex]:
                    cut += 1
        # graph is undirected
        cut = cut // 2

        return cut


if __name__ == '__main__':
    max_cut = MaxCut('graph_to_solve.txt', iterations=1000)
    max_cut, subsets = max_cut.solve()
    print(f'Max cut: {max_cut}')
    print(f'Subsets: {subsets}')
