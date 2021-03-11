package main

import (
	"fmt"
	"math/rand"
	"time"
)

func sortSlice(polk []bool, leftProblem, rightProblem bool, barrier *PseudoCyclicBarrier) {
	if !leftProblem {
		for id, _ := range polk {
			polk[id] = false
		}
	} else if !rightProblem {
		for id, _ := range polk {
			polk[id] = true
		}
	} else {
		for id, _ := range polk {
			polk[id] = !polk[id]
		}
	}
	barrier.await()
}

func breakPolk(polk []bool) [][]bool {
	result := make([][]bool, 0)
	previousStart := 0
	l := len(polk) - 1
	for i := 0; i < l; i++ {
		if polk[i] && !polk[i+1] {
			result = append(result, polk[previousStart:i+1])
			previousStart = i + 1
		}
	}
	result = append(result, polk[previousStart:l+1])
	return result
}

func generatePolk(size int) []bool {
	result := make([]bool, size)

	for i := 0; i < size; i++ {
		s1 := rand.NewSource(time.Now().UnixNano())
		r1 := rand.New(s1)
		result[i] = r1.Intn(2) == 0
	}
	return result
}

func printPolk(polk []bool) {
	s := ""
	for _, v := range polk {
		if v {
			s += ">"
		} else {
			s += "<"
		}
	}
	fmt.Println(s)
}

func main() {
	polk := generatePolk(10)
	divisions := breakPolk(polk)
	barrierChannel := make(chan bool)
	var barrier *PseudoCyclicBarrier
	for len(divisions) > 1 {
		printPolk(polk)
		barrier = makeBarrier(len(divisions), barrierChannel)
		for id, division := range divisions {
			go sortSlice(division, id > 0, id < len(divisions)-1, barrier)
		}
		<-barrierChannel
		divisions = breakPolk(polk)
	}
	printPolk(polk)
}
