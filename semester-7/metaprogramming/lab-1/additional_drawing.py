import pygame
from constants import *



def redraw(screen, game, arrow):
    game.draw(screen)
    # draw_lines(screen)
    if arrow.visible:
        arrow.draw(screen)


