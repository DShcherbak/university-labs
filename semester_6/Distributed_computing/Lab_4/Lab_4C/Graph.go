package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Vertex struct {
	name string
	id int
}

type Edge struct {
	from *Vertex
	to   *Vertex
	cost int
}

func (edge1 *Edge) equals(edge2 *Edge) bool{
	return (edge1.from == edge2.from && edge2.to == edge1.to) ||
		(edge1.to == edge2.from && edge2.to == edge1.from)
}

func (edge *Edge) changeCost(newCost int){
	edge.cost = newCost
	fmt.Printf("New cost between %s and %s is %d\n", edge.from.name, edge.to.name, edge.cost)
}

type Graph struct {
	maxId     int
	cities []*Vertex
	cityNames map[string]*Vertex
	tickets   map[*Edge]bool
	lock sync.RWMutex
}

func (graph *Graph) createGraph(){
	graph.maxId = 0;
	graph.tickets = make(map[*Edge]bool)
	graph.cityNames = make(map[string]*Vertex)
	graph.cities = make([]*Vertex, 0)
}

func (graph Graph) AddCity(name string) {
	_, ok := graph.cityNames[name];
	if (!ok) {
		v := &Vertex{id: graph.maxId, name: name}
		graph.maxId += 1
		graph.cityNames[name] = v
		graph.cities = append(graph.cities, v)
		fmt.Println("Added the city of " + name);
	} else {
		fmt.Println("City of " + name + " already exists");
	}
}

func (graph Graph) DeleteCity(name string) {
	v, ok := graph.cityNames[name];
	if (ok) {
		i := 0;
		for ; graph.cities[i] != v; i++ {}
		graph.cities[i] = graph.cities[len(graph.cities) - 1]
		graph.cities = graph.cities[:len(graph.cities) - 1]
		delete(graph.cityNames, name)
		fmt.Println("City of " + name + " was deleted");
	} else {
		fmt.Println("City of " + name + " doesn't exists");
	}
}

func (graph Graph) AddRoad(A, B *Vertex, newCost int) {
	edge := &Edge{A, B, newCost}
	for oldEdge, _ := range graph.tickets{
		if edge.equals(oldEdge){
			oldEdge.changeCost(newCost)
			return
		}
	}
	graph.tickets[edge] = true
}

func (graph Graph) HasRoad(A, B *Vertex) bool{
	edge := &Edge{A, B, 0}
	for oldEdge, _ := range graph.tickets{
		if oldEdge.equals(edge) {
			return true;
		}
	}
	return false;
}

func (graph Graph) DeleteRoad(A, B *Vertex) {
	edge := &Edge{A, B, 0}
	for oldEdge, _ := range graph.tickets{
		if oldEdge.equals(edge) {
			fmt.Printf("Deleted road between %s and %s\n", A.name, B.name,)
			delete(graph.tickets, oldEdge)
			return
		}
	}
}

func (graph Graph) GetRandomCity() *Vertex {
	var s1 = rand.NewSource(time.Now().UnixNano())
	var r1 = rand.New(s1)
	if len(graph.cities) == 0 {
		return nil;
	}
	c := r1.Intn(len(graph.cities))
	return graph.cities[c];
}

