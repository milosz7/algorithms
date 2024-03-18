from MatrixGraph import MatrixGraph


class DFS:
    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename)
        self.visited = set()
        self.result = []

    def _run(self, start):
        self.visited.add(start)
        self.result.append(start)
        for node in self.graph.get_neighbours(start):
            if node not in self.visited:
                self._run(node)
        return self.result.copy()

    def _clear(self):
        self.visited.clear()
        self.result.clear()

    def search(self, current):
        result = self._run(current)
        self._clear()
        return result
