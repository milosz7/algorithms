import unittest
from topological_sort.TopologicalSort import TopologicalSort
from graph.MatrixGraph import MatrixGraph


class TestTopologicalSort(unittest.TestCase):
    def setUp(self):
        self.graph = MatrixGraph(5)
        self.graph.add_edge(0, 1)
        self.graph.add_edge(1, 2)
        self.graph.add_edge(2, 3)
        self.graph.add_edge(3, 4)
        self.topological_sort = TopologicalSort(graph_object=self.graph)

    def test_sort(self):
        self.assertListEqual(self.topological_sort.sort(), [0, 1, 2, 3, 4])

    def test_sort_with_cycle(self):
        self.graph.add_edge(4, 0)
        self.assertEqual(self.topological_sort.sort(), "ERROR - cycle detected")


if __name__ == '__main__':
    unittest.main()
