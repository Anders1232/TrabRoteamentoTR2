#include"Grafo.hpp"
#include<string>

#define INFINITO -1

Grafo::Grafo(FILE *arq)
{
	int numeroDeLinhas=1;//o arquivo já começa com 1 linha
	char aux;
	while(fscanf(arq, "%c", &aux))
	{
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
	
	int aux1, aux2;
	for(int cont1 =0; cont1 < numeroDeLinhas; cont1++)
	{
		for(int cont2 =0; cont2 < numeroDeLinhas; cont2++)
		{
			grafo[cont1][cont2]= INFINITO;
		}
	}
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{//vou supor que na linha x tem as informações do nodo x, ou seja, será começado com x; 
		if(0 == fscanf(arq, "%d;", &aux1) )
		{
			throw(new string("Arquivo no formato invalido!\n"));
		}
		if(aux != cont )
		{
			throw(new string("Arquivo no formato invalido!\n"));
		}
		while(fscanf(arq, "%d[%d];", &aux1, &aux2))
		{//suponho que no arquivo, os nodos do grafo estão indexados a partir de zero.
			grafo[cont][aux]= aux2;
			grafo[aux][cont]= aux2;
		}
	}
}
