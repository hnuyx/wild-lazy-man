#****************************************************************************
#
# Makefile for ftp operation
# henuyx
# 2015-06-18
#
#****************************************************************************

CXX	:= g++

INC_HEAD:= -I"../include"
INC_SLIB:=
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

LIBS	:= -shared
AR	:= ar rc

LIBSPATH:= ../libs

OUTPUT	:= libFtpOp.so
ARLIB	:= libFtpOp.a

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all
all:$(OUTPUT)

$(OUTPUT):$(OBJECTS)
	@$(CXX) -o $@ $(LIBS) $(OBJECTS)
	cp $@ $(LIBSPATH)
	$(AR) $(ARLIB) $(OBJECTS)

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(OUTPUT) $(ARLIB) $(LIBSPATH)/$(OUTPUT)
