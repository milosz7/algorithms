class MatrixGraph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]

    def add_edge(self, u, v, weight=1):
        if not self.check_boundaries(u,v):
            raise IndexError(f'Invalid vertex for size {self.vertices}')
        self.graph[u][v] = weight

    def remove_edge(self, u, v):
        if not self.check_boundaries(u,v):
            raise IndexError(f'Invalid vertex for size {self.vertices}')
        if self.has_edge(u, v):
            self.graph[u][v] = 0
        else:
            raise IndexError(f'No edge between {u} and {v}')

    def get_edge(self, u, v):
        if not self.check_boundaries(u,v):
            raise IndexError(f'Invalid vertex for size {self.vertices}')
        return self.graph[u][v]

    def has_edge(self, u, v):
        if not self.check_boundaries(u,v):
            raise IndexError(f'Invalid vertex for size {self.vertices}')
        return self.graph[u][v]

    def get_vertices(self):
        return self.vertices

    @staticmethod
    def read_from_file(file, weighted=False):
        with open(file, 'r') as f:
            graph = MatrixGraph(int(f.readline()))
            for line in f:
                if weighted:
                    u, v, w = map(int, line.split())
                    graph.add_edge(u, v, w)
                else:
                    u, v = map(int, line.split())
                    graph.add_edge(u, v)
        return graph

    def get_neighbours(self, u):
        return sorted([(v, self.graph[u][v]) for v in range(self.vertices) if self.graph[u][v]])

    def check_boundaries(self, u, v):
        return 0 <= u < self.vertices and 0 <= v < self.vertices

    def __str__(self):
        return '\n'.join([' '.join(map(str, row)) for row in self.graph])
