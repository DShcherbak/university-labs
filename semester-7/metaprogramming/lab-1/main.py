import pygame
import objects
from constants import *

pygame.init()
screen = pygame.display.set_mode([cell_size * field_width, cell_size * window_height])
running = True

field = [[objects.Cell(x,y,False,'BLACK') for x in range(25)] for y in range(15)]

while running:

    for event in pygame.event.get(pygame.draw.rectangle(screen, (0, 0, 255), (250, 250), 75)):
        if event.type == pygame.QUIT:
            running = False
    screen.fill((255, 255, 255))

    for line in field:
        for cell in line:
            if cell.x == cell.y:
                pygame.draw.rectangle(screen, (10, 10, 10), cell.rect)
            else:
                pygame.draw.rectangle(screen, (200, 0, 0), cell.rect)

    pygame.display.flip()

pygame.quit()