package main

import (
	"fmt"
	"image/color"
	"io/ioutil"
	"log"
	"math/rand"
	"strconv"
	"strings"
	"time"

	"github.com/hajimehoshi/ebiten/v2"
)

type Game struct{}

var N = 50
var M = 50
var pixelSize = 20
var field [][]bool

func (g *Game) Update() error {
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
		field = proceedField()
		screen.Fill(color.RGBA{255, 255, 255, 0xff})
		for i := 0; i < N; i++{
			for j:=0; j < M; j++{
				if field[i][j]{
					for pi:=0; pi< pixelSize; pi++{
						for pj:=0; pj<pixelSize; pj++{
							screen.Set(i*pixelSize + pi, j*pixelSize + pj, color.RGBA{0, 255, 0, 0xff})
						}
					}

				}
			}
		time.Sleep( 5000000 )
		//fmt.Println("RECOUNTED!")
	}

}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	return M*pixelSize, N*pixelSize
}

func randomNumber(maxBound int) int{
	var s1 = rand.NewSource(time.Now().UnixNano())
	var r1 = rand.New(s1)
	return r1.Intn(maxBound)
}

func readFile(fname string) (nums []int, err error) {
	b, err := ioutil.ReadFile(fname)
	if err != nil { return nil, err }

	lines := strings.Split(string(b), "\n")
	// Assign cap to avoid resize on every append.
	nums = make([]int, 0, len(lines) * 2)

	for _, l := range lines {
		// Empty line occurs at the end of the file when we use Split.
		if len(l) == 0 { continue }
		// Atoi better suits the job when we know exactly what we're dealing
		// with. Scanf is the more general option.
		n, err := strconv.Atoi(strings.Split(l," ")[0])
		if err != nil { return nil, err }
		nums = append(nums, n)
		n, err = strconv.Atoi(strings.Split(l," ")[1])
		if err != nil { return nil, err }
		nums = append(nums, n)
	}

	return nums, nil
}

func makeField(filename string) [][]bool {
	newField := make([][]bool, N)
	for i:=0; i<N; i++ {
		newField[i] = make([]bool, M)
	}
	if filename == ""{
		for i:=0; i<N; i++{
			for j:=0; j<M; j++{
				if randomNumber(3) == 0{
					newField[i][j] = true;
				}
			}
		}
		return newField
	}
	for i:=0; i<N; i++ {
		for j:=0; j<M; j++{
			newField[i][j] = false
		}
	}
	nums, _ := readFile(filename)
	for id := 0; id + 1 < len(nums); id+=2{
		fmt.Printf("{%d, %d}", nums[id], nums[id+1])
		newField[nums[id]][nums[id+1]] = true
	}
	/*

	*/
	return newField
}

func isAlive(field [][]bool, i, j int) bool {
	counter := 0
	if(i > 0 && j > 0 && field[i-1][j-1] == true){
		counter += 1
	}
	if(i > 0  && field[i-1][j] == true){
		counter += 1
	}
	if(i > 0 && j+1 < M && field[i-1][j+1] == true){
		counter += 1
	}
	if(j > 0 && field[i][j-1] == true){
		counter += 1
	}
	if(j+1 < M && field[i][j+1] == true){
		counter += 1
	}
	if(i+1 < N && j > 0 && field[i+1][j-1] == true){
		counter += 1
	}
	if(i+1 < N  && field[i+1][j] == true){
		counter += 1
	}
	if(i+1 < N && j+1 < M && field[i+1][j+1] == true){
		counter += 1
	}


	//return (counter == 2) || (counter ==3)
	return (counter == 3) || ((counter == 2) && field[i][j])
}

func proceedField() [][]bool {
	newField := make([][]bool, N)
	for i:=0; i<N; i++ {
		newField[i] = make([]bool, M)
	}
	for i:=0; i < N; i++{
		for j:=0; j < M; j++{
			newField[i][j] = isAlive(field, i, j)
		}
	}
	return newField
}

func main() {
	field = makeField("source2.txt")
	ebiten.SetWindowSize(M*pixelSize, N*pixelSize)
	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}

}