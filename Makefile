###
### Makefile
###
###
### Licensed under GNU GPL v3
###
###

.PHONY: build clean run

CC = g++                        # compiler to use

SRCS := source/main.cpp

BIN := main

dvd:
	@echo "Building Main..."
	@${CC} ${SRCS} -o ${BIN}
	@echo "Done!"

vis:
	@echo "Building Visualizer..."
	@${CC} source/visualizer.cpp -o visualizer
	@echo "Done!"

clean:
	@echo "Cleaning up..."
	@rm main visualizer
	@echo "Done!"

build:dvd vis
	@echo "Done Building!";

run:
	@echo "Running..."
	@./main | ./visualizer
	@echo "Done!"

build-run:build run