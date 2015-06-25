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
	$(MAKE) -C mysql
	cp mysql/*.h include
	$(MAKE) -C record
	cp record/*.h include
	$(MAKE) -C tcp/client
	cp tcp/client/*.h include
	$(MAKE) -C ftp
	cp ftp/*.h include

.PHONY: clean
clean:
	$(MAKE) -C common clean
	$(MAKE) -C file clean
	$(MAKE) -C mysql clean
	$(MAKE) -C record clean
	$(MAKE) -C tcp/client clean
	$(MAKE) -C ftp clean

.PHONY: cleanall
cleanall:
	$(MAKE) -C common cleanall
	$(MAKE) -C file cleanall
	$(MAKE) -C mysql cleanall
	$(MAKE) -C record cleanall
	$(MAKE) -C tcp/client cleanall
	$(MAKE) -C ftp cleanall
	rm -rf include/*.h
