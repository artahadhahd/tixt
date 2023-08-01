all:
	@g++ src/*.cc -g3 -o tixt -g -I. -Wall -Wextra -lncurses -std=c++20

install:
	cp ./tixt /usr/bin
