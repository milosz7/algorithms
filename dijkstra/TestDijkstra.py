import unittest
from Dijkstra import Dijkstra
import math


class TestDijkstra(unittest.TestCase):
    def test_dijkstra_0_1(self):
        self.dijkstra = Dijkstra("Graf1.txt")
        distances, paths = self.dijkstra.run(0)
        self.assertListEqual([0, 3, 4, 6, 3, 5], distances)
        self.assertDictEqual({
            "0": [],
            "1": [0],
            "2": [1, 0],
            "3": [5, 4, 0],
            "4": [0],
            "5": [4, 0]}, paths)

    def test_dijkstra_1_1(self):
        self.dijkstra = Dijkstra("Graf1.txt")
        distances, paths = self.dijkstra.run(1)
        self.assertListEqual([8, 0, 1, 3, 11, 2], distances)
        self.assertDictEqual({
            "0": [5, 2, 1],
            "1": [],
            "2": [1],
            "3": [5, 2, 1],
            "4": [0, 5, 2, 1],
            "5": [2, 1]}, paths)

    def test_dijkstra_2_1(self):
        self.dijkstra = Dijkstra("Graf1.txt")
        distances, paths = self.dijkstra.run(2)
        self.assertListEqual([7, 5, 0, 2, 10, 1], distances)
        self.assertDictEqual({
            "0": [5, 2],
            "1": [3, 5, 2],
            "2": [],
            "3": [5, 2],
            "4": [0, 5, 2],
            "5": [2]}, paths)

    def test_dijkstra_3_1(self):
        self.dijkstra = Dijkstra("Graf1.txt")
        distances, paths = self.dijkstra.run(3)
        self.assertListEqual([11, 3, 4, 0, 14, 5], distances)
        self.assertDictEqual({
            "0": [5, 2, 1, 3],
            "1": [3],
            "2": [1, 3],
            "3": [],
            "4": [0, 5, 2, 1, 3],
            "5": [2, 1, 3]}, paths)

    def test_dijkstra_4_1(self):
        self.dijkstra = Dijkstra("Graf1.txt")
        distances, paths = self.dijkstra.run(4)
        self.assertListEqual([8, 6, 7, 3, 0, 2], distances)
        self.assertDictEqual({
            "0": [5, 4],
            "1": [3, 5, 4],
            "2": [1, 3, 5, 4],
            "3": [5, 4],
            "4": [],
            "5": [4]}, paths)

    def test_dijkstra_0_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(0)
        self.assertListEqual([0, 15, 25, 9, 8, 16, 16, math.inf, 19, 19], distances)
        self.assertDictEqual({
            "0": [],
            "1": [4, 0],
            "2": [8, 5, 3, 4, 0],
            "3": [4, 0],
            "4": [0],
            "5": [3, 4, 0],
            "6": [3, 4, 0],
            "7": None,
            "8": [5, 3, 4, 0],
            "9": [1, 4, 0]
        }, paths)

    def test_dijkstra_1_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(1)
        self.assertListEqual([8, 0, 12, 17, 16, 8, 2, math.inf, 6, 4], distances)
        self.assertDictEqual({
            "0": [8, 9, 1],
            "1": [],
            "2": [8, 9, 1],
            "3": [4, 0, 8, 9, 1],
            "4": [0, 8, 9, 1],
            "5": [1],
            "6": [1],
            "7": None,
            "8": [9, 1],
            "9": [1]
        }, paths)

    def test_dijkstra_2_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(2)
        self.assertListEqual([23, 38, 0, 32, 31, 39, 9, math.inf, 21, 19], distances)
        self.assertDictEqual({
            "0": [8, 9, 6, 2],
            "1": [4, 0, 8, 9, 6, 2],
            "2": [],
            "3": [4, 0, 8, 9, 6, 2],
            "4": [0, 8, 9, 6, 2],
            "5": [3, 4, 0, 8, 9, 6, 2],
            "6": [2],
            "7": None,
            "8": [9, 6, 2],
            "9": [6, 2]
        }, paths)

    def test_dijkstra_3_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(3)
        self.assertListEqual([7, 11, 16, 0, 4, 7, 7, math.inf, 10, 15], distances)
        self.assertDictEqual({
            "0": [4, 3],
            "1": [4, 3],
            "2": [8, 5, 3],
            "3": [],
            "4": [3],
            "5": [3],
            "6": [3],
            "7": None,
            "8": [5, 3],
            "9": [1, 4, 3]
            }, paths)

    def test_dijkstra_4_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(4)
        self.assertListEqual([3, 7, 17, 1, 0, 8, 8, math.inf, 11, 11], distances)
        self.assertDictEqual({
            "0": [4],
            "1": [4],
            "2": [8, 5, 3, 4],
            "3": [4],
            "4": [],
            "5": [3, 4],
            "6": [3, 4],
            "7": None,
            "8": [5, 3, 4],
            "9": [1, 4]
        }, paths)

    def test_dijkstra_5_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(5)
        self.assertListEqual([5, 20, 9, 14, 13, 0, 18, math.inf, 3, 24], distances)
        self.assertDictEqual({
            "0": [8, 5],
            "1": [4, 0, 8, 5],
            "2": [8, 5],
            "3": [4, 0, 8, 5],
            "4": [0, 8, 5],
            "5": [],
            "6": [2, 8, 5],
            "7": None,
            "8": [5],
            "9": [1, 4, 0, 8, 5]
        }, paths)

    def test_dijkstra_6_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(6)
        self.assertListEqual([14, 29, 18, 23, 22, 30, 0, math.inf, 12, 10], distances)
        self.assertDictEqual({
            "0": [8, 9, 6],
            "1": [4, 0, 8, 9, 6],
            "2": [8, 9, 6],
            "3": [4, 0, 8, 9, 6],
            "4": [0, 8, 9, 6],
            "5": [3, 4, 0, 8, 9, 6],
            "6": [],
            "7": None,
            "8": [9, 6],
            "9": [6]
        }, paths)

    def test_dijkstra_7_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(7)
        self.assertListEqual([3, 18, 7, 12, 11, 19, 16, 0, 1, 22], distances)
        self.assertDictEqual({
            "0": [8, 7],
            "1": [4, 0, 8, 7],
            "2": [8, 7],
            "3": [4, 0, 8, 7],
            "4": [0, 8, 7],
            "5": [3, 4, 0, 8, 7],
            "6": [2, 8, 7],
            "7": [],
            "8": [7],
            "9": [1, 4, 0, 8, 7]
        }, paths)

    def test_dijkstra_8_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(8)
        self.assertListEqual([2, 17, 6, 11, 10, 18, 15, math.inf, 0, 21], distances)
        self.assertDictEqual({
            "0": [8],
            "1": [4, 0, 8],
            "2": [8],
            "3": [4, 0, 8],
            "4": [0, 8],
            "5": [3, 4, 0, 8],
            "6": [2, 8],
            "7": None,
            "8": [],
            "9": [1, 4, 0, 8]
        }, paths)

    def test_dijkstra_9_2(self):
        self.dijkstra = Dijkstra("Graf2.txt")
        distances, paths = self.dijkstra.run(9)
        self.assertListEqual([4, 19, 8, 13, 12, 20, 17, math.inf, 2, 0], distances)
        self.assertDictEqual({
            "0": [8, 9],
            "1": [4, 0, 8, 9],
            "2": [8, 9],
            "3": [4, 0, 8, 9],
            "4": [0, 8, 9],
            "5": [3, 4, 0, 8, 9],
            "6": [2, 8, 9],
            "7": None,
            "8": [9],
            "9": []
        }, paths)
