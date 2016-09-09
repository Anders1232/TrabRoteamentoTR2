#ifndef GRAFO_HPP
#define GRAFO_HPP

#define INFINITO -1

#include <vector>
#include<string>

using namespace std;

class Grafo
{
	public:
		Grafo operator=(Grafo& g);
		Grafo(string nomeArq);
	private:
		vector<vector<int> > grafo;
};

#endif
