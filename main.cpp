#include "Grafo.hpp"
#include <iostream>
#include <string>
#include<stdbool.h>
#include"Node.hpp"

using namespace std;

bool TabelasConvergiram(vector<Node*> nos)
{
	static bool primeiraVez=true;
	static vector<vector<RegRoteamento> > iteracaoPassada;
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
		string nomeArq;
		vector<Node*> nos;
		if(1 == argc){
			cout <<"Informe o nome do arquivo\n";
			cin >> nomeArq;
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
		while(!TabelasConvergiram(nos))
		{
			numeroInteracoes++;
			for( unsigned int cont =0 ; cont < (unsigned int)g.obterNumNos(); cont++)
			{
				vector<int> vizinhos= g[cont];
				for(unsigned int cont2=0; cont2< vizinhos.size(); cont++)
				{
					if(vizinhos[cont2] != INFINITO)
					{
						nos[cont2]->receberTabela(nos[cont]->obterTabela());
					}
				}
			}
		}
	}
	catch(string *str)
	{
		cout << *str << endl;
	}
	return(0);
}


