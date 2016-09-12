#ifndef GRAFO_HPP
#define GRAFO_HPP

#include<vector>
#include<string>
#include<climits>

#define INFINITO INT_MAX/2

class Grafo
{
	public:
		Grafo(std::string nomeArq);
		int obterNumNos(void);
		std::vector<int>& operator[](int pos);
	private:
		std::vector<std::vector<int> > grafo;
//membros especias
		Grafo (const Grafo&);
		Grafo& operator= (const Grafo&);
};

#endif
