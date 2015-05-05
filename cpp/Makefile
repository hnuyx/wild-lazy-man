#****************************************************************************
#
# Makefile for cpp
# henuyx
# 2015-05-04
#
#****************************************************************************

.PHONY: all
all: qsort kmp

qsort: qsort.o
	g++ -o qsort qsort.o

kmp: kmp.o
	g++ -o kmp kmp.o

.PHONY: clean
clean:
	rm -f *.o

.PHONY: cleanall
cleanall:
	rm -f *.o qsort kmp
