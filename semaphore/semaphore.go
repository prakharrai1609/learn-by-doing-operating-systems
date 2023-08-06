package main

import (
	"fmt"
	"sync"
	"time"
)

type Semaphore struct {
	count int
	mutex sync.Mutex
	cond  *sync.Cond
}

func NewSemaphore(initialCount int) *Semaphore {
	s := &Semaphore{count: initialCount}
	s.cond = sync.NewCond(&s.mutex)
	return s
}

func (s *Semaphore) Acquire() {
	s.mutex.Lock()
	defer s.mutex.Unlock()
	for s.count == 0 {
		s.cond.Wait()
	}
	s.count--
}

func (s *Semaphore) Release() {
	s.mutex.Lock()
	defer s.mutex.Unlock()
	s.count++
	s.cond.Signal()
}

var semaphore = NewSemaphore(2)

func worker(id int) {
	semaphore.Acquire()
	fmt.Printf("Worker %d acquired the semaphore.\n", id)
	time.Sleep(time.Second * 5) // Simulate some work
	fmt.Printf("Worker %d releasing the semaphore.\n", id)
	semaphore.Release()
}

func main() {
	var wg sync.WaitGroup

	wg.Add(3)
	go func() {
		defer wg.Done()
		worker(1)
	}()

	go func() {
		defer wg.Done()
		worker(2)
	}()

	go func() {
		defer wg.Done()
		worker(3)
	}()

	wg.Wait()
}
