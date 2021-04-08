package main

import (
	"github.com/hajimehoshi/ebiten/v2"
	"image"
)

type Bullet struct {
	x int
	y int
	isOut bool
}

type Hunter struct {
	x int
	direction int
}

func (hunter* Hunter) drawHunter(hunterPosition int) (*ebiten.Image, *ebiten.DrawImageOptions){
	var dogImage *ebiten.Image;
	op := &ebiten.DrawImageOptions{}

	if (hunter.x == hunterPosition) {
		dogImage = duckSprites.SubImage(image.Rect(197, 63, 226, 102)).(*ebiten.Image)
		op.GeoM.Translate(float64(hunterPosition)-15, 390)
	} else {
		dogImage = duckSprites.SubImage(image.Rect(178, 0, 240, 62)).(*ebiten.Image)

		if hunter.x - hunterPosition > 1 {
			op.GeoM.Scale(-1, 1)
			op.GeoM.Translate(frameWidth, 0)
		}
		op.GeoM.Translate(float64(hunterPosition)-30, 400)
	}
	hunter.x = hunterPosition
	return dogImage, op

}

func operateBullet(screen *ebiten.Image, bullet *Bullet, bulletsClock chan bool) {
	for !bullet.isOut {
		<-bulletsClock
		if bullet.y < 0 {
			bullet.isOut = true
		} else {
			for _, duck := range ducks {
				if !duck.isGarbage && !duck.isDead {
					if duck.x <= bullet.x && duck.isHit(bullet.x, bullet.y) {
						duck.kill()
						bullet.isOut = true
						score += 1 << (duck.duckType - 1)
						break
					}
				}
			}


			bullet.y -= bulletSpeed

			op := &ebiten.DrawImageOptions{}
			op.GeoM.Scale(0.1, 0.05)
			op.GeoM.Translate(float64(bullet.x), float64(bullet.y))

			screen.DrawImage(bulletImage, op)

		}
		bulletsClock <- true
	}
}