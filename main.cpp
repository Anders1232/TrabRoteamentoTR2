#include <iostream>
#include <string>
#include <cstdbool>
#include "Grafo.hpp"
#include "Node.hpp"
#include "ArgumentAnalizer.h"
#include "modos.h"

//#define DEBUG_MAIN

//#define BEBUG_GETCHAR_MAIN
//#define BREAK_PRIMEIRA_PASSADA_TABELAS_CONVERGIRAM

void MensagemDeBoasVindas(void)
{
	printf("-------------------------------------------------------\n");
	printf("Trabalho de Roteamento de TR2  Copyleft 2016  Francisco Anderson Bezerra Rodrigues e Vitor Silva de Deus\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY;\n");
	printf("This is free software, and you are welcome to redistribute it under certain conditions;\n");
	printf("-------------------------------------------------------\n");
}

void MensagemDeAjuda(void)
{
	printf("Modo de usar: ");
	printf("'NomeDoExecutavel' [OPCOES]*\nAs possiveis opcoes sao:\n");
	printf("-i 'NomeDoArquivo'\t\tpara informar o arquivo com a descricao do grafo\n");
	printf("-s \t\t\t\tpara rodar o programa no modo silencioso\n");
	printf("-v \t\t\t\tpara rodar o programa no modo verboso\n");
	printf("--verboso \t\t\tpara rodar o programa no modo muito verboso\n");
	printf("-h \t\t\t\tpara exibir essa mensagem\n\n");
}
/*Método que verifica se os vetores do todos os nós convergiram comparando-os com seus valores na iretação anterior.
Se todos permanecem iguais a iteração anterior significa que a topologia convergiu*/
bool TabelasConvergiram(const std::vector<Node*> &nos)
{
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
//Função que compara o número de dois nós do grafo
bool CompararDestinos(RegRoteamento &a, RegRoteamento &b)
{
	return ( (a.destino) < (b.destino) );
}

int main(int argc,char **argv)
{
	MensagemDeBoasVindas();
	try
	{
		//Analisar os argumentos de linha de comando
		if(argc == 1 || SEARCH_FAILED != ArgumentAnalizer::FindArgument("-h", argc, argv))
		{
			MensagemDeAjuda();
		}
		if(SEARCH_FAILED != ArgumentAnalizer::FindArgument("-h", argc, argv))
		{
			return 0;
		}
		int modo= MODO_NORMAL;
		if(SEARCH_FAILED != ArgumentAnalizer::FindArgument("-s", argc, argv))
		{
			modo= MODO_SILENCIOSO;
		}
		if(SEARCH_FAILED != ArgumentAnalizer::FindArgument("-v", argc, argv))
		{
			modo= MODO_VERBOSO;
		}
		if(SEARCH_FAILED != ArgumentAnalizer::FindArgument("--verboso", argc, argv))
		{
			modo= MODO_MUITO_VERBOSO;
		}
		
		//Agora sim o programa em si
		std::string nomeArq;
		std::vector<Node*> nos;
		int posicaoArquivo = ArgumentAnalizer::FindArgument("-i", argc, argv);
		if(SEARCH_FAILED == posicaoArquivo){
			std::cout <<"Informe o nome do arquivo\n";
			std::cin >> nomeArq;
		}
		else
		{
			nomeArq = argv[posicaoArquivo+1];
		}
		//Cria o grafo
		Grafo g(nomeArq);

		//Cria uma cópia do grafo
		for(int i = 0 ; i < g.ObterNumeroDeNos(); i ++)
		{

			nos.push_back(new Node(g[i]) );

		}

		int numeroInteracoes=0;
		int numeroEnviosDeTablela=0;
		/*Enquanto as tabelas não convergiram,o programa realiza a troca de tabelas de modo sequencial,ou seja:
		1) O primeiro nó envia seu vetor para seus vizinhos
		2)Os vizinhos computam e obtêm um novo vetor.Esses enviam para seus vizinhos que voltam ao passo 1*/
		while(!TabelasConvergiram(nos))
		{

			numeroInteracoes++;
			for( unsigned int cont =0 ; cont < (unsigned int)g.ObterNumeroDeNos(); cont++)//cada um nos nós
			{

				const std::vector<int> vizinhos= g[cont];
				if(MODO_SILENCIOSO != modo)
				{
					printf("\nO nó %d está repassando sua tabela aos vizinhos.\n", cont+1);
					nos[cont]->imprimirTabela();
				}
				for(unsigned int cont2=0; cont2< vizinhos.size(); cont2++)//vai repassa suas info para cada um dos vizinhos
				{

					if(vizinhos[cont2] != INFINITO && vizinhos[cont2] != 0)
					{

						numeroEnviosDeTablela++;
						nos[cont2]->receberTabela(nos[cont]->obterTabela(), modo);
					}
				}
			}
		}
		printf("-------------------------------------------------------\n");
		printf("As tabelas convergiram =D\n");
		printf("\t numero de iterações necessárias: %d\n", numeroInteracoes-1);
		printf("\t numero de trocas de tabela necessárias(incluindo as redundantes): %d\n", numeroEnviosDeTablela- 2*g.ObterNumeroDeArestas()/*-g.obterNumNos()*/);
		printf("-------------------------------------------------------\n");
	}
	catch(std::string *str)
	{
		std::cout << *str << std::endl;
	}
	return(0);
}


