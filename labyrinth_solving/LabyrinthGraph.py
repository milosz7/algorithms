from PIL import Image, ImageDraw


class LabyrinthGraph:
    def __init__(self, filename, wall=0, path=1, start=2, end=3):
        self.graph = []
        self.wall_value = wall
        self.path_value = path
        self.start_value = start
        self.end_value = end
        self.start_cell = None
        self.end_cell = None

        with open(filename, 'r') as f:
            for i, line in enumerate(f.read().splitlines()):
                cells = line.split(";")
                row = []
                for j, cell in enumerate(cells):
                    cell = int(cell)
                    row.append(cell)
                    if cell == self.start_value:
                        self.start_cell = (i, j)
                    if cell == self.end_value:
                        self.end_cell = (i, j)
                self.graph.append(row)

        self.end_x = len(self.graph[0]) - 1
        self.end_y = len(self.graph) - 1

    def __str__(self):
        out = ""
        for row in self.graph:
            out += (";".join((str(cell) for cell in row)) + "\n")

        print(self.start_cell, self.end_cell, self.end_x, self.end_y)
        return out

    def get_cell(self, i, j):
        return self.graph[i][j]

    def get_start(self):
        return self.start_cell

    def get_end_value(self):
        return self.end_value

    def get_neighbours(self, i, j):
        neighbours = []
        if i != 0:
            top_cell = (i-1, j)
            if self.get_cell(*top_cell):
                neighbours.append(top_cell)
        if j != 0:
            left_cell = (i, j-1)
            if self.get_cell(*left_cell):
                neighbours.append(left_cell)
        if j != self.end_x:
            right_cell = (i, j+1)
            if self.get_cell(*right_cell):
                neighbours.append(right_cell)
        if i != self.end_y:
            bottom_cell = (i+1, j)
            if self.get_cell(*bottom_cell):
                neighbours.append(bottom_cell)

        return neighbours

    def draw_labyrinth(self, path=None):
        width = len(self.graph[0])
        height = len(self.graph)
        cell_size = 50
        img = Image.new('RGB', (width * cell_size, height * cell_size), color='white')
        draw = ImageDraw.Draw(img)
        for i, row in enumerate(self.graph):
            for j, cell in enumerate(row):
                x0 = j * cell_size
                y0 = i * cell_size
                x1 = x0 + cell_size
                y1 = y0 + cell_size
                if cell == self.wall_value:
                    draw.rectangle((x0, y0, x1, y1), fill='black')
                elif cell == self.start_value:
                    draw.rectangle((x0, y0, x1, y1), fill='green')
                elif cell == self.end_value:
                    draw.rectangle((x0, y0, x1, y1), fill='red')
                elif path and (i, j) in path:
                    draw.rectangle((x0, y0, x1, y1), fill='blue')
        img.show()
