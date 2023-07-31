all:
	g++ *.cc -o tixt -I. -Wall -Wextra -lncurses -std=c++20

sandwich:
	cp ./tixt /usr/bin
