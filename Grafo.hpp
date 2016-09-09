#ifndef GRAFO_HPP
#define GRAFO_HPP

#define INFINITO -1

#include <vector>
#include<string>

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
