package main

import "sync"

type PseudoCyclicBarrier struct {
	numberOfThreads int
	waitFor         int
	lock            sync.Mutex
	barrier         chan bool
}

func makeBarrier(threads int, barrierChannel chan bool) *PseudoCyclicBarrier {
	bar := &PseudoCyclicBarrier{
		numberOfThreads: threads,
		waitFor:         threads,
		lock:            sync.Mutex{},
		barrier:         barrierChannel,
	}
	return bar
}

func (barrier *PseudoCyclicBarrier) await() {
	barrier.lock.Lock()
	barrier.waitFor--
	if barrier.waitFor == 0 {
		barrier.waitFor = barrier.numberOfThreads
		barrier.lock.Unlock()
		barrier.barrier <- true
		return
	}
	barrier.lock.Unlock()
}
