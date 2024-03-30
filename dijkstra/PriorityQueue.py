class PriorityQueue:
    """
    PriorityQueue for (data, weight) pairs.
    The Queue works as min heap so the top of the queue is
    going to be the node with the minimal distance.
    """
    def __init__(self):
        self.queue = []

    def push(self, node, distance):
        self.queue.append((node, distance))
        idx = len(self.queue) - 1
        self.heapify_up(idx)

    def heapify_up(self, idx):
        parent_idx = (idx - 1) // 2
        parent = self.queue[parent_idx][1]
        current = self.queue[idx][1]
        if (parent_idx >= 0) and (current < parent):
            temp = self.queue[parent_idx]
            self.queue[parent_idx] = self.queue[idx]
            self.queue[idx] = temp
            self.heapify_up(parent_idx)

    def heapify_down(self, idx):
        left_idx = 2 * idx + 1
        right_idx = 2 * idx + 2
        largest = idx
        if (left_idx < len(self.queue)) and (self.queue[left_idx][1] < self.queue[largest][1]):
            largest = left_idx
        if (right_idx < len(self.queue)) and (self.queue[right_idx][1] < self.queue[largest][1]):
            largest = right_idx
        if largest != idx:
            temp = self.queue[idx]
            self.queue[idx] = self.queue[largest]
            self.queue[largest] = temp
            self.heapify_down(largest)

    def update_priority(self, node, distance):
        for i, (n, d) in enumerate(self.queue):
            if n == node:
                self.queue[i] = (n, distance)
                if distance < d:
                    self.heapify_up(i)
                else:
                    self.heapify_down(i)
                break

    def top(self):
        if self.is_empty():
            return None
        return self.queue[0]

    def pop(self):
        if self.is_empty():
            return None
        if len(self.queue) == 1:
            return self.queue.pop()
        top = self.queue[0]
        self.queue[0] = self.queue.pop()
        self.heapify_down(0)
        return top

    def is_empty(self):
        return len(self.queue) == 0

    def __len__(self):
        return len(self.queue)

    def __str__(self):
        return str(self.queue)

    def __contains__(self, value):
        return value in [x[0] for x in self.queue]