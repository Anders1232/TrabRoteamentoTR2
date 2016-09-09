#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include<map>

#define INFINITO -1

struct RegRoteamento{
	
	int destino;
	int peso;
	int nodeSaida;
};

using namespace std;

class Node
{
	public:
		Node(vector<int> adj);
		void receberTabela(vector<RegRoteamento> &tabEstrangeira);
		void enviarTabela(void);
		const vector<RegRoteamento> obterTabela(void) const;
		void imprimirTabela(void) const;
	private:
		vector<RegRoteamento> tabela;
};

#endif
