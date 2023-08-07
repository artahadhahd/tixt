all:
	@g++ src/*.cc -o tixt -I. -g -Wall -Wextra -lncurses -std=c++20

install:
	strip ./tixt
	cp ./tixt /usr/bin
