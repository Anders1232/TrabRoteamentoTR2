#ifndef ARESTA_HPP
#define ARESTA_HPP

#include<cstdio>

class Aresta
{
	public:
		Aresta(Aresta&);
		Aresta(FILE *arq);
	private:
		int origem;
		int destino;
		int peso;
}

#endif
