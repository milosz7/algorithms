import unittest
from floyd_warshall.FloydWarshall import FloydWarshall


class FloydWarshallTest(unittest.TestCase):
    def test_graph_1(self):
        fw = FloydWarshall("floyd_graph_1.txt")
        result = fw.traverse()
        expected = [
            [0, 3, 4, 6, 3, 5],
            [8, 0, 1, 3, 11, 2],
            [7, 5, 0, 2, 10, 1],
            [11, 3, 4, 0, 14, 5],
            [8, 6, 7, 3, 0, 2],
            [6, 4, 5, 1, 9, 0]
        ]
        self.assertListEqual(expected, result)

    def test_graph_2(self):
        fw = FloydWarshall("floyd_graph_2.txt")
        result = fw.traverse()
        expected = [
            [0, 3, 1, 0, -1, 3, 0, 1, 4, 1],
            [2, 0, 1, 0, -1, 3, 0, 1, 4, 1],
            [5, 8, 0, 5, 4, 6, 5, 6, 9, 6],
            [2, 3, 1, 0, 1, 3, 0, 3, 6, 1],
            [3, 4, 2, 1, 0, 4, 1, 2, 5, 2],
            [-1, 2, 0, -1, -2, 0, -1, 0, 3, 0],
            [2, 5, 3, 2, 1, 3, 0, 3, 6, 3],
            [1, 2, 0, -1, -2, 2, -1, 0, 3, 0],
            [4, 5, 3, 2, 1, 5, 2, 3, 0, 3],
            [1, 2, 2, 1, 0, 2, -1, 2, 5, 0]
        ]
        self.assertListEqual(expected, result)


if __name__ == "__main__":
    unittest.main()