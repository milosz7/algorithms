from labyrinth_generation.LabyrinthGenerator import LabyrinthGenerator
import pygame


class WrongInputError(Exception):
    pass


def main():
    CELL_SIZE = 50
    FPS = 5
    WHITE = (255, 255, 255)

    while True:
        try:
            width = int(input("Enter the width of the labyrinth: "))
            height = int(input("Enter the height of the labyrinth: "))
            generate_image = input("Do you want to generate an image of the labyrinth? (y/n): ")
            if generate_image not in ['y', 'n']:
                raise WrongInputError
            if width < 3 or height < 3:
                raise ValueError
            break
        except ValueError:
            print("Invalid input. Please enter a positive integer greater than 2")
        except WrongInputError:
            print("Invalid input. Please enter 'y' or 'n'")

    SCREEN_WIDTH = CELL_SIZE * width
    SCREEN_HEIGHT = CELL_SIZE * height

    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("DFS Maze Generator Visualization")
    clock = pygame.time.Clock()

    generator = LabyrinthGenerator(width, height)
    screen.fill(WHITE)

    while True:
        for step in generator.generate(steps=True):
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    return
            screen.fill(WHITE)
            draw_labyrinth(step, screen)
            pygame.display.flip()
            clock.tick(FPS)

        if generate_image == 'y':
            generator.draw_labyrinth_image()
            break


def draw_labyrinth(labyrinth, screen, color=(0, 0, 0)):
    cell_size = 50
    draw = pygame.draw
    for row in labyrinth:
        for cell in row:
            x0 = cell.x * cell_size
            y0 = cell.y * cell_size
            x1 = x0 + cell_size
            y1 = y0 + cell_size
            if cell.left_wall:
                draw.line(screen, color, (x0, y0), (x0, y1), 2)
            if cell.right_wall:
                draw.line(screen, color, (x1, y0), (x1, y1), 2)
            if cell.top_wall:
                draw.line(screen, color, (x0, y0), (x1, y0), 2)
            if cell.bottom_wall:
                draw.line(screen, color, (x0, y1), (x1, y1), 2)
    pygame.display.flip()


if __name__ == '__main__':
    main()
