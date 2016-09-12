#include <iostream>
#include <string>
#include <cstdbool>
#include "Grafo.hpp"
#include "Node.hpp"

#define DEBUG_MAIN

//#define BEBUG_GETCHAR_MAIN
//#define BREAK_PRIMEIRA_PASSADA_TABELAS_CONVERGIRAM

bool TabelasConvergiram(const std::vector<Node*> &nos)
{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	static bool primeiraVez=true;
	static std::vector<std::vector<RegRoteamento> > iteracaoPassada;
	bool convergiu=true;
	if(!primeiraVez)
	{
		for(unsigned int cont=0; cont < nos.size(); cont++)
		{
			if(iteracaoPassada[cont].size() != nos[cont]->obterTabela().size())
			{
				convergiu=false;
				break;
			}
			else if(nos[cont]->obterTabela().size() != nos.size())
			{
				convergiu=false;
				break;
			}
			else
			{
				for(unsigned int cont2=0; cont2< nos[cont]->obterTabela().size(); cont2++)
				{
					if(nos[cont]->obterTabela()[cont2] != iteracaoPassada[cont][cont2])
					{
						convergiu=false;
						break;
					}
				}
				if(!convergiu)
				{
					break;
				}
			}
		}
		if(!convergiu)
		{
			for(int unsigned cont=0; cont < nos.size(); cont++)
			{
				iteracaoPassada.at(cont)= nos[cont]->obterTabela();
			}
			return false;
		}
	}
	else
	{
		for(int unsigned cont=0; cont < nos.size(); cont++)
		{
			iteracaoPassada.push_back(nos[cont]->obterTabela());
		}
		primeiraVez = false;
		return false;
	}
	return true;
}

int main(int argc,char **argv)
{
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
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		Grafo g(nomeArq);
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
printf("g.obterNumNos()= %d\n", g.obterNumNos());
//exit(0);
#endif
//		nos.reserve(g.obterNumNos());
		for(int i = 0 ; i < g.obterNumNos(); i ++)
		{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			nos.push_back(new Node(g[i]) );
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
printf("i = %d\n", i);
#endif
		}
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		int numeroInteracoes=0;
		int numeroEnviosDeTablela=0;
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		while(!TabelasConvergiram(nos))
		{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			numeroInteracoes++;
			for( unsigned int cont =0 ; cont < (unsigned int)g.obterNumNos(); cont++)//cada um nos nós
			{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
				const std::vector<int> vizinhos= g[cont];
				printf("O nó %d está repassando sua tabela aos vizinhos.\n", cont+1);
				nos[cont]->imprimirTabela();
				for(unsigned int cont2=0; cont2< vizinhos.size(); cont2++)//vai repassa suas info para cada um dos vizinhos
				{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
					if(vizinhos[cont2] != INFINITO && vizinhos[cont2] != 0)
					{
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
						numeroEnviosDeTablela++;
						nos[cont2]->receberTabela(nos[cont]->obterTabela());
					}
				}
			}
#ifdef DEBUG_MAIN
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		}
		printf("-------------------------------------------------------\n");
		printf("As tabelas convergiram =D\n");
		printf("\t numero de iterações necessárias: %d\n", numeroInteracoes-1);
		printf("\t numero de trocas de tabela necessárias: %d\n", numeroEnviosDeTablela-g.obterNumNos());
		printf("-------------------------------------------------------\n");
	}
	catch(std::string *str)
	{
		std::cout << *str << std::endl;
	}
	return(0);
}


