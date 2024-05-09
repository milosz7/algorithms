import unittest
from kruskal.Kruskal import Kruskal


class TestKruskal(unittest.TestCase):
    def setUp(self):
        """
        graph file contents:\n
        4\n
        0 1 1\n
        1 0 1\n
        1 2 2\n
        2 1 2\n
        0 2 4\n
        2 0 4\n
        0 3 6\n
        3 0 6\n
        3 2 9\n
        2 3 9\n
        """
        self.kruskal = Kruskal(graph_filename="graph_test.txt")

    def test_populate_queue(self):
        self.kruskal.populate_queue()
        self.assertEqual(len(self.kruskal.queue), 10)

    def test_run(self):
        self.kruskal.populate_queue()
        self.kruskal.run()
        self.assertEqual(len(self.kruskal.mst), 3)

    def test_sum_weights(self):
        self.kruskal.populate_queue()
        self.kruskal.run()
        self.assertEqual(self.kruskal.sum_weights(), 9)


if __name__ == '__main__':
    unittest.main()
