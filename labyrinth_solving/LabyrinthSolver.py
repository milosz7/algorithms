import random
from priority_queue.PriorityQueue import PriorityQueue


class LabyrinthSolver:
    def __init__(self, labyrinth, method="bfs"):
        methods = ("bfs", "dfs", "greedy", "a_star")
        if method not in methods:
            raise ValueError(f"Method: {method} is not a valid method, available methods: {', '.join(methods)}.")

        self.labyrinth = labyrinth
        self.start = self.labyrinth.get_start()
        self.method = method

    def dfs_bfs_routine(self):
        stack = [self.start]
        visited = set()
        precedents = dict()

        while len(stack):
            if self.method == "bfs":
                # queue
                current = stack.pop(0)
            else:
                # stack
                current = stack.pop()

            if current == self.labyrinth.end_cell:
                return precedents, current, visited

            visited.add(current)
            neighbors = self.labyrinth.get_neighbours(*current)
            if self.method == "dfs":
                random.shuffle(neighbors)

            for neighbor in neighbors:
                if neighbor not in visited:
                    precedents[neighbor] = current
                    stack.append(neighbor)

        raise Exception("Unable to solve the maze!")

    def run(self, return_visited=False):
        # check of correctness of method is done in the constructor,
        # therefore the function always returns some value
        if self.method == "dfs" or self.method == "bfs":
           precedents, end, visited = self.dfs_bfs_routine()
        if self.method == "greedy":
            precedents, end, visited = self.greedy_routine()
        if self.method == "a_star":
            precedents, end, visited = self.a_star_routine()
        if return_visited:
            # noinspection PyUnboundLocalVariable
            return precedents, end, visited
        # noinspection PyUnboundLocalVariable
        return precedents, end

    def get_path(self, precedents, end_cell):
        path = []
        current = end_cell
        while current != self.start:
            path.append(current)
            current = precedents[current]

        return path

    def manhattan_distances(self):
        distances = [[0 for _ in range(self.labyrinth.end_x + 1)] for _ in range(self.labyrinth.end_y + 1)]
        for i, row in enumerate(self.labyrinth.graph):
            for j, cell in enumerate(row):
                distances[i][j] = abs(i - self.labyrinth.end_cell[0]) + abs(j - self.labyrinth.end_cell[1])
        return distances

    def greedy_routine(self):
        queue = PriorityQueue()
        queue.push(self.start, 0)
        visited = set()
        precedents = dict()
        distances = self.manhattan_distances()

        while not queue.is_empty():
            current, _ = queue.pop()
            visited.add(current)
            if current == self.labyrinth.end_cell:
                return precedents, current, visited

            neighbors = self.labyrinth.get_neighbours(*current)
            # random.shuffle(neighbors)

            for neighbor in neighbors:
                if neighbor not in visited:
                    precedents[neighbor] = current
                    queue.push(neighbor, distances[neighbor[0]][neighbor[1]])

        raise Exception("Unable to solve the maze!")

    def get_current_path_len(self, precedents, current):
        path = []
        while current != self.start:
            path.append(current)
            current = precedents[current]
        return len(path)

    def a_star_routine(self):
        queue = PriorityQueue()
        queue.push(self.start, 0)
        visited = set()
        precedents = dict()
        distances = self.manhattan_distances()

        while not queue.is_empty():
            current, _ = queue.pop()
            visited.add(current)
            if current == self.labyrinth.end_cell:
                return precedents, current, visited

            neighbors = self.labyrinth.get_neighbours(*current)
            # random.shuffle(neighbors)

            for neighbor in neighbors:
                if neighbor not in visited:
                    precedents[neighbor] = current
                    weight = self.get_current_path_len(precedents, current) + distances[neighbor[0]][neighbor[1]]
                    queue.push(neighbor, weight)

        raise Exception("Unable to solve the maze!")