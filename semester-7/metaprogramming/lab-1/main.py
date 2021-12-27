import pygame

import additional_drawing
from objects import *
from constants import *

def main():
    pygame.init()
    screen = pygame.display.set_mode([field_width_pix, window_height_pix])
    running = True
    arrow = Arrow()
    level = 16

    field = [[Cell(x,y) for y in range(field_height)] for x in range(field_width)]
    balls = [Ball() for _ in range(level + 1)]

    while running:

        arrow.grow(field)
        for ball in balls:
            ball.move(field, arrow)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if not arrow.visible:
                    arrow.init(pygame.mouse.get_pos())
            elif event.type == pygame.KEYDOWN:
                if not arrow.visible and event.key == pygame.K_SPACE:
                    arrow.flip_vertical()

        additional_drawing.redraw(screen, field, arrow, balls)

        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()