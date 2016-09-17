#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
//#include<climits>

#define INFINITO -1
//Estrutura que representa cada posição do vetor de distâncias
struct RegRoteamento{
	
	int destino;
	int peso;
	int nodeSaida;
	//Definição do operador de igualdade para essa estrutura
	inline bool operator==(RegRoteamento cmp) const
	{
		if(this->destino == cmp.destino && this->peso == cmp.peso && this->nodeSaida == cmp.nodeSaida)
		{
			return true;
		}
		return false;
	}
	//Definição do operador de não igualdade para essa estrutura
	inline bool operator!=(RegRoteamento cmp) const
	{
		return(!( (*this) == cmp) );//=D
	}
	//Função que compara o número de dois nós do grafo
	inline bool operator<(/*const RegRoteamento &a,*/ const RegRoteamento &b)const
	{
		return ( (this->destino) < (b.destino) );
	}
};
//Classe que representa o nó
class Node
{
	public:
		//COnstrutor
		Node(const std::vector<int>& adj);
		//Recebe vetor de distâncias
		void receberTabela(const std::vector<RegRoteamento> &tabEstrangeira, int modo);
		//Retorna o vetor de sistâncias desse nó
		const std::vector<RegRoteamento>& obterTabela(void) const;
		//imprime a tabela
		void imprimirTabela(void) const;
	private:
		//Numero de identificacao do nó
		int id;
		//vetor de distâncias
		std::vector<RegRoteamento> tabela;

		//membros especias
		Node (const Node&);
		Node& operator= (const Node&);
};

#endif
