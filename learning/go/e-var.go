/*
 e-var.go
 */

package main

import "fmt"

func var_declare() {
	/*
	 * var v1 int
	 * var v2 string
	 * var v3 [10]int
	 * var v4 []int
	 * var v5 struct {
	 * 	f int
	 * }
	 * var v6 *int
	 * var v7 map[string]int
	 * var v8 func(a int) int
	 * var (
	 * 	v9 int 
	 * 	v10 int
	 * )
	 */

	var v1 int
	fmt.Println(v1);
}

func var_init() {
	/*
	 * var v1 int = 10
	 * var v2 = 10
	 * v3 := 10
	 */

	var v1 int = 10
	fmt.Println(v1);
}

func var_swap() {
	i := 10
	j := 20
	fmt.Println(i, j);
	i, j = j, i
	fmt.Println(i, j);
}

func var_const() {
	/*
	 * const pi float64 = 3.14159265358979323846
	 * const zero = 0.0
	 * const (
	 * 	size int64 = 1024
	 * 	eof = -1
	 * )
	 * const u, v float32 = 0, 3
	 * const a, b, c = 3, 4, "foo"
	 * const mask = 1 << 3
	 */

	const pi float64 = 3.14159265358979323846
	fmt.Println(pi);
}

func var_pre_const() {
	// true, false iota
	const (
		a0 = iota		// 0
		a1 = iota		// 1
		a2 = iota		// 2
	)

	const (
		b1 = 1 << iota	// 1
		b2 = 1 << iota	// 2
		b3 = 1 << iota	// 4
	)

	const (
		u 		  = iota * 42		// 0
		v float64 = iota * 42		// 42.0
		w 		  = iota * 42		// 84
	)

	const x = iota		// 0
	const y = iota		// 0

	const (
		c0 = iota		// 0
		c1				// 1
		c2				// 2
	)

	const (
		d1 = 1 << iota	// 1
		d2				// 2
		d3				// 4
	)

	const (
		Sunday = iota
		Monday
		Tuesday
		Wednesday
		Thursday
		Friday
		Staturday
		numberofDays
	)
}

func getName() (fristName, lastName, nickName string) {
	return "A", "B", "C"
}

func main() {
	fmt.Println("var learning")

	var_declare()
	var_init()
	var_swap()
	var_const()
	var_pre_const()
	var nickName string
	_, _, nickName = getName()
	fmt.Println(nickName)
}
