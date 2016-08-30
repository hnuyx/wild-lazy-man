/*
 qsort_test.go
 */

package qsort

import "testing"

func TestQuickSort1 (t *testing.T) {
	values := []int{5, 4, 3, 2, 1}
	QuickSort(values)
	values2 := []int{1, 2, 3, 4, 5}
	for i := 0; i < 5; i ++ {
		if values[i] != values2[i] {
			t.Error("QuickSort() failed. Got ", values, "Expected ", values2)
		}
	}
}

func TestQuickSort2 (t *testing.T) {
	values := []int{5, 5, 3, 2, 1}
	QuickSort(values)
	values2 := []int{1, 2, 3, 5, 5}
	for i := 0; i < 5; i ++ {
		if values[i] != values2[i] {
			t.Error("QuickSort() failed. Got ", values, "Expected ", values2)
		}
	}
}

func TestQuickSort3 (t *testing.T) {
	values := []int{5}
	QuickSort(values)
	values2 := []int{5}
	for i := 0; i < 1; i ++ {
		if values[i] != values2[i] {
			t.Error("QuickSort() failed. Got ", values, "Expected ", values2)
		}
	}
}
