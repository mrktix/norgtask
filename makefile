all: main

main: src/main.cpp
	g++ -lncurses src/main.cpp -o bin/main
