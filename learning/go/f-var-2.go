/*
 f-var-2.go
 */

package main

import "fmt"
import "math"

func var_bool() {
	var v1 bool
	v1 = true
	v2 := (1 == 2)

	// v1 = 1  			// wrong!
	// v1 = bool(1)		// wrong!
	fmt.Println(v1, v2)
}

func var_int() {
	var v1 int32
	v2 := 64		// type: int
	//v1 = v2			// wrong
	v1 = int32(v2)
	fmt.Println(v1)
}

func isEqual(f1, f2, p float64) bool {
	return math.Dim(f1, f2) < p
}

func var_float() {
	var f1 float64
	f1 = 10.0
	f2 := 12.0	// type: float64

	isEqual(f1, f2, 0.00001)
}

func var_complex() {
	var v1 complex64
	v1 = 3.2 + 12i
	v2 := 3.2 + 12i
	v3 := complex(3.2, 12)
	r := real(v1)
	i := imag(v1)
	r = real(complex64(v2))
	i = imag(complex64(v2))
	r = real(complex64(v3))
	i = imag(complex64(v3))

	fmt.Println(r, i)
}

func var_string() {
	var str string
	str = "Hello Wrold!"
	ch := str[0]

	fmt.Printf("the length of \"%s\" si %d.\n", str, len(str))
	fmt.Printf("The frist character of \"%s\" is %c.\n", str, ch)

	s1 := "Hello World!"
	s2 := "How do you do!"
	s3 := s1+s2
	
	fmt.Println(s3)

	s4 := "Hello 世界"
	l := len(s4)
	for i := 0; i < l; i++ {
		ch = s4[i]
		fmt.Println(i, ch)
	}

	for i, ch := range s4 {
		fmt.Println(i, ch)
	}
}

func modify(array [5]int) {
	array[0] = 10
	fmt.Println("in modify(), array values: ", array)
}


// [32]byte
// [2*N] struct {x, y int32}
// [1000] *float64
// [3][5] int
// [2][2][2] float64

func var_array() {
	array := [5]int{1, 2, 3, 4, 5}
	modify(array)
	fmt.Println("in var_array(), array values: ", array)

	fmt.Println("===============================")
	for i, v := range array {
		fmt.Println(i, v)
	}

	arr2 := [10]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	// asli2 := arr2[:5]
	// asli2 := arr2[:]
	asli2 := arr2[5:]
	fmt.Println("===============================")
	for i, v := range asli2 {
		fmt.Println(i, v)
	}

	// slice := make([]int, 5)
	// slice := []int{1, 2, 3, 4, 5}
	asli3 := make([]int, 5, 10)
	fmt.Println("capacity is: ", cap(asli3))
	fmt.Println("length is: ", len(asli3))
	asli3 = append(asli3, asli2...)
	fmt.Println("===============================")
	for i, v := range asli3 {
		fmt.Println(i, v)
	}

	copy(asli2, asli3)
	fmt.Println("===============================")
	for i, v := range asli2 {
		fmt.Println(i, v)
	}
	copy(asli3, asli2)
	fmt.Println("===============================")
	for i, v := range asli3 {
		fmt.Println(i, v)
	}
}

func var_map() {
	type PersonInfo struct {
		ID string
		Name string
		Address string
	}
	var personDB map[string] PersonInfo
	//personDB = make(map [string] PersonInfo, 10)
	personDB = make(map [string] PersonInfo, 10)
	personDB["12345"] = PersonInfo{"12345", "Tom", "Room 203..."}
	personDB["1"] = PersonInfo{"1", "Jack", "Room 204..."}

	person, ok := personDB["1234"]
	if ok {
		fmt.Println("found person ", person.Name, "with ID 1234")
		delete(personDB, "1234")
	} else {
		fmt.Println("Did not find person with ID 1234")
	}
}

// bool
// int8, uint8(byte), int16, uint16, int32, uint32, int64, uint64, int, uint, uintptr
// float32, float64, complex64, complex128
// string, rune, error
// pointer, array, slice, map, chan, struct, interface

// +, -, *, /, %
// >, <, ==, >=, <=, !=
// <<, >>, ^ (x^y), &, |, ^ (^x)

func main() {
	fmt.Println("var learning")
	var_bool()
	var_int()
	var_float()
	var_complex()
	var_string()
	var_array()
	var_map()
}
