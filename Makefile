all:
	@g++ src/*.cc -o tixt -I. -g -O3 -Wall -Wextra -lncurses -std=c++20

install:
	strip ./tixt
	cp ./tixt /usr/bin
