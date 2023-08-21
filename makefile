all:
	g++ -fsanitize=address -fno-omit-frame-pointer \
	-lncurses \
	src/*.cpp -o bin/norgtask
