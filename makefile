all:
	g++ Grafo.cpp main.cpp Node.cpp -g -Wall -pedantic -std=c++11
static:
	g++ Grafo.cpp main.cpp Node.cpp -g -Wall -pedantic -std=c++11 -static -o static.out
