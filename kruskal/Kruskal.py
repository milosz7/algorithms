from graph.MatrixGraph import MatrixGraph
from priority_queue.PriorityQueue import PriorityQueue


class Kruskal:
    def __init__(self, graph_filename):
        self.graph = MatrixGraph.read_from_file(graph_filename, weighted=True)
        self.vertices = self.graph.get_vertices_in_graph()
        self.are_connected = [i for i in range(self.graph.get_vertices())]
        self.mst = []
        self.queue = PriorityQueue()

    def populate_queue(self):
        for vertex_from in self.vertices:
            edges = self.graph.get_neighbours(vertex_from)

            for vertex_to, weight in edges:
                self.queue.push((vertex_from, vertex_to), weight)

    def run(self):
        while not self.queue.is_empty():
            (vertex_from, vertex_to), weight = self.queue.pop()
            conn_from = self.are_connected[vertex_from]
            conn_to = self.are_connected[vertex_to]

            if conn_to != conn_from:
                min_conn = min(conn_to, conn_from)
                max_conn = max(conn_to, conn_from)
                for i in range(len(self.are_connected)):
                    if self.are_connected[i] == max_conn:
                        self.are_connected[i] = min_conn

                self.mst.append(((vertex_from, vertex_to), weight))

    def sum_weights(self):
        return sum([weight for _, weight in self.mst])


if __name__ == "__main__":
    kruskal = Kruskal("graph.txt")
    kruskal.populate_queue()
    kruskal.run()
    print(kruskal.sum_weights())
    for edge in kruskal.mst:
        print(edge)
