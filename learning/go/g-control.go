/*
 g-control.go
 */

package main

import "fmt"

// if, else if, else
// switch, case, fallthrough

func var_ifelse() {
}

func var_switchcase(a int) {
	switch a {
	case 0:
		fmt.Println("0")
	case 1:
		fmt.Println("1")
	case 2:
		fallthrough
	case 3:
		fmt.Println("3")
	case 4,5,6:
		fmt.Println("4, 5, 6")
	default:
		fmt.Println("Default")
	}
}

func main() {
  fmt.Println("hello, control")

	var_ifelse()
	var_switchcase(0)
	var_switchcase(1)
	var_switchcase(2)
	var_switchcase(3)
	var_switchcase(4)
	var_switchcase(5)
	var_switchcase(6)
	var_switchcase(7)
}
