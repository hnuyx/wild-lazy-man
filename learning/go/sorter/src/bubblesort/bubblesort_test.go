/*
 buffersort_test.go
 */

package bubblesort

import "testing"

func TestBubbleSort1 (t *testing.T) {
	values := []int{5, 4, 3, 2, 1}
	BubbleSort(values)
	values2 := []int{1, 2, 3, 4, 5}
	for i := 0; i < 5; i ++ {
		if values[i] != values2[i] {
			t.Error("BubbleSort() failed. Got ", values, "Expected ", values2)
		}
	}
}

func TestBubbleSort2 (t *testing.T) {
	values := []int{5, 5, 3, 2, 1}
	BubbleSort(values)
	values2 := []int{1, 2, 3, 5, 5}
	for i := 0; i < 5; i ++ {
		if values[i] != values2[i] {
			t.Error("BubbleSort() failed. Got ", values, "Expected ", values2)
		}
	}
}

func TestBubbleSort3 (t *testing.T) {
	values := []int{5}
	BubbleSort(values)
	values2 := []int{5}
	for i := 0; i < 1; i ++ {
		if values[i] != values2[i] {
			t.Error("BubbleSort() failed. Got ", values, "Expected ", values2)
		}
	}
}
