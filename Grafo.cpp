#include"Grafo.hpp"
#include<string>

#define INFINITO -1
#define DEBUG

Grafo::Grafo(string nomeArq)
{	
	FILE *arq;
	char aux;

	arq = fopen(nomeArq.c_str(),"r");

	if(arq == NULL){

		throw(new string("Erro ao abrir o arquivo!\n"));

	}
#ifdef DEBUG
printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
#endif
	int numeroDeLinhas=1;//o arquivo já começa com 1 linha

	while(EOF != fscanf(arq, "%c", &aux))
	{
		printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
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

	for(int cont =0; cont < numeroDeLinhas; cont++)
	{//vou supor que na linha x tem as informações do nodo x, ou seja, será começado com x; 
		#ifdef DEBUG
		printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
		#endif
		if(0 == fscanf(arq, " %d;", &origem) )
		{
			throw(new string("Arquivo no formato invalido!\n"));
		}
		while(fscanf(arq, "%d[%d];", &destino, &peso))
		{//suponho que no arquivo, os nodos do grafo estão indexados a partir de zero.
			grafo[origem - 1][destino - 1]= peso;
			grafo[destino - 1][origem - 1]= peso;
		#ifdef DEBUG
		printf("checkpoint: %s\t\t%d\n", __FILE__, __LINE__);
		#endif
		}

	}

	fclose(arq);

}
