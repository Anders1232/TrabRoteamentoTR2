#ifndef NODE_HPP
#define NODE_HPP

#include<iostream>
#include <vector>
#include<map>

#define INFINITO -1

struct RegRoteamento{
	
	int destino;
	int peso;
	int nodeSaida;

	bool operator==(RegRoteamento cmp) const
	{
		if(this->destino == cmp.destino && this->peso == cmp.peso && this->nodeSaida == cmp.nodeSaida)
		{
			return true;
		}
		return false;
	}
	bool operator!=(RegRoteamento cmp) const
	{
		return(!(*(this) == cmp) );
	}
};

class Node
{
	public:
		Node(std::vector<int> adj);
		void receberTabela(const std::vector<RegRoteamento> &tabEstrangeira);
		const std::vector<RegRoteamento> obterTabela(void);
		void imprimirTabela(void) ;
	private:
		std::vector<RegRoteamento> tabela;
};

#endif
