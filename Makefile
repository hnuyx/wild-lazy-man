#****************************************************************************
#
# Makefile for base library
# henuyx
# 2015-04-28
#
#****************************************************************************

.PHONY: all
all:
	mkdir -p include
	mkdir -p libs
	$(MAKE) -C common
	cp common/*.h include
	$(MAKE) -C file
	cp file/*.h include

.PHONY: clean
clean:
	$(MAKE) -C common clean
	$(MAKE) -C file clean

.PHONY: cleanall
cleanall:
	$(MAKE) -C common cleanall
	$(MAKE) -C file cleanall
	rm -rf include/*.h
