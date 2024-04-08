import unittest
from priority_queue.PriorityQueue import PriorityQueue


class TestPriorityQueue(unittest.TestCase):
    def setUp(self):
        self.pq = PriorityQueue()
        self.pq.push(3, 2)
        self.pq.push(1, 3)
        self.pq.push(2, 1)

    def tearDown(self):
        self.pq = None

    def test_update(self):
        self.pq.update_priority(2, 5)
        self.assertEqual((3, 2), self.pq.top())
        self.pq.update_priority(2, 1)
        self.assertEqual((2, 1), self.pq.top())

    def test_pop(self):
        self.assertEqual((2, 1), self.pq.pop())
        self.assertEqual((3, 2), self.pq.pop())
        self.assertEqual((1, 3), self.pq.pop())
        self.assertIsNone(self.pq.pop())
        self.assertTrue(self.pq.is_empty())

    def test_top(self):
        self.assertEqual((2, 1), self.pq.top())
        self.assertEqual((2, 1), self.pq.top())
        self.pq.pop()
        self.assertEqual((3, 2), self.pq.top())
        self.pq.pop()
        self.assertEqual((1, 3), self.pq.top())
        self.pq.pop()
        self.assertIsNone(self.pq.top())
