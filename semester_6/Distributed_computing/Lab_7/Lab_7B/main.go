package main

import (
	"fmt"
	"github.com/hajimehoshi/ebiten/examples/resources/fonts"
	ebiten "github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/text"
	"golang.org/x/image/font"
	"golang.org/x/image/font/opentype"
	"image"
	"image/color"
	_ "image/png"
	"log"
	"math/rand"
	"os"
	"time"
)

var (
	myFont font.Face
)

func Abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

const (
	screenWidth  = 500
	screenHeight = 500
	frameWidth   = 38
)

var (
	gameStarted = false
	ducksClocks []chan bool
	hostClock   chan bool
	bulletClocks []chan bool

	ducks []*Duck
	bullets []*Bullet
	hunter *Hunter

	backgroundImage *ebiten.Image
	bulletImage *ebiten.Image

	score     int
	ammo      int
	bulletSpeed int

	mouseIsDown bool
)

func hostGame(screen *ebiten.Image, nextFrameTick chan bool) {
	var ticks int
	for {
		<- nextFrameTick

		for i := range ducksClocks {
			if ducks[i].isGarbage {
				continue
			}
			ducksClocks[i] <- true
		}

		for i := range ducksClocks {
			if ducks[i].isGarbage {
				continue
			}
			<- ducksClocks[i]
		}



		deletedDuck := true
		for deletedDuck {
			deletedDuck = false
			for i := range ducksClocks {
				if ducks[i].isGarbage {
					deletedDuck = true

					ducks[i] = ducks[len(ducks)-1]
					ducksClocks[i] = ducksClocks[len(ducksClocks)-1]

					ducks = ducks[:len(ducks)-1]
					ducksClocks = ducksClocks[:len(ducksClocks)-1]
					break
				}
			}
		}

		for i := range bulletClocks {
			if bullets[i].isOut {
				continue
			}
			bulletClocks[i] <- true
		}

		for i := range bulletClocks {
			if bullets[i].isOut {
				continue
			}
			<- bulletClocks[i]
		}

		deletedBullet := true
		for deletedBullet {
			deletedBullet = false
			for i, bullet := range bullets {
				if bullet.isOut {
					deletedBullet = true

					bullets[i] = bullets[len(bullets)-1]
					bulletClocks[i] = bulletClocks[len(bulletClocks)-1]

					bullets = bullets[:len(bullets)-1]
					bulletClocks = bulletClocks[:len(bulletClocks)-1]
					break
				}
			}
		}

		if ticks % 40 == 0 {
			var duck *Duck
			newDuckColor := rand.Intn(6)
			switch {
			case newDuckColor == 0:
				duck = createDuck(3) //red
				break
			case newDuckColor > 0 && newDuckColor < 3:
				duck = createDuck(2) //black
				break
			default:
				duck = createDuck(1) // blue
				break
			}

			ducks = append(ducks, duck)
			ducksClocks = append(ducksClocks, make(chan bool))

			go moveDuck(screen, ducks[len(ducks)-1], ducksClocks[len(ducksClocks)-1])
		}

		if ammo < 3 {
			if ticks%30 == 0 {
				ammo++
			}
		}

		ticks++

		if ticks == 12000 {
			ticks = 0
		}

		nextFrameTick <- true
	}
}

type Game struct {
	count int
}

func (game *Game) Update() error {
	return nil
}

func (game *Game) StartGame(screen *ebiten.Image) {
	hostClock = make(chan bool)
	go hostGame(screen, hostClock)
	gameStarted = true
}

func (game *Game) Draw(screen *ebiten.Image) {
	if !gameStarted {
		game.StartGame(screen)
	}

	hunterPosition, _ := ebiten.CursorPosition()
	if !mouseIsDown && ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft) {
		mouseIsDown = true
		if ammo > 0 {
			ammo--
			newBullet := &Bullet{
				x: hunterPosition,
				y: screenHeight - 40,
				isOut: false,
			}
			bullets = append(bullets, newBullet)
			bulletClocks = append(bulletClocks, make(chan bool))
			go operateBullet(screen, newBullet, bulletClocks[len(bulletClocks) - 1])
		}
	}

	op := &ebiten.DrawImageOptions{}
	screen.DrawImage(backgroundImage.SubImage(image.Rect(220, 0, 720, 500)).(*ebiten.Image), op)

	dogImage, op := hunter.drawHunter(hunterPosition)
	screen.DrawImage(dogImage, op)

	hostClock <- true
	time.Sleep(100 * time.Millisecond)
	<-hostClock
	mouseIsDown = false

	text.Draw(screen, fmt.Sprintf("Score: %d\nAmmo: %d", score, ammo), myFont, 5, 25, color.White)
}

func (game *Game) Layout(outsideWidth, outsideHeight int) (int, int) {
	return screenWidth, screenHeight
}

func getAndDecode(filename string) *ebiten.Image {
	encodedImage, err := os.Open(filename)
	if err != nil {
		log.Fatal(err)
	}
	decodedImage, _, err := image.Decode(encodedImage)
	if err != nil {
		log.Fatal(err)
	}
	return ebiten.NewImageFromImage(decodedImage)
}

func initialiseVariables() {
	//get ducks
	duckSprites = getAndDecode("../duckhunt_various_sheet.png")
	initialiseFrames()

	//background
	backgroundImage = getAndDecode("../bg.png")

	bulletImage = getAndDecode("../bullet.png")

	//create some font
	tt, err := opentype.Parse(fonts.MPlus1pRegular_ttf)
	if err != nil {
		log.Fatal(err)
	}
	myFont, err = opentype.NewFace(tt, &opentype.FaceOptions{
		Size:    24,
		DPI:     72,
		Hinting: font.HintingFull,
	})

	hunter = &Hunter{x: 0}
	bulletSpeed = 20

	windowWidth := 31 * screenHeight / 8
	windowHeight := 13 * screenHeight / 6
	ebiten.SetWindowSize(windowWidth, windowHeight)
}

func main() {
	initialiseVariables()

	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}
}
