import pygame

import additional_drawing
from objects import *
from menu import *

def main():
    pygame.init()
    screen = pygame.display.set_mode([field_width_pix, window_height_pix])
    running = True
    arrow = Arrow()
    game = Game()
    game.screen = screen
    menu = Menu()

    game.increment_level()

    while running:
        if game.state == "Game":
            arrow.grow(game)
            for ball in game.field.balls:
                ball.move(game, arrow)

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if not arrow.visible:
                        arrow.init(pygame.mouse.get_pos(), game)
                elif event.type == pygame.KEYDOWN:
                    if not arrow.visible and event.key == pygame.K_SPACE:
                        arrow.flip_vertical()

            additional_drawing.redraw(screen, game, arrow)
        else:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    (x,y) = pygame.mouse.get_pos()
                    if menu.is_quit_button(x,y):
                        running = False
                    elif menu.is_credentials_button(x,y):
                        game.state = "Creds"
                    elif menu.isGameButton(x,y):
                        game.state = "Game"
            menu.draw(screen)
        pygame.display.flip()

    pygame.quit()

if __name__ == "__main__":
    main()