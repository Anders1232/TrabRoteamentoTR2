#include<cstdio>
#include<algorithm>
#include"Node.hpp"
#include "modos.h"

//#define DEBUG_NODE

//Construtor do objeto que representa um nó do grafo(topologia completa)
//Recebe como argumento a linha na matriz de adjacências correspondente a esse nó
Node::Node(const std::vector<int> &adj)
{
//Aqui tabela é um nome que representa vetor de distâncias
//Constroi a tabela de adjacências desse nó
//A tabela guarda o destino,o peso total do caminho e o nó de saída para cada outro nó do grafo
	for(unsigned int i = 0 ; i < adj.size(); i++)
	{

		if(adj.at(i) != INFINITO)
		{

			tabela.push_back({(int)i,adj.at(i),(int)i});
			//Se o peso for zero a posição corresponde a esse nó
			if(0 == adj.at(i) )
			{

				id= i;
			}
		}
	}

}
//Método que implementa o recebimento de uma tabela para um nó
void Node::receberTabela(const std::vector<RegRoteamento> &tabelaEstrangeira, int modo)
{
	int quemEnviou, posicaoNaTabelaLocalDeQuemEnviou;
	for(unsigned int i = 0 ; i < tabelaEstrangeira.size() ; i ++)
	{
		/*Deduz qual o nó que enviou a partir da informação de que em sua tabela
		a distância para ele mesmo é zero*/
		if(0 == tabelaEstrangeira[(int)i].peso)
		{
			quemEnviou= tabelaEstrangeira[i].destino;
			break;
		}
	}
	//Descobre a posição do nó remetente na tabela local
	for(unsigned int i = 0 ; i < tabela.size() ; i ++)
	{
		if(tabela[i].destino == quemEnviou)
		{
			posicaoNaTabelaLocalDeQuemEnviou= i;
			break;
		}
	}
	//Defines para quantidade de informações a serem mostradas
	if(MODO_SILENCIOSO != modo)
	{
		printf("No %d recebeu a tabela do no %d\n", id+1, quemEnviou+1);
	}
	if(MODO_MUITO_VERBOSO == modo)
	{
		printf("Estado da tabela antes do cálculo das rotas:\n");
		imprimirTabela();
	}
	//Nesse loop é implementado o algoritmo de Belmann-Ford
	/*Para cada posição de vetor de distâncias do remetente,calcula um peso candidato e o sustitui na tabela local caso necessário*/
	for(unsigned int posicaoTabelaEstrangeira = 0 ; posicaoTabelaEstrangeira < tabelaEstrangeira.size() ; posicaoTabelaEstrangeira ++)
	{
		int posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada= -1;
		//Loop para descobrir qual é a posição do destino que está sendo analisado no vetor de distâncias local
		for(int posicaoTabelaLocal =0 ; (unsigned int)posicaoTabelaLocal < tabela.size(); posicaoTabelaLocal++)
		{
			if(tabelaEstrangeira[posicaoTabelaEstrangeira].destino == tabela[posicaoTabelaLocal].destino)
			{
				posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada= posicaoTabelaLocal;
				break;
			}
		}
		//Calculo da fórmula de bellman ford
		int pesoCandidato = tabelaEstrangeira[posicaoTabelaEstrangeira].peso + tabela[posicaoNaTabelaLocalDeQuemEnviou].peso;
		if(-1 == posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada)
		{//esse destino nao tem na tabela local, adicionemos
			tabela.push_back({
				tabelaEstrangeira[posicaoTabelaEstrangeira].destino,
				pesoCandidato,
				quemEnviou
			});
		}
		else
		{/*Tem-se o destino na tabela local, verificar se precisa atualizar,ou seja,se o peso candidato calculado anteriormente 
		é menor que o atual ou não*/
			if(pesoCandidato < tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].peso)
			{
				tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].peso= pesoCandidato;
				tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].nodeSaida= quemEnviou;
			}
		}
	}
	std::sort(tabela.begin(), tabela.end());
	if(MODO_VERBOSO == modo || MODO_MUITO_VERBOSO == modo)
	{
		printf("Estado da tabela após do cálculo das rotas:\n");
		imprimirTabela();
	}
}
//Método que retorna o vetor de distâncias do nó corrente
const std::vector<RegRoteamento>& Node::obterTabela(void)const
{
	return(tabela);
}
//Imprime o vetor de distâncias local
void Node::imprimirTabela(void)const
{
	printf("\nImprimindo tabela do nó %d\n", id+1);
	for(unsigned int i = 0 ; i < tabela.size() ; i ++)
	{
		printf("\tdestino: %d \t peso: %d \tsaída: %d\n",tabela[i].destino+1,tabela[i].peso,tabela[i].nodeSaida+1);
	}
}

