import pygame
from constants import *



def redraw(screen, field, arrow):
    for line in field:
        for cell in line:
            cell.draw(screen)
    draw_lines(screen)
    if arrow.visible:
        arrow.draw(screen)

def draw_lines(screen):
    for x in range(field_width):
        pygame.draw.line(screen, color(Color.BLACK), (x * cell_size, 0), (x * cell_size, field_height * cell_size))
    for y in range(field_height):
        pygame.draw.line(screen, color(Color.BLACK), (0, y * cell_size), (field_width * cell_size, y * cell_size))