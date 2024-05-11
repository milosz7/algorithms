import random


class LabyrinthSolver:
    def __init__(self, labyrinth, method="bfs"):
        methods = ("bfs", "dfs")
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

            visited.add(current)
            neighbors = self.labyrinth.get_neighbours(*current)
            random.shuffle(neighbors)

            for neighbor in neighbors:
                if neighbor not in visited:
                    precedents[neighbor] = current
                    stack.append(neighbor)
                    if self.labyrinth.get_cell(*neighbor) == self.labyrinth.end_value:
                        return precedents, neighbor

        raise Exception("Unable to solve the maze!")

    def run(self):
        if self.method == "dfs" or self.method == "bfs":
            return self.dfs_bfs_routine()

    def get_path(self, precedents, end_cell):
        path = []
        current = end_cell
        while current != self.start:
            path.append(current)
            current = precedents[current]

        return path
