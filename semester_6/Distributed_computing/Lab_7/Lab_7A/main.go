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
	nestWaiter  chan bool

	ducks []*Duck

	backgroundImage *ebiten.Image

	score     int
	ammo      int
	lastClick time.Time
)

func hostGame(screen *ebiten.Image, nextFrameTick chan bool) {
	var ticks int
	for {
		<-nextFrameTick

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
			<-ducksClocks[i]
		}

		deleted := true
		for deleted {
			deleted = false
			for i := range ducksClocks {
				if ducks[i].isGarbage {
					deleted = true

					ducks[i] = ducks[len(ducks)-1]
					ducksClocks[i] = ducksClocks[len(ducksClocks)-1]

					ducks = ducks[:len(ducks)-1]
					ducksClocks = ducksClocks[:len(ducksClocks)-1]
					break
				}
			}
		}

		if ticks%40 == 0 {
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
	nestWaiter = make(chan bool)
	go hostGame(screen, nestWaiter)
	gameStarted = true
}

func (game *Game) Draw(screen *ebiten.Image) {
	if !gameStarted {
		game.StartGame(screen)
	}

	shot_x, shot_y := ebiten.CursorPosition()
	if ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft) {
		if time.Now().Sub(lastClick) > 300000000 {
			lastClick = time.Now()
			if ammo > 0 {
				ammo--
				for i := range ducks {
					if ducks[i].isGarbage || ducks[i].isDead {
						continue
					}
					if ducks[i].isHit(shot_x, shot_y) {
						ducks[i].kill()
						score += 1 << (ducks[i].duckType - 1)
						break
					}
				}
			}
		}

	}

	op := &ebiten.DrawImageOptions{}
	screen.DrawImage(backgroundImage.SubImage(image.Rect(220, 0, 720, 500)).(*ebiten.Image), op)

	nestWaiter <- true

	time.Sleep(100 * time.Millisecond)

	<-nestWaiter

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

	windowHeight := 31 * screenHeight / 8
	windowWidth := 5 * screenHeight / 2
	ebiten.SetWindowSize(windowHeight, windowWidth)
}

func main() {
	initialiseVariables()

	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}
}
