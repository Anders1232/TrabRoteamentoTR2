#include"Node.hpp"

Node::Node(vector<int> adj)
{
	for(unsigned int i = 0 ; i < adj.size() ; i ++)
	{
		if(adj[i] != INFINITO)
		{
			tabela.push_back({adj[i],(int)i});
		}
	}
}

void Node::receberTabela(vector<RegRoteamento> &tabelaEstrangeira)
{
	int quemEnviou, posicaoNaTabelaLocalDeQuemEnviou;
	for(unsigned int i = 0 ; i < tabelaEstrangeira.size() ; i ++)
	{
		if(0 == tabelaEstrangeira[(int)i].peso)
		{
			quemEnviou= tabelaEstrangeira[i].destino;
			break;
		}
	}
	for(unsigned int i = 0 ; i < tabela.size() ; i ++)
	{
		if(tabela[i].destino == quemEnviou)
		{
			posicaoNaTabelaLocalDeQuemEnviou= i;
			break;
		}
	}

	for(unsigned int posicaoTabelaEstrangeira = 0 ; posicaoTabelaEstrangeira < tabelaEstrangeira.size() ; posicaoTabelaEstrangeira ++)
	{
		int posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada= -1;
		for(int posicaoTabelaLocal =0 ; (unsigned int)posicaoTabelaLocal < tabela.size(); posicaoTabelaLocal++)
		{
			if(tabelaEstrangeira[posicaoTabelaEstrangeira].destino == tabela[posicaoTabelaLocal].destino)
			{
				posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada= posicaoTabelaLocal;
				break;
			}
		}
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
		{//Tem-se o destino na tabela local, verificar se precisa atualizar
			if(pesoCandidato < tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].peso)
			{
				tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].peso= pesoCandidato;
				tabela[posicaoNaMinhaTabelaDaEntradaEstrangeiraAnalisada].nodeSaida= quemEnviou;
			}
		}
	}
}

void enviarTabela(void)
{
	
}




