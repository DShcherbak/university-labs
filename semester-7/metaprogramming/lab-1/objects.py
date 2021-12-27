import math

import pygame
from constants import *
from random import randint


balls_speed = 1
arrow_speed = 1
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
                        if not field[column][center].blocked:
                            field[column][center].block(Color.RED)
                if not self.right_dead_end:
                    bottom = (self.y + (self.width + (cell_size // 2))) // cell_size
                    if field[column][bottom].blocked:
                        self.right_dead_end = True
                        for cell_y in range(bottom - 1, self.y // cell_size, -1):
                            field[column][cell_y].block(Color.BLUE)
                        if not field[column][center].blocked:
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
                        if not field[center][row].blocked:
                            field[center][row].block(Color.RED)
                if not self.right_dead_end:
                    right = (self.x + (self.width + (cell_size // 2))) // cell_size
                    if field[right][row].blocked:
                        self.right_dead_end = True
                        for cell_x in range(right - 1, self.x // cell_size, -1):
                            field[cell_x][row].block(Color.BLUE)
                        if not field[center][row].blocked:
                            field[center][row].block(Color.BLUE)




        self.width = self.width + arrow_speed


    def flip_vertical(self):
        self.vertical = not self.vertical

class Ball:
    def __init__(self):
        self.xf = float(randint(cell_size + radius, field_width_pix-cell_size-radius))
        self.yf = float(randint(cell_size + radius, field_height_pix-cell_size-radius))
        self.angle = 2 * math.pi * randint(0,360) / 360
        self.set_coordinates()

    def set_coordinates(self):
        self.x = int(self.xf)
        self.y = int(self.yf)

    def draw(self, screen):
        pygame.draw.circle(screen, color(Color.YELLOW), (self.x, self.y), radius)

    def move(self, field, arrow):
        self.xf = self.xf + balls_speed * math.cos(self.angle)
        self.yf = self.yf + balls_speed * math.sin(self.angle)
        self.set_coordinates()

        row = self.y // cell_size
        column = self.x // cell_size

        if (3 * math.pi / 2 > self.angle > math.pi / 2) and (balls_speed >= (radius - (self.x % cell_size))) >= 0:
            left = (self.x - radius) // cell_size # - 1 if self.x % cell_size == radius else 0
            if field[left][row].blocked:
                self.angle = left_right_change_angle(self.angle)


        if ((self.angle > 3 * math.pi / 2) or  (self.angle < math.pi / 2)) and (balls_speed >= (radius - (cell_size - (self.x % cell_size)))) >= 0:
            right = (self.x + radius) // cell_size
            if field[right][row].blocked:
                self.angle = left_right_change_angle(self.angle)

        if (self.angle > math.pi) and (balls_speed >= (radius - (self.y % cell_size))) >= 0:
            top = (self.y - radius) // cell_size
            if field[column][top].blocked:
                self.angle = top_bottom_change_angle(self.angle)


        if (self.angle < math.pi) and (balls_speed >= (radius - (cell_size - (self.y % cell_size)))) >= 0:
            bottom = (self.y + radius) // cell_size
            if field[column][bottom].blocked:
                self.angle = top_bottom_change_angle(self.angle)


def left_right_change_angle(angle):
    if angle < math.pi:
        return math.pi - angle
    else:
        return 2 * math.pi - (angle - math.pi)


def top_bottom_change_angle(angle):
    return math.pi * 2 - angle
