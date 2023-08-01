all:
	@g++ src/*.cc -o tixt -g -I. -Wall -Wextra -lncurses -std=c++20

install: ~/.config/tixt
	cp ./tixt /usr/bin
