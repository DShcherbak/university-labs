import pygame

import additional_drawing
from objects import *
from menu import *

def main():
    pygame.init()
    screen = pygame.display.set_mode([field_width_pix, window_height_pix])
    arrow = Arrow()
    game = Game()
    game.screen = screen
    menu = Menu()
    restart_menu = Restart()


    while game.running:
        if game.state == "Game":
            arrow.grow(game)
            for ball in game.field.balls:
                ball.move(game, arrow)
            if game.lives <= 0:
                game.over()
                arrow = Arrow()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game.quit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if not arrow.visible:
                        arrow.init(pygame.mouse.get_pos(), game)
                elif event.type == pygame.KEYDOWN:
                    if not arrow.visible and event.key == pygame.K_SPACE:
                        arrow.flip_vertical()

            additional_drawing.redraw(screen, game, arrow)
        elif game.state == "Menu":
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game.quit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    (x,y) = pygame.mouse.get_pos()
                    if menu.is_quit_button(x,y):
                        game.quit()
                    elif menu.is_credentials_button(x,y):
                        game.state = "Creds"
                    elif menu.isGameButton(x,y):
                        game.state = "Game"
            menu.draw(screen)
        else:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game.quit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    (x,y) = pygame.mouse.get_pos()
                    if restart_menu.is_quit_button(x,y):
                        game.quit()
                    elif restart_menu.is_restart_button(x,y):
                        game = Game()
                        game.state = "Game"
            restart_menu.draw(screen)
        pygame.display.flip()
    pygame.quit()

if __name__ == "__main__":
    main()