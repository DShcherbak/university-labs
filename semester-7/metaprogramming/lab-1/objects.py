from pygame import Rect

class Cell:
    def __init__(self,x,y,taken,color):
        self.x = x
        self.y = y
        self.taken = taken
        self.color = color
        self.building = False
        self.rect = Rect()

    