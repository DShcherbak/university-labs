import pygame

from constants import *


class Menu:

    def __init__(self):
        p = 4
        q = 7
        self.left_x = field_width_pix // p
        self.button_width = 2 * field_width_pix // p
        self.button_height = window_height_pix // q
        self.game_y = 1 * window_height_pix // q
        self.cred_y = 3 * window_height_pix // q
        self.quit_y = 5 * window_height_pix // q

    def draw(self, screen):
        pygame.draw.rect(screen, (50, 50, 50), (0, 0, field_width_pix, window_height_pix))

        pygame.draw.rect(screen, (100, 100, 100), (self.left_x, self.game_y, self.button_width,  self.button_height ))
        pygame.draw.rect(screen, (100, 100, 100), (self.left_x, self.cred_y, self.button_width,  self.button_height ))
        pygame.draw.rect(screen, (100, 100, 100), (self.left_x, self.quit_y, self.button_width,  self.button_height ))
        #pygame.draw(screen, (100, 100, 100), (field_width_pix // p, 5 * window_height_pix // q, 2 * field_width_pix // p,  window_height_pix // q))
        #pygame.draw.rect(screen, (100, 100, 100), (field_width_pix // p, 5 * window_height_pix // q, 2 * field_width_pix // p, 6 * window_height_pix // q))

    def is_quit_button(self, x, y):
        return (self.left_x <= x <= self.left_x + self.button_width) and (self.quit_y <= y <= self.quit_y + self.button_height)

    def is_credentials_button(self, x, y):
        return (self.left_x <= x <= self.left_x + self.button_width) and (self.cred_y <= y <= self.cred_y + self.button_height)

    def isGameButton(self, x, y):
        return (self.left_x <= x <= self.left_x + self.button_width) and (self.game_y <= y <= self.game_y + self.button_height)
