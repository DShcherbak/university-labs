package main

import (
	"fmt"
	"math/rand"
	"time"
)


type Vinnie struct {
	x, y int
}

type Hive struct{
	isFound bool
	field [][]int
}

var vinnie Vinnie
var hive Hive
var quit = make(chan string)
var fieldWidth, fieldHeight = 5, 5

func (hive *Hive) Rapport(x, y int, found bool) {
	hive.field[y][x] = -1
	hive.isFound = hive.isFound || found
}

func (hive *Hive) CreateField() {
	hive.field = make([][]int, fieldHeight)
	for i := 0; i < fieldHeight; i++ {
		hive.field[i] = make([]int, fieldWidth)
		for j := 0; j < fieldHeight; j++ {
			hive.field[i][j] = 0
		}
	}

}

func (hive Hive) GetNewTask() (int, int){
	if hive.isFound {
		return -1, -1
	}
	for x := 0; x < fieldWidth; x++ {
		for y := 0; y < fieldHeight; y++{
			if hive.field[y][x] == 0 {
				hive.field[y][x] = 1
				return x, y
			}
		}
	}
	return -1, -1
}

func (vinnie Vinnie) CheckVinnie(x, y int) bool{
	return vinnie.x == x && vinnie.y == y
}

func (vinnie *Vinnie) SetRandomCoordinates() {
	s2 := rand.NewSource(time.Now().UnixNano())
	rnd := rand.New(s2)
	vinnie.x = rnd.Intn(fieldWidth)
	vinnie.y = rnd.Intn(fieldHeight)
}


func GoVinniePooh() {
	for i := 0; i < 10000; i++ {
		time.Sleep(time.Millisecond * 1000)
		fmt.Println("Go go Vinnie Pooh")
	}
}



func goBee(number int) {
	for {
		x, y := hive.GetNewTask()
		if x < 0 || y < 0{
			quit <- "Done"
			return
		}
		time.Sleep(200 * time.Millisecond)
		fmt.Printf("Bee number %d arrived to (%d, %d)\n", number, x, y)
		time.Sleep(200 * time.Millisecond)
		foundVinnie := vinnie.CheckVinnie(x,y)
		fmt.Printf("Bee number %d completed search in (%d, %d)\n", number, x, y)
		if foundVinnie {
			fmt.Printf("Target eliminated, mission completer\n")
		} else {
			fmt.Printf("Target not found, returning to the hive\n")
		}
		time.Sleep(200 * time.Millisecond)
		fmt.Printf("Bee number %d arrived to the hive\n", number)
		hive.Rapport(x, y, foundVinnie)
	}
}

func main() {
	vinnie.SetRandomCoordinates()
	hive.CreateField()
	go GoVinniePooh()
	numberOfBees := 3
	for i := 0; i < numberOfBees; i++ {
		go goBee(i)
	}
	for i := 0; i < numberOfBees; i++ {
		<-quit
	}
	fmt.Println("Thank you for your attention!")
}

