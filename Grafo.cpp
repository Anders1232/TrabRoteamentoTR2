#include"Grafo.hpp"

//#define DEBUG_GRAFO

#ifdef DEBUG_GRAFO
#include<cstdio>
#endif

Grafo::Grafo(std::string nomeArq)
{
	FILE *arq;
	char aux,aux2;

	arq = fopen(nomeArq.c_str(),"r");
	if(arq == NULL)
	{
		throw(new std::string("Erro ao abrir o arquivo!\n"));
	}
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	int numeroDeLinhas= 1;//o arquivo já começa com 1 linha
	while(EOF != fscanf(arq, "%c", &aux))
	{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		if('\n'== aux)
		{
			numeroDeLinhas++;
			aux2= getc(arq);
			if(EOF == aux2)
			{//se sim, o arquivo termina com um \n, que não deve ser contado pro numero de linhas
				numeroDeLinhas--;
printf("Esse arquivo ter um '\\n' a mais !\n");
			}
			else
			{//senão desfaz essa última leitura e continua
				ungetc(aux2, arq);
			}
		}
	}
	rewind(arq);
	grafo.resize(numeroDeLinhas);//configuro o tamanho da primeira dimensão
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{
		grafo[cont].resize(numeroDeLinhas);//configuro o tamanho da segunda dimensão
	}
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
printf("numeroDeLinhas= %d\n", numeroDeLinhas);
#endif

	int origem, destino,peso;
	for(int cont1 =0; cont1 < numeroDeLinhas; cont1++)
	{
		for(int cont2 =0; cont2 < numeroDeLinhas; cont2++)
		{
			grafo[cont1][cont2]= INFINITO;
		}
	}
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif

	int resultadoFscanf=0;
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{//vou supor que na linha x tem as informações do nodo x, ou seja, será começado com x; 
		aux= getc(arq);
		if(';' != aux)
		{
			ungetc(aux, arq);
		}
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		if(1 == resultadoFscanf)
		{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			origem= destino;
		}
		else if(0 == fscanf(arq, " %d;", &origem) )
		{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
//printf("origem: %d\tdestino: %d\tpeso: %d\n", origem, destino, peso);
#endif
			throw(new std::string("Arquivo no formato invalido!\n"));
		}

		do
		{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			resultadoFscanf= fscanf(arq, "%d[%d];", &destino, &peso);
			if(2 != resultadoFscanf)
			{
				break;
			}
			grafo[origem - 1][destino - 1]= peso;
			grafo[destino - 1][origem - 1]= peso;
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
printf("origem: %d\tdestino: %d\tpeso: %d\n", origem, destino, peso);
#endif
			
		}
		while(1);
	}
	for(unsigned int cont =0; cont < grafo.size(); cont++)
	{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		grafo[cont][cont]= 0;
	}
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	fclose(arq);
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
}

int Grafo::obterNumNos(void)
{
	return(grafo.size());
}

std::vector<int>& Grafo::operator[](int pos)
{
#ifdef DEBUG_GRAFO
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	return grafo.at(pos);
}
