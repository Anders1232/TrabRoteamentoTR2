#ifndef GRAFO_HPP
#define GRAFO_HPP

#include<vector>
#include<string>
//#include<climits>

#define INFINITO -1
//Classe que representa toda a topologia
class Grafo
{
	public:
		//Construtor de um objeto do tipo grafo
		Grafo(std::string nomeArq);
		//Método para retornar o tamanho(dimensão) da matriz ou grafo
		//Redefinição do operador '[]' nessa classe.O mesmo passa a retornar uma linha inteira da matriz
		std::vector<int>& operator[](int pos);
		int ObterNumeroDeNos(void);
		int ObterNumeroDeArestas(void);
	private:
		//Matriz de adjacências
		std::vector<std::vector<int> > grafo;
		//membros especias
		Grafo (const Grafo&);
		Grafo& operator= (const Grafo&);
};

#endif
