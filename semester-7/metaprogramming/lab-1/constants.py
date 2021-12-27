from enum import Enum

import pygame

field_width = 25
field_height = 17
window_height = 20
cell_size = 50
field_width_pix = field_width * cell_size
field_height_pix = field_height * cell_size
window_height_pix = window_height * cell_size

class Color(Enum):
    BLACK = 0
    RED = 1
    BLUE = 2
    GRAY = 3
    YELLOW = 4

colors = [(0, 0, 0),
          (250, 50, 50), (200, 0, 0),       # RED
          (50, 50, 250), (0, 0, 200),       # BLUE
          (100, 100, 100), (40, 40, 40),    # GRAY
          (255, 255, 0)]                    # YELLOW (undefined)

def color(color_name):
    if color_name == Color.BLACK:
        return colors[0]
    elif color_name == Color.RED:
        return colors[1]
    elif color_name == Color.BLUE:
        return colors[3]
    elif color_name == Color.GRAY:
        return colors[5]
    else:
        return colors[7]




