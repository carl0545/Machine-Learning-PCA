CXX=g++
SHELL=/bin/sh

CPPFLAGS=-O3 -Wall
CFLAGS=$(CPPFLAGS)
LIBS = -lm

NAME=\
pca

BIN=\
pca

SRCS=\
pca.cpp\
mat.cpp\
randf.cpp

HDRS=\
mat.h\
rand.h

OBJS=\
mat.o\
rand.o

$(BIN): $(OBJS) $(BIN).o
	$(CXX)  $(CFLAGS) $(OBJS) $(BIN).o $(LIBS) -o $(NAME)

clean:
	/bin/rm -f *.o a.out
