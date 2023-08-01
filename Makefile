all:
	@g++ src/*.cc -o tixt -I. -Wall -Wextra -lncurses -std=c++20
	@echo "Compiled Successfully. Run 'make install' as root now."

install: ~/.config/tixt
	cp ./tixt /usr/bin
