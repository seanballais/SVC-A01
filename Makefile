all:
	mkdir -p bin
	g++ -std=c++11 -Iinclude/ src/Memory.cpp src/CPU.cpp src/main.cpp -o bin/cpu