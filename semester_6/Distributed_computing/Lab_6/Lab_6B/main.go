package main

import (
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

var N = 120
var M = 120
var pixelSize = 8
var field [][]int

func (g *Game) Update() error {
	return nil
}

func printPixel(screen *ebiten.Image, i, j int, cl color.Color) {
	for pi := 0; pi < pixelSize; pi++ {
		for pj := 0; pj < pixelSize; pj++ {
			screen.Set(i*pixelSize+pi, j*pixelSize+pj, cl)
		}
	}
}

func (g *Game) Draw(screen *ebiten.Image) {
	var typeColor = make(map[int]color.Color)
	typeColor[0] = color.RGBA{255, 255, 255, 0xff}
	typeColor[1] = color.RGBA{0, 255, 0, 0xff}
	typeColor[2] = color.RGBA{255, 0, 0, 0xff}
	typeColor[3] = color.RGBA{0, 0, 255, 0xff}
	if field == nil {
		field = makeField("source3.txt")
	}
	field = proceedField()
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			printPixel(screen, i, j, typeColor[field[i][j]])
		}
		time.Sleep(250)
		//fmt.Println("RECOUNTED!")
	}

}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	return M * pixelSize, N * pixelSize
}

func randomNumber(maxBound int) int {
	var s1 = rand.NewSource(time.Now().UnixNano())
	var r1 = rand.New(s1)
	return r1.Intn(maxBound)
}

func readFile(fname string) (nums []int, err error) {
	b, err := ioutil.ReadFile(fname)
	if err != nil {
		return nil, err
	}

	lines := strings.Split(string(b), "\n")
	// Assign cap to avoid resize on every append.
	nums = make([]int, 0, len(lines)*2)

	for _, l := range lines {
		// Empty line occurs at the end of the file when we use Split.
		if len(l) == 0 {
			continue
		}
		// Atoi better suits the job when we know exactly what we're dealing
		// with. Scanf is the more general option.
		n, err := strconv.Atoi(strings.Split(l, " ")[0])
		if err != nil {
			return nil, err
		}
		nums = append(nums, n)
		n, err = strconv.Atoi(strings.Split(l, " ")[1])
		if err != nil {
			return nil, err
		}
		nums = append(nums, n)
		n, err = strconv.Atoi(strings.Split(l, " ")[2])
		if err != nil {
			return nil, err
		}
		nums = append(nums, n)
	}

	return nums, nil
}

func makeField(filename string) [][]int {
	newField := make([][]int, N)
	for i := 0; i < N; i++ {
		newField[i] = make([]int, M)
	}
	if filename == "" {
		for i := 0; i < N; i++ {
			for j := 0; j < M; j++ {
				if randomNumber(3) == 0 {
					newField[i][j] = 1
				}
			}
		}
		return newField
	}
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			newField[i][j] = 0
		}
	}
	nums, _ := readFile(filename)
	for id := 0; id+2 < len(nums); id += 3 {
		newField[nums[id]][nums[id+1]] = nums[id+2]
	}
	/*

	 */
	return newField
}

func isAlive(field [][]int, i, j int) int {
	counter := make(map[int]int)
	counter[0] = 0
	counter[1] = 0
	counter[2] = 0
	counter[3] = 0
	if i > 0 && j > 0 {
		counter[field[i-1][j-1]]++
	}
	if i > 0 {
		counter[field[i-1][j]]++
	}
	if i > 0 && j+1 < M {
		counter[field[i-1][j+1]]++
	}
	if j > 0 {
		counter[field[i][j-1]]++
	}
	if j+1 < M {
		counter[field[i][j+1]]++
	}
	if i+1 < N && j > 0 {
		counter[field[i+1][j-1]]++
	}
	if i+1 < N {
		counter[field[i+1][j]]++
	}
	if i+1 < N && j+1 < M {
		counter[field[i+1][j+1]]++
	}

	var maxColor, valMax, secondMax = 0, -1, -1
	for i := 1; i < 4; i++ {
		if counter[i] > valMax && counter[i] >= 2 {
			if (field[i][j] == 0 && counter[i] == 2) || counter[i] > 3 {
				continue
			}
			maxColor = i
			valMax = counter[i]
		} else if counter[i] == valMax && counter[i] >= 2 {
			secondMax = valMax
		}
	}

	if valMax == secondMax {
		return field[i][j]
	} else {
		return maxColor
	}
}

func proceedField() [][]int {
	newField := make([][]int, N)
	for i := 0; i < N; i++ {
		newField[i] = make([]int, M)
	}
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			newField[i][j] = isAlive(field, i, j)
		}
	}
	return newField
}

func processFieldThread(field, newField [][]int, l, r, t, b int) {
	for i := t; i < b; i++ {
		for j := l; j < r; j++ {
			newField[i][j] = isAlive(field, i, j)
		}
	}
}

func proceedFieldGo() [][]int {
	left := 0
	top := 0
	split_second := 3
	newField := make([][]int, N)
	for i := 0; i < N; i++ {
		newField[i] = make([]int, M)
	}

	for i := 0; i < split_second-1; i++ {
		for j := 0; j < split_second-1; j++ {
			go processFieldThread(field, newField, left, left+(M/split_second), top, top+(N/split_second))
			left += (M / split_second)
		}
		go processFieldThread(field, newField, left, M, top, top+(N/split_second))
		left = 0
		top += (N / split_second)
	}
	for j := 0; j < split_second-1; j++ {
		go processFieldThread(field, newField, left, left+(M/split_second), top, M)
		left += (M / split_second)
	}
	go processFieldThread(field, newField, left, M, top, M)
	return newField
}

func main() {

	ebiten.SetWindowSize(M*pixelSize, N*pixelSize)
	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}

}
