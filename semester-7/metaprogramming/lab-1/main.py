import pygame

import additional_drawing
from objects import *
from constants import *

def main():
    pygame.init()
    screen = pygame.display.set_mode([field_width_pix, window_height_pix])
    running = True
    arrow = Arrow()

    field = [[Cell(x,y) for y in range(field_height)] for x in range(field_width)]

    while running:

        arrow.grow(field)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if not arrow.visible:
                    arrow.init(pygame.mouse.get_pos())
            elif event.type == pygame.KEYDOWN:
                if not arrow.visible and event.key == pygame.K_SPACE:
                    arrow.flip_vertical()

        additional_drawing.redraw(screen, field, arrow)

        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()