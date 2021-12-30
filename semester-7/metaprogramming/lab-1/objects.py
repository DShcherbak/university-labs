import math

import pygame
from constants import *
from random import randint
from queue import Queue


balls_speed = 1
arrow_speed = 1

class Field:
    def __init__(self):
        self.cells = []
    
    def recount_free_cells(self, balls):
        rectangles = self.bfs_start()
        free_spaces = self.count_walls()
        for (x1, y1, x2, y2) in rectangles:
            free = True
            for ball in balls:
                if (x1 <= ball.x <= x2) and (y1 <= ball.y <= y2):
                    free = False
            if free:
                free_spaces += (x2 - x1 + 1) * (y2 - y1 + 1)

        print(free_spaces / (field_height * field_width))

    def count_walls(self):
        result = 0
        for y in range(field_height):
            for x in range(field_width):  
                result += 1 if self.cells[x][y].blocked else 0

    def bfs_start(self):
        result = []
        visited = [[False for _ in range(field_height)] for _ in range(field_width)]

        for y in range(field_height):
            for x in range(field_width):
                if not visited[x][y]:
                    result.append(self.bfs(x,y,visited))
        return result

    def bfs(self, xs, ys, visited):
        queue = Queue()
        queue.put((xs,ys))
        rect = (xs,ys,xs,ys)
        while not queue.empty():
            (x,y) = queue.get()
            if x < rect[0]: 
                rect = (x, rect[1], rect[2], rect[3])
            if x > rect[2]: 
                rect = (rect[0], rect[1], x, rect[3])
            if y < rect[1]: 
                rect = (rect[0], y, rect[2], rect[3]) 
            if y > rect[3]: 
                rect = (rect[0], rect[1], rect[2], y) 
            visited[x][y] = True
            for d1 in range(-1, 1):
                for d2 in range(-1, 1):
                    (x1, y1) = (x + d1, x + d2)
                    if not visited[x1][y1]:
                        queue.put((x1,y1))
        return rect      


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
        self.left_hand_free = True
        self.right_hand_free = True


    def init(self, pos):
        if (pos[0] < 0 or pos[1] < 0 or pos[0] > field_width_pix or pos[1] > field_height_pix):
            return
        else:
            x = (pos[0] // cell_size) * cell_size + half_cell
            y = (pos[1] // cell_size) * cell_size + half_cell
            self.x = x
            self.y = y
            self.width = half_cell
            self.visible = True
            self.left_hand_free = False
            self.right_hand_free = False


    def draw(self, screen):
        if not self.visible:
            return
        if self.vertical:
            if not self.left_hand_free:
                pygame.draw.rect(screen, color(Color.RED), (self.x-half_cell, self.y - self.width, cell_size, self.width))
            if not self.right_hand_free:
                pygame.draw.rect(screen, color(Color.BLUE), (self.x-half_cell, self.y, cell_size, self.width))
        else:
            if not self.left_hand_free:
                pygame.draw.rect(screen, color(Color.RED), (self.x - self.width, self.y - half_cell, self.width, cell_size))
            if not self.right_hand_free:
                pygame.draw.rect(screen, color(Color.BLUE), (self.x, self.y - half_cell, self.width, cell_size))


    def grow(self, field):
        if self.left_hand_free and self.right_hand_free:
            self.visible = False
            return
        if (self.width + (half_cell)) % cell_size == 0:
            if self.vertical:
                center = self.y // cell_size
                column = self.x // cell_size
                if not self.left_hand_free:
                    top = (self.y - (self.width + (half_cell))) // cell_size - 1
                    if field.cells[column][top].blocked:
                        self.left_hand_free = True
                        field.recount_free_cells()
                        for cell_y in range(top + 1, self.y // cell_size):
                            field.cells[column][cell_y].block(Color.RED)
                        if not field.cells[column][center].blocked:
                            field.cells[column][center].block(Color.RED)
                if not self.right_hand_free:
                    bottom = (self.y + (self.width + (half_cell))) // cell_size
                    if field.cells[column][bottom].blocked:
                        self.right_hand_free = True
                        field.recount_free_cells()
                        for cell_y in range(bottom - 1, self.y // cell_size, -1):
                            field.cells[column][cell_y].block(Color.BLUE)
                        if not field.cells[column][center].blocked:
                            field.cells[column][center].block(Color.BLUE)
            else:
                center = self.x // cell_size
                row = self.y // cell_size
                if not self.left_hand_free:
                    left = (self.x - (self.width + (half_cell))) // cell_size -1
                    if field.cells[left][row].blocked:
                        self.left_hand_free = True
                        field.recount_free_cells()
                        for cell_x in range(left + 1, self.x // cell_size):
                            field.cells[cell_x][row].block(Color.RED)
                        if not field.cells[center][row].blocked:
                            field.cells[center][row].block(Color.RED)
                if not self.right_hand_free:
                    right = (self.x + (self.width + (half_cell))) // cell_size
                    if field.cells[right][row].blocked:
                        self.right_hand_free = True
                        field.recount_free_cells()
                        for cell_x in range(right - 1, self.x // cell_size, -1):
                            field.cells[cell_x][row].block(Color.BLUE)
                        if not field.cells[center][row].blocked:
                            field.cells[center][row].block(Color.BLUE)  
        self.width = self.width + arrow_speed
    

    def left_part(self):
        if self.vertical:
            return (self.x - half_cell, self.y - half_cell - self.width, self.x + half_cell, self.y) 
        else:
            return (self.x - half_cell - self.width, self.y - half_cell , self.x, self.y + half_cell)   


    def right_part(self):
        if self.vertical:
            return (self.x - half_cell, self.y, self.x + half_cell, self.y + half_cell + self.width) 
        else:
            return (self.x, self.y - half_cell, self.x + half_cell + self.width, self.y + half_cell)   


    def left_strike(self):
        self.left_hand_free = True
        if self.right_hand_free:
            self.visible = False
            self.width = 0


    def right_strike(self):
        self.right_hand_free = True
        if self.left_hand_free:
            self.visible = False
            self.width = 0


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
            if field.cells[left][row].blocked:
                self.angle = left_right_change_angle(self.angle)


        if ((self.angle > 3 * math.pi / 2) or  (self.angle < math.pi / 2)) and (balls_speed >= (radius - (cell_size - (self.x % cell_size)))) >= 0:
            right = (self.x + radius) // cell_size
            if field.cells[right][row].blocked:
                self.angle = left_right_change_angle(self.angle)

        if (self.angle > math.pi) and (balls_speed >= (radius - (self.y % cell_size))) >= 0:
            top = (self.y - radius) // cell_size
            if field.cells[column][top].blocked:
                self.angle = top_bottom_change_angle(self.angle)


        if (self.angle < math.pi) and (balls_speed >= (radius - (cell_size - (self.y % cell_size)))) >= 0:
            bottom = (self.y + radius) // cell_size
            if field.cells[column][bottom].blocked:
                self.angle = top_bottom_change_angle(self.angle)

        self.check_collision_with_arrow(arrow)


    def check_collision_with_arrow(self, arrow):
        if not arrow.left_hand_free:
            (x1, y1, x2, y2) = arrow.left_part()
            if (x1 <= self.x <= x2) and (y1 <= self.y - radius <= self.y + radius <= y2):
                arrow.left_strike()
            elif (x1 <= self.x - radius <= self.x + radius <= x2) and (y1 <= self.y <= y2):
                arrow.left_strike()
            elif self.collides_with_point(x1,y1):
                arrow.left_strike()
            elif self.collides_with_point(x2,y1):
                arrow.left_strike()
            elif self.collides_with_point(x1,y2):
                arrow.left_strike()
            elif self.collides_with_point(x2,y2):
                arrow.left_strike()
        if not arrow.right_hand_free:
            (x1, y1, x2, y2) = arrow.right_part()
            if (x1 <= self.x <= x2) and (y1 <= self.y - radius <= self.y + radius <= y2):
                arrow.right_strike()
            elif (x1 <= self.x - radius <= self.x + radius <= x2) and (y1 <= self.y <= y2):
                arrow.right_strike()
            elif self.collides_with_point(x1,y1):
                arrow.right_strike()
            elif self.collides_with_point(x2,y1):
                arrow.right_strike()
            elif self.collides_with_point(x1,y2):
                arrow.right_strike()
            elif self.collides_with_point(x2,y2):
                arrow.right_strike()
                

    def collides_with_point(self, x, y):
        return math.sqrt((self.x - x)**2 + (self.y - y)**2) <= radius


def left_right_change_angle(angle):
    if angle < math.pi:
        return math.pi - angle
    else:
        return 2 * math.pi - (angle - math.pi)


def top_bottom_change_angle(angle):
    return math.pi * 2 - angle
