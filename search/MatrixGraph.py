class MatrixGraph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = [[False for _ in range(vertices)] for _ in range(vertices)]

    def add_edge(self, u, v):
        self.graph[u][v] = True

    def remove_edge(self, u, v):
        if not self.check_boundaries(u,v):
            raise IndexError(f'Invalid vertex for size {self.vertices}')
        if self.has_edge(u, v):
            self.graph[u][v] = False
        else:
            raise IndexError(f'No edge between {u} and {v}')

    def has_edge(self, u, v):
        return self.graph[u][v]

    @staticmethod
    def read_from_file(file):
        with open(file, 'r') as f:
            graph = MatrixGraph(int(f.readline()))
            for line in f:
                u, v = map(int, line.split())
                graph.add_edge(u, v)
        return graph

    def get_neighbours(self, u):
        return sorted([v for v in range(self.vertices) if self.graph[u][v]])

    def check_boundaries(self, u, v):
        return 0 <= u < self.vertices and 0 <= v < self.vertices

    def __str__(self):
        return '\n'.join([' '.join(map(str, row)) for row in self.graph])
