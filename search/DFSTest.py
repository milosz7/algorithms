import unittest
from dfs import DFS


class DFSTest(unittest.TestCase):
    def test_dfs(self):
        dfs = DFS('grafDFSBFS.txt')
        self.assertListEqual([1, 36, 84, 21, 33, 17, 38, 30, 47, 66, 49], dfs.search(1))
        self.assertListEqual([4], dfs.search(4))
        self.assertListEqual([7, 10], dfs.search(7))
        self.assertListEqual([11, 72, 57], dfs.search(11))


if __name__ == '__main__':
    unittest.main()