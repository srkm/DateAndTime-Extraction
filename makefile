CFLAGS=-g -Wall
LDFLAGS=-lncurses

.PHONY: clean

all:
	g++ $(CFLAGS) bouncingBall.cpp -o BouncingBall $(LDFLAGS) -std=c++11

clean:
	rm -rf BouncingBall
