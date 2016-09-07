/*
 h-oop.go
 */

package main

import "fmt"


type Integer int

func (a Integer) Less (b Integer) bool {
	return a < b
}

func (a *Integer) Add (b Integer) {
	*a += b
}

type Rect struct {
	x, y float64
	width, height float64
}

func (r *Rect) Area() float64 {
	return r.width * r.height
}

func main() {
	fmt.Println("hello oop")

	var a  Integer = 1
	if a.Less(2) {
		fmt.Println(a, "Less 2")
	}

	a.Add(2)
	fmt.Println(a)

	r1 := new(Rect)
	r2 := &Rect{}
	r3 := &Rect{0, 0, 100, 200}
	r4 := &Rect{width: 100, height: 200}
	fmt.Println(r1.Area())
	fmt.Println(r2.Area())
	fmt.Println(r3.Area())
	fmt.Println(r4.Area())
}

