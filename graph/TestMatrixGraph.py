import unittest
from graph.MatrixGraph import MatrixGraph


class TestMatrixGraph(unittest.TestCase):
    def setUp(self):
        self.graph = MatrixGraph(5)
        self.graph.add_edge(1, 3, 20)
        self.graph.add_edge(1, 2, 20)
        self.graph.add_edge(2, 3, 30)
        self.graph.add_edge(3, 4, 40)

    def test_get_edges_to(self):
        self.assertListEqual(self.graph.get_edges_to(2), [(1, 2, 20)])
        self.assertListEqual(self.graph.get_edges_to(3), [(1, 3, 20), (2, 3, 30)])
        self.assertListEqual(self.graph.get_edges_to(4), [(3, 4, 40)])

    def test_get_vertices(self):
        self.assertSetEqual(self.graph.get_vertices_in_graph(), {1, 2, 3, 4})


if __name__ == "__main__":
    unittest.main()
