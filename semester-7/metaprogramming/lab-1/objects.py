import pygame
from constants import *

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.blocked = x == 0 or y == 0 or x == field_width-1 or y == field_height-1
        self.under_construction = False
        self.rect = pygame.Rect(cell_size * x, cell_size * y, cell_size, cell_size)
        self.reset_color(Color.GRAY)

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)
        if self.blocked:
            pygame.draw.line(screen, color(Color.BLACK), (self.x * cell_size, self.y * cell_size), ((1 + self.x) * cell_size, (1 + self.y) * cell_size))
            pygame.draw.line(screen, color(Color.BLACK), ((1 + self.x) * cell_size, self.y * cell_size), (self.x * cell_size, (1 + self.y) * cell_size))

    def reset_color(self, new_color = Color.YELLOW):
        dim = 1 if self.blocked else 0
        if new_color == Color.BLACK:
            self.color = colors[0]
        elif new_color == Color.RED:
            self.color = colors[1 + dim]
        elif new_color == Color.BLUE:
            self.color = colors[3 + dim]
        elif new_color == Color.GRAY:
            self.color = colors[5 + dim]
        else:
            self.color = colors[7]

    def block(self, new_color):
        self.blocked = True
        self.reset_color(new_color)

class Arrow:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.width = 0
        self.visible = False
        self.vertical = False
        self.left_dead_end = True
        self.right_dead_end = True

    def init(self, pos):
        if (pos[0] < 0 or pos[1] < 0 or pos[0] > field_width_pix or pos[1] > field_height_pix):
            return
        else:
            x = (pos[0] // cell_size) * cell_size + cell_size // 2
            y = (pos[1] // cell_size) * cell_size + cell_size // 2
            self.x = x
            self.y = y
            self.width = cell_size // 2
            self.visible = True
            self.left_dead_end = False
            self.right_dead_end = False

    def draw(self, screen):
        if not self.visible:
            return
        if self.vertical:
            if not self.left_dead_end:
                pygame.draw.rect(screen, color(Color.RED), (self.x-cell_size//2, self.y - self.width, cell_size, self.width))
            if not self.right_dead_end:
                pygame.draw.rect(screen, color(Color.BLUE), (self.x-cell_size//2, self.y, cell_size, self.width))
        else:
            if not self.left_dead_end:
                pygame.draw.rect(screen, color(Color.RED), (self.x - self.width, self.y - cell_size // 2, self.width, cell_size))
            if not self.right_dead_end:
                pygame.draw.rect(screen, color(Color.BLUE), (self.x, self.y - cell_size // 2, self.width, cell_size))

    def grow(self, field):
        if self.left_dead_end and self.right_dead_end:
            self.visible = False
            return
        if (self.width + (cell_size // 2)) % cell_size == 0:
            if self.vertical:
                center = self.y // cell_size
                column = self.x // cell_size
                if not self.left_dead_end:
                    top = (self.y - (self.width + (cell_size // 2))) // cell_size - 1
                    if field[column][top].blocked:
                        self.left_dead_end = True
                        for cell_y in range(top + 1, self.y // cell_size):
                            field[column][cell_y].block(Color.RED)
                        if field[column][center].blocked == True:
                            field[column][center].reset_color(Color.YELLOW)
                        else:
                            field[column][center].block(Color.RED)
                if not self.right_dead_end:
                    bottom = (self.y + (self.width + (cell_size // 2))) // cell_size
                    if field[column][bottom].blocked:
                        self.right_dead_end = True
                        for cell_y in range(bottom - 1, self.y // cell_size, -1):
                            field[column][cell_y].block(Color.BLUE)
                        if field[column][center].blocked == True:
                            field[column][center].reset_color(Color.YELLOW)
                        else:
                            field[column][center].block(Color.BLUE)
            else:
                center = self.x // cell_size
                row = self.y // cell_size
                if not self.left_dead_end:
                    left = (self.x - (self.width + (cell_size // 2))) // cell_size -1
                    if field[left][row].blocked:
                        self.left_dead_end = True
                        for cell_x in range(left + 1, self.x // cell_size):
                            field[cell_x][row].block(Color.RED)
                        if field[center][row].blocked == True:
                            field[center][row].reset_color(Color.YELLOW)
                        else:
                            field[center][row].block(Color.RED)
                if not self.right_dead_end:
                    right = (self.x + (self.width + (cell_size // 2))) // cell_size
                    if field[right][row].blocked:
                        self.right_dead_end = True
                        for cell_x in range(right - 1, self.x // cell_size, -1):
                            field[cell_x][row].block(Color.BLUE)
                        if field[center][row].blocked == True:
                            field[center][row].reset_color(Color.YELLOW)
                        else:
                            field[center][row].block(Color.BLUE)




        self.width = self.width + 1


    def flip_vertical(self):
        self.vertical = not self.vertical