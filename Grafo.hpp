#ifndef GRAFO_HPP
#define GRAFO_HPP

#include<cstdio>
#include <vector>
#include"Aresta.hpp"

class Grafo
{
	public:
		Grafo operator=(&Grafo g);
		Grafo(FILE *arq);
	private:
		vector<vector<int>> *grafo;
}

#endif
