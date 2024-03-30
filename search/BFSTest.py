import unittest
from bfs import BFS


class BFSTest(unittest.TestCase):
    def test_bfs(self):
        bfs = BFS('grafDFSBFS.txt')
        self.assertListEqual([1, 36, 84, 21, 66, 33, 49, 17, 30, 47, 38], bfs.search(1))
        self.assertListEqual([4], bfs.search(4))
        self.assertListEqual([7, 10], bfs.search(7))
        self.assertListEqual([11, 72, 57], bfs.search(11))


if __name__ == '__main__':
    unittest.main()