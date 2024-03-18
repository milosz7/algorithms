from MatrixGraph import MatrixGraph


class BFS:
    """Breadth First Search implementation using a queue.
    The queue is used to store the vertices to be visited.
    The visited set is used to keep track of the vertices already visited.
    """

    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename)
        self.queue = []
        self.visited = set()
        self.result = []

    def visit(self, neighbor):
        if neighbor not in self.visited:
            self.queue.append(neighbor)
            self.visited.add(neighbor)

    def run(self, start):
        self.queue.append(start)
        self.visited.add(start)
        while self.queue:
            current = self.queue.pop(0)
            self.result.append(current)
            for neighbor in self.graph.get_neighbours(current):
                self.visit(neighbor)
        return self.result.copy()

    def search(self, start):
        result = self.run(start)
        self.clear()
        return result

    def clear(self):
        self.queue.clear()
        self.visited.clear()
        self.result.clear()