#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

#define INFINITO -1

struct RegRoteamento{
	
	int destino;
	int peso;
	int nodeSaida;

	inline bool operator==(RegRoteamento cmp) const
	{
		if(this->destino == cmp.destino && this->peso == cmp.peso && this->nodeSaida == cmp.nodeSaida)
		{
			return true;
		}
		return false;
	}
	inline bool operator!=(RegRoteamento cmp) const
	{
		return(!( (*this) == cmp) );//=D
	}
};

class Node
{
	public:
		Node(const std::vector<int>& adj);
		void receberTabela(const std::vector<RegRoteamento> &tabEstrangeira);
		const std::vector<RegRoteamento>& obterTabela(void);
		void imprimirTabela(void) const;
	private:
		int id;
		int PosicaoNaTabela();//não pode ser um atributo pois pode variar durante a execução
		std::vector<RegRoteamento> tabela;

//membros especias
		Node (const Node&);
		Node& operator= (const Node&);
};

#endif
