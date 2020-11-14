###
### Makefile
###
###
### Licensed under GNU GPL v3
###
###

.PHONY: clean run

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
		@rm main
		@echo "Done!"
run:dvd
	@echo "Running..."
	@./main
	@echo "Done!"