package main

import (
	"fmt"
	"math/rand"
	"time"
)
var graph *Graph = &Graph{};

var s1 = rand.NewSource(time.Now().UnixNano())
var r1 = rand.New(s1)
var quit = make(chan bool)

func buildNewRoad(){
	city1 := graph.GetRandomCity();
	city2 := graph.GetRandomCity();
	if city1 == nil || city2 == nil || city1 == city2 {
		return;
	}
	if(graph.HasRoad(city1, city2)){
		return;
	}
	value := r1.Intn(100)
	graph.AddRoad(city2, city1, value)
	fmt.Printf("Road builder: new road between %s and %s costs %d\n", city1.name, city2.name, value)
}

func deleteRoad(){
	if len(graph.tickets) == 0{
		return
	}
	r := r1.Intn(len(graph.tickets))
	for edge, _ := range graph.tickets {
		if r == 0 {
			fmt.Printf("Road builder: deleted road between %s and %s\n", edge.from.name, edge.to.name)
			delete(graph.tickets, edge)
			break;
		}
		r--;
	}

}

func roadBuilderThread(n, pr int){
	for p := 0; p < n; p++ {
		time.Sleep((800) * time.Millisecond)
		graph.lock.Lock();
		if r1.Intn(pr) == 0 {
			deleteRoad();
		} else {
			buildNewRoad();
		}
		graph.lock.Unlock();
	}
}

func ticketThread(n int){
	for p := 0; p < n; p++ {
		time.Sleep((700) * time.Millisecond)
		if len(graph.tickets) == 0 {
			continue
		}
		graph.lock.Lock();
		r := r1.Intn(len(graph.tickets))
		for edge, _ := range graph.tickets {
			if r == 0 {
				newCost := edge.cost + r1.Intn(41) - 20;
				if newCost > 0 {
					edge.changeCost(newCost)
				}
				break;
			}
			r--;
		}
		graph.lock.Unlock();
	}
}

func cityBuilderThread(n, pr int){
	for p := 0; p < n; p++ {
		time.Sleep((500) * time.Millisecond)
		graph.lock.Lock();
		if r1.Intn(pr) == 0 {
			deleteCity();
		} else {
			buildCity();
		}
		graph.lock.Unlock();
	}
}

func deleteCity() {
	city := graph.GetRandomCity();
	if city == nil {
		return
	}
	for edge, _ := range graph.tickets {
		if edge.from == city || edge.to == city {
			delete(graph.tickets, edge)
		}
	}
	delete(graph.cityNames, city.name)
	i := 0
	for ; graph.cities[i] != city; i++ {}
	graph.cities[i] = graph.cities[len(graph.cities) - 1]
	graph.cities = graph.cities[:len(graph.cities) - 1]
	fmt.Printf("City builder: city %s was destroyed\n", city.name)
}

func buildCity() {
	city := &Vertex{id: graph.maxId, name: randomCityName()}
	graph.cities = append(graph.cities, city)
	graph.cityNames[city.name] = city
	fmt.Printf("City builder: city %s was built\n", city.name)
}

func randomCityName() string{
	s := "qwertyuiopasdfghjklzxcvbnm"
	result := ""

	for i := 0; i < 6; i++ {
		result += string(s[r1.Intn(26)])
	}
	return result
}

func pathSearchingThread(n int){
	for p := 0; p < n; p++ {
		time.Sleep((1000) * time.Millisecond)
		graph.lock.RLock();
		cityA := graph.GetRandomCity();
		cityB := graph.GetRandomCity();
		if cityA == cityB {
			graph.lock.RUnlock();
			continue
		}
		visited := make(map[*Vertex]bool)
		for _, city := range graph.cities{
			visited[city] = false
		}
		path, ok := dfsPathSearch(cityA, cityB, visited)
		if ok {
			fmt.Printf("Path from %s to %s: %s\n", cityA.name, cityB.name, path);
		} else {
			fmt.Printf("No path between %s and %s\n", cityA.name, cityB.name)
		}
		graph.lock.RUnlock();
	}
	quit <- true
}

func dfsPathSearch(cur, target *Vertex, visited map[*Vertex]bool) (string, bool){
	visited[cur] = true
	if(cur == target){
		return target.name, true
	}
	for edge, _ := range graph.tickets {
		if edge.from == cur && !visited[edge.to]{
			result, ok := dfsPathSearch(edge.to, target, visited)
			if ok {
				return cur.name + "->" + result, ok
			}
		} else if edge.to == cur && !visited[edge.from]{
			result, ok := dfsPathSearch(edge.from, target, visited)
			if ok {
				return cur.name + "->" + result, ok
			}
		}
	}
	return "", false
}


func main() {
	graph.createGraph();
	cityBuilderThread(10, 5)
	roadBuilderThread(10, 5)

	go cityBuilderThread(10, 3)
	go roadBuilderThread(10, 3);
	go ticketThread(10);
	go pathSearchingThread(10);
	go pathSearchingThread(10);
	go pathSearchingThread(10);

	<- quit
	fmt.Println("Thank you for your attention!")
}
