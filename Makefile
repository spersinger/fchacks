###
### Makefile
###
###
### Licensed under GNU GPL v3
###
###

.PHONY: clean install uninstall

CC = g++                        # compiler to use

LINKERFLAG = -lcurses

SRCS := source/main.cpp

BIN := main

dvd:
		@echo "Building..."
		@${CC} ${SRCS} -o ${BIN} ${LINKERFLAG}
		@echo "Done!"

clean:
		@echo "Cleaning up..."
		@rm dvd
		@echo "Done!"