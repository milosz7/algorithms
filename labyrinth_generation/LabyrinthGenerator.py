import random
from PIL import Image, ImageDraw
from labyrinth_generation.Cell import Cell


class LabyrinthGenerator:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.labyrinth = [[Cell(x, y) for x in range(width)] for y in range(height)]
        self.visited = [[False for _ in range(width)] for _ in range(height)]

    def generate(self):
        current = self.labyrinth[0][0]
        self.visited[current.y][current.x] = True
        stack = [current]

        while stack:
            current = stack.pop()
            neighbors = self.get_neighbors(current)
            if neighbors:
                random.shuffle(neighbors)
                for neighbor in neighbors:
                    if not self.visited[neighbor.y][neighbor.x]:
                        current.remove_wall(neighbor)
                        self.visited[neighbor.y][neighbor.x] = True
                        stack.append(neighbor)

    def get_neighbors(self, cell):
        neighbors = []
        x, y = cell.x, cell.y
        if x > 0:
            neighbors.append(self.labyrinth[y][x - 1])
        if y > 0:
            neighbors.append(self.labyrinth[y - 1][x])
        if x < self.width - 1:
            neighbors.append(self.labyrinth[y][x + 1])
        if y < self.height - 1:
            neighbors.append(self.labyrinth[y + 1][x])
        return neighbors

    def draw_labyrinth(self):
        cell_size = 50
        b_width = 2
        img = Image.new('RGB', (self.width * cell_size + 2, self.height * cell_size + 2), color='white')
        draw = ImageDraw.Draw(img)
        for i, row in enumerate(self.labyrinth):
            for j, cell in enumerate(row):
                x0 = j * cell_size
                y0 = i * cell_size
                x1 = x0 + cell_size
                y1 = y0 + cell_size

                if cell.top_wall:
                    if cell.x == 0 and cell.y == 0:
                        draw.line([(x0, y0), (x1, y0)], fill='green', width=b_width)
                    else:
                        draw.line([(x0, y0), (x1, y0)], fill='black', width=b_width)
                if cell.bottom_wall:
                    if cell.x == self.width - 1 and cell.y == self.height - 1:
                        draw.line([(x0, y1), (x1, y1)], fill='red', width=b_width)
                    else:
                        draw.line([(x0, y1), (x1, y1)], fill='black', width=b_width)
                if cell.left_wall:
                    draw.line([(x0, y0), (x0, y1)], fill='black', width=b_width)
                if cell.right_wall:
                    draw.line([(x1, y0), (x1, y1)], fill='black', width=b_width)
        img.show()
