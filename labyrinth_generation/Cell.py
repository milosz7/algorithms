class Cell:
    def __init__(self, x, y):
        self.left_wall = True
        self.right_wall = True
        self.top_wall = True
        self.bottom_wall = True
        self.x = x
        self.y = y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def remove_wall(self, other):
        dx = other.x - self.x
        dy = other.y - self.y
        if dx == 1:
            self.right_wall = False
            other.left_wall = False
        elif dx == -1:
            self.left_wall = False
            other.right_wall = False
        elif dy == 1:
            self.bottom_wall = False
            other.top_wall = False
        elif dy == -1:
            self.top_wall = False
            other.bottom_wall = False
