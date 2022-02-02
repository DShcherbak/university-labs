import pygame

from constants import *


p = 4
q = 7
left_x = field_width_pix // p
button_width = 2 * field_width_pix // p
button_height = window_height_pix // q


class Menu:

    def __init__(self):
        self.game_y = 1 * window_height_pix // q
        self.cred_y = 3 * window_height_pix // q
        self.quit_y = 5 * window_height_pix // q
        self.font = pygame.font.Font(pygame.font.get_default_font(), 36)

    def draw(self, screen):
        pygame.draw.rect(screen, (50, 50, 50), (0, 0, field_width_pix, window_height_pix))

        pygame.draw.rect(screen, (100, 100, 100), (left_x, self.game_y, button_width,  button_height ))
        pygame.draw.rect(screen, (100, 100, 100), (left_x, self.cred_y, button_width,  button_height ))
        pygame.draw.rect(screen, (100, 100, 100), (left_x, self.quit_y, button_width,  button_height ))

        # now print the text
        font = self.font
        text_surface = font.render('Start game', True, (0, 0, 0))
        screen.blit(text_surface, dest=(left_x + button_width // 2 - 9*9, self.game_y + button_height// 2 - 18))

        text_surface2 = font.render('How to play', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(left_x + button_width // 2 - 9*11, self.cred_y + button_height// 2 - 18))

        text_surface3 = font.render('Quit', True, (0, 0, 0))
        screen.blit(text_surface3, dest=(left_x + button_width // 2 - 18*2, self.quit_y + button_height// 2 - 18))

    def is_quit_button(self, x, y):
        return (left_x <= x <= left_x + button_width) and (self.quit_y <= y <= self.quit_y + button_height)

    def is_credentials_button(self, x, y):
        return (left_x <= x <= left_x + button_width) and (self.cred_y <= y <= self.cred_y + button_height)

    def isGameButton(self, x, y):
        return (left_x <= x <= left_x + button_width) and (self.game_y <= y <= self.game_y + button_height)


class Restart:

    def __init__(self):
        self.restart_y = 3 * window_height_pix // q
        self.quit_y = 5 * window_height_pix // q
        self.font = pygame.font.Font(pygame.font.get_default_font(), 36)

    def draw(self, screen):
        pygame.draw.rect(screen, (200, 50, 50), (0, 0, field_width_pix, window_height_pix))
        pygame.draw.rect(screen, (100, 100, 100), (left_x, self.restart_y, button_width,  button_height ))
        pygame.draw.rect(screen, (100, 100, 100), (left_x, self.quit_y, button_width,  button_height ))
        #pygame.draw(screen, (100, 100, 100), (field_width_pix // p, 5 * window_height_pix // q, 2 * field_width_pix // p,  window_height_pix // q))
        #pygame.draw.rect(screen, (100, 100, 100), (field_width_pix // p, 5 * window_height_pix // q, 2 * field_width_pix // p, 6 * window_height_pix // q))

        caps = pygame.font.Font(pygame.font.get_default_font(), 72)
        text_surface = caps.render('Game over', True, (0, 0, 0))
        screen.blit(text_surface, dest=(left_x + button_width // 2 - 9 * 20, button_height // 2 + 36))

        font = self.font
        text_surface2 = font.render('Restart', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(left_x + button_width // 2 - 9 * 6, self.restart_y + button_height // 2 - 18))

        text_surface3 = font.render('Quit', True, (0, 0, 0))
        screen.blit(text_surface3, dest=(left_x + button_width // 2 - 18 * 2, self.quit_y + button_height // 2 - 18))

    def is_quit_button(self, x, y):
        return (left_x <= x <= left_x + button_width) and (self.quit_y <= y <= self.quit_y + button_height)

    def is_restart_button(self, x, y):
        return (left_x <= x <= left_x + button_width) and (self.restart_y <= y <= self.restart_y + button_height)


class Creds:

    def __init__(self):
        self.restart_y = 3 * window_height_pix // q
        self.quit_y = 5 * window_height_pix // q
        self.font = pygame.font.Font(pygame.font.get_default_font(), 34)

    def draw(self, screen):
        pygame.draw.rect(screen, (100, 100, 100), (0, 0, field_width_pix, window_height_pix))

        caps = pygame.font.Font(pygame.font.get_default_font(), 72)
        text_surface = caps.render('How to play', True, (0, 0, 0))
        screen.blit(text_surface, dest=(left_x + button_width // 2 - 9 * 20, button_height // 2 + 36))

        font = self.font
        text_surface2 = font.render('Натисніть лівою кнопкою миші, щоб почати будувати стіну.', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(20, button_height // 2 + 150))

        text_surface2 = font.render('Міняйте напрям побудови стіни, натискаючи на пробіл.', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(20, button_height // 2 + 250))

        text_surface2 = font.render('Якщо кулька стикається з недобудованою стіною, ви втрачаєте життя.', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(20, button_height // 2 + 350))

        text_surface2 = font.render('Захопіть 75% поля, щоб пройти рівень.', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(20, button_height // 2 + 450))

        text_surface2 = font.render('Натисніть Esc щоб вийти.', True, (0, 0, 0))
        screen.blit(text_surface2, dest=(20, button_height // 2 + 550))
