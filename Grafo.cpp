#include"Grafo.hpp"
#include<string>
#include<cstdio>

//#define DEBUG

Grafo::Grafo(string nomeArq)
{	
	FILE *arq;
	char aux;

	arq = fopen(nomeArq.c_str(),"r");
	if(arq == NULL)
	{
		throw(new string("Erro ao abrir o arquivo!\n"));
	}
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	int numeroDeLinhas=1;//o arquivo já começa com 1 linha
	while(EOF != fscanf(arq, "%c", &aux))
	{
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		if('\n'== aux)
		{
			numeroDeLinhas++;
		}
	}
	rewind(arq);
	grafo.resize(numeroDeLinhas);//configuro o tamanho da primeira dimensão
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{
		grafo[cont].resize(numeroDeLinhas);//configuro o tamanho da segunda dimensão
	}
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif

	int origem, destino,peso;
	for(int cont1 =0; cont1 < numeroDeLinhas; cont1++)
	{
		for(int cont2 =0; cont2 < numeroDeLinhas; cont2++)
		{
			grafo[cont1][cont2]= INFINITO;
		}
	}
#ifdef DEBUG
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
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
		if(1 == resultadoFscanf)
		{
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			origem= destino;
		}
		else if(0 == fscanf(arq, " %d;", &origem) )
		{
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
//printf("origem: %d\tdestino: %d\tpeso: %d\n", origem, destino, peso);
#endif
			throw(new string("Arquivo no formato invalido!\n"));
		}

		do
		{
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
			resultadoFscanf= fscanf(arq, "%d[%d];", &destino, &peso);
			if(2 != resultadoFscanf)
			{
				break;
			}
			grafo[origem - 1][destino - 1]= peso;
			grafo[destino - 1][origem - 1]= peso;
printf("origem: %d\tdestino: %d\tpeso: %d\n", origem, destino, peso);
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
printf("origem: %d\tdestino: %d\tpeso: %d\n", origem, destino, peso);
#endif
			
		}
		while(1);
	}
	for(unsigned int cont =0; cont < grafo.size(); cont++)
	{
		grafo[cont][cont]= 0;
	}
	fclose(arq);
}

int Grafo::obterNumNos(){

	return(grafo.size());

}

vector<int> Grafo::operator[](int pos)
{
	return grafo[pos];
}
