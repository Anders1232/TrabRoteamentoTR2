#include <iostream>
#include <string>
#include <stdbool.h>
#include "Grafo.hpp"
#include "Node.hpp"

bool TabelasConvergiram(const std::vector<Node*> &nos)
{
	static bool primeiraVez=true;
	static std::vector<std::vector<RegRoteamento> > iteracaoPassada;
	if(!primeiraVez)
	{
		for(unsigned int cont=0; cont < nos.size(); cont++)
		{
			if(iteracaoPassada[cont].size() != nos[cont]->obterTabela().size())
			{
				return false;
			}
			for(unsigned int cont2=0; cont2< nos[cont]->obterTabela().size(); cont2++)
			{
				if(nos[cont]->obterTabela()[cont2] != iteracaoPassada[cont][cont2])
				{
					return false;
				}
			}
		}
	}
	else
	{
		for(int unsigned cont=0; cont < nos.size(); cont++)
		{
			iteracaoPassada[cont]=nos[cont]->obterTabela();
		}
		primeiraVez = true;
		return false;
	}
	return true;
}

int main(int argc,char **argv){

	try
	{
		std::string nomeArq;
		std::vector<Node*> nos;
		if(1 == argc){
			std::cout <<"Informe o nome do arquivo\n";
			std::cin >> nomeArq;
		}
		else
		{
			nomeArq = argv[1];
		}
		Grafo g(nomeArq);
		for(unsigned int i = 0 ; i < (unsigned int)g.obterNumNos(); i ++)
		{
			nos[i] = new Node(g[i]);
		}
		int numeroInteracoes=0;
		int numeroEnviosDeTablela=0;
		while(!TabelasConvergiram(nos))
		{
			numeroInteracoes++;
			for( unsigned int cont =0 ; cont < (unsigned int)g.obterNumNos(); cont++)//cada um nos nós
			{
				const std::vector<int> vizinhos= g[cont];
				printf("O nó %d está repassando sua tabela aos vizinhos.\n", cont+1);
				nos[cont]->imprimirTabela();
				for(unsigned int cont2=0; cont2< vizinhos.size(); cont++)//vai repassa suas info para cada um dos vizinhos
				{
					if(vizinhos[cont2] != INFINITO)
					{
						numeroEnviosDeTablela++;
						nos[cont2]->receberTabela(nos[cont]->obterTabela());
					}
				}
			}
		}
	}
	catch(std::string *str)
	{
		std::cout << *str << std::endl;
	}
	return(0);
}


