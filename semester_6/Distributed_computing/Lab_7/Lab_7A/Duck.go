package main

import (
	ebiten "github.com/hajimehoshi/ebiten/v2"
	"image"
	"math/rand"
)

type Frame struct {
	x         int
	y         int
	sizeX     int
	sizeY     int
	nextFrame *Frame
}

var (
	frames      map[int]map[string]*Frame
	duckSprites *ebiten.Image
)

const (
	topMargin = 118
	duckX     = 38
	duckY     = 37
	gap       = 15
)

func defaultFrame(x, y int, nextFrame *Frame) *Frame {
	return &Frame{
		x:         x,
		y:         y,
		sizeX:     duckX,
		sizeY:     duckY,
		nextFrame: nextFrame,
	}
}

func createTrio(x, y int) *Frame {
	third := defaultFrame(x+2*duckX, y, nil)
	second := defaultFrame(x+duckX, y, third)
	first := defaultFrame(x, y, second)
	third.nextFrame = first
	return first
}

func initialiseFrames() {
	frames = make(map[int]map[string]*Frame)
	frames[1] = make(map[string]*Frame)
	frames[2] = make(map[string]*Frame)
	frames[3] = make(map[string]*Frame)
	for duckType := 1; duckType <= 3; duckType++ {
		duckTypeX := (duckType - 1) * (duckX*3 + gap)
		left := createTrio(duckTypeX, topMargin)
		frames[duckType]["W"] = left
		diagonal := createTrio(duckTypeX, topMargin+duckY)
		frames[duckType]["NW"] = diagonal
		top := createTrio(duckTypeX, topMargin+duckY*2)
		frames[duckType]["N"] = top
		shot := defaultFrame(duckTypeX, topMargin+duckY*3, nil)
		frames[duckType]["O"] = shot
		dead := defaultFrame(duckTypeX+duckX, topMargin+duckY*3, nil)
		shot.nextFrame = dead
		dead.nextFrame = dead
		frames[duckType]["X"] = dead
	}
}

type Duck struct {
	frame *Frame

	x int
	y int

	speed     int
	direction int

	duckType int

	isGarbage bool
	isDead    bool
}

func (duck *Duck) getImage() *ebiten.Image {
	frame := duck.frame
	return duckSprites.SubImage(image.Rect(frame.x, frame.y, frame.x+frame.sizeX, frame.y+frame.sizeY)).(*ebiten.Image)
}

func (duck *Duck) isHit(x, y int) bool {
	return x > duck.x && x < duck.x+duckX && y > duck.y && y < duck.y+duckY
}

func (duck *Duck) kill() {
	duck.direction = 0
	duck.setSpeed(0)
	duck.isDead = true
}

func (duck *Duck) setSpeed(speed int) {
	duck.speed = speed
	switch speed {
	case 1:
		duck.frame = frames[duck.duckType]["W"]
		break
	case 2:
		duck.frame = frames[duck.duckType]["NW"]
		break
	case 3:
		duck.frame = frames[duck.duckType]["N"]
		break
	case 0:
		duck.frame = frames[duck.duckType]["O"]
		break
	case 10:
		duck.frame = frames[duck.duckType]["X"]
		break
	default:
		duck.frame = frames[duck.duckType]["N"]
		break
	}
}

func (duck *Duck) changeDirection() {
	speed := duck.speed
	if speed == 0 {
		return
	}
	direction := duck.direction
	decision := rand.Intn(2) == 1
	if speed == 1 {
		if decision {
			duck.setSpeed(2)
		}
	} else if speed == 2 {
		if decision {
			duck.setSpeed(3)
		} else {
			duck.setSpeed(1)
		}
	} else if speed == 3 {
		if decision {
			duck.setSpeed(2)
		}
		duck.direction = -direction

	}
}

func (duck *Duck) changeCoordinates() {
	boost := (duck.duckType + rand.Intn(3))
	if duck.speed == 1 {
		duck.x += duck.direction * duck.speed * 5 * boost
		duck.y -= boost
	} else if duck.speed == 2 {
		duck.x += duck.direction * duck.speed * boost
		duck.y -= 2 * boost
	} else if duck.speed == 3 {
		duck.y -= 3 * boost
	} else if duck.speed == 0 {
		duck.setSpeed(10)
	} else if duck.speed == 10 {
		duck.y += 15
		duck.direction *= -1
	}
}

func createDuck(duckType int) *Duck {
	duck := &Duck{
		duckType:  duckType,
		direction: 1,
		y:         380,
		x:         screenWidth/4 + (screenWidth/4)*rand.Intn(3),
		speed:     3,
		frame:     frames[duckType]["N"],
	}
	return duck
}

func prepareOp(x, y int, invert bool) *ebiten.DrawImageOptions {
	op := &ebiten.DrawImageOptions{}

	if invert {
		op.GeoM.Scale(-1, 1)
		op.GeoM.Translate(frameWidth, 0)
	}

	op.GeoM.Translate(float64(x), float64(y))
	return op
}

func moveDuck(screen *ebiten.Image, duck *Duck, nextFrameTick chan bool) {
	for {
		<-nextFrameTick

		if rand.Intn(3) == 0 {
			duck.changeDirection()
		}

		duckImage := duck.getImage()
		op := prepareOp(duck.x, duck.y, duck.direction < 0)
		screen.DrawImage(duckImage, op)

		duck.changeCoordinates()
		duck.frame = duck.frame.nextFrame

		nextFrameTick <- true

		if (duck.x < 0) || duck.x > screenWidth || duck.y < 0 || duck.y > 380 {
			duck.isGarbage = true
			return
		}
	}
}
