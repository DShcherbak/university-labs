package main

import (
	"context"
	"fmt"
	"golang.org/x/sync/semaphore"
	"math/rand"
	"time"
)

var sem = semaphore.NewWeighted(int64(1))
var paper, matches, tobacco bool;

func Smoke(s string){
	s1 := rand.NewSource(time.Now().UnixNano())
	r1 := rand.New(s1)
	r := r1.Intn(5)
	fmt.Printf("%s is smoking\n", s)
	for i := 0; i < r; i++ {
		fmt.Println("Pffff.....")
	}
}

func Paper(){
	for number := 0; number < 10000; number ++ {
		ctx := context.Background()
		sem.Acquire(ctx, 1);
		if (matches && tobacco) {
			Smoke("Paper")
		}
		sem.Release(1)
	}
}

func Tobacco(){
	for number := 0; number < 10000; number ++ {
		ctx := context.Background()
		sem.Acquire(ctx, 1)
		if (matches && paper) {
			Smoke("Tobacco")
		}
		sem.Release(1)
	}
}

func Mathces(){
	for number := 0; number < 10000; number ++ {
		ctx := context.Background()
		sem.Acquire(ctx, 1)
		if (paper && tobacco) {
			Smoke("Mathces")
		}
		sem.Release(1)
	}
}

var quit = make(chan bool)

func Dealer(){
	for number := 0; number < 10000; number ++ {

		ctx := context.Background()
		sem.Acquire(ctx, 1);
		s1 := rand.NewSource(time.Now().UnixNano())
		r1 := rand.New(s1)
		r := r1.Intn(3)
		paper = r < 2
		matches = r > 0
		tobacco = !(paper && matches)
		if(paper){
			fmt.Printf("Paper ")
		}
		if(matches){
			fmt.Printf("Matches ")
		}
		if(tobacco){
			fmt.Printf("Tobacco ")
		}
		fmt.Printf("are on the table!\n")
		time.Sleep(1000 * time.Millisecond)
		sem.Release(1)
	}
	quit <- true
}


func main() {
	go Dealer()
	go Paper()
	go Tobacco()
	go Mathces()

	<- quit
	fmt.Println("Thank you for your attention!")
}
