#ifndef GRAFO_HPP
#define GRAFO_HPP

#include<cstdio>
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
