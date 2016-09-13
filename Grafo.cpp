#include"Grafo.hpp"

//#define DEBUG_GRAFO

#ifdef DEBUG_GRAFO
#include<cstdio>
#endif
//Construtor do objeto que representa a topologia completa
Grafo::Grafo(std::string nomeArq)
{
	//Leitura do arquivo
	FILE *arq;
	char aux,aux2;

	arq = fopen(nomeArq.c_str(),"r");
	if(arq == NULL)
	{
		throw(new std::string("Erro ao abrir o arquivo!\n"));
	}
	//No loop abaixo descobre o número de linhas do arquivo,ou seja, o número de nós e também dimensão da matriz de adjacencias
	int numeroDeLinhas= 1;//o arquivo já começa com 1 linha
	while(EOF != fscanf(arq, "%c", &aux))
	{
		if('\n'== aux)
		{
			numeroDeLinhas++;
			aux2= getc(arq);
			if(EOF == aux2)
			{//se sim, o arquivo termina com um \n, que não deve ser contado pro numero de linhas
				numeroDeLinhas--;
			}
			else
			{//senão desfaz essa última leitura e continua
				ungetc(aux2, arq);
			}
		}
	}
	rewind(arq);
	grafo.resize(numeroDeLinhas);//configuro o tamanho da primeira dimensão da matriz de adjacências
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{
		grafo[cont].resize(numeroDeLinhas);//configuro o tamanho da segunda dimensão da matriz
	}
	//Inicializa a matriz de adjacências com pesos infinitos em todas as posições
	int origem, destino,peso;
	for(int cont1 =0; cont1 < numeroDeLinhas; cont1++)
	{
		for(int cont2 =0; cont2 < numeroDeLinhas; cont2++)
		{
			grafo[cont1][cont2]= INFINITO;
		}
	}
	//Aqui realiza a leitura do grafo
	int resultadoFscanf=0;
	for(int cont =0; cont < numeroDeLinhas; cont++)
	{//vou supor que na linha x tem as informações do nodo x, ou seja, será começado com x; 
		aux= getc(arq);
		if(';' != aux)
		{
			ungetc(aux, arq);
		}

		if(1 == resultadoFscanf)
		{
			origem= destino;
		}
		else if(0 == fscanf(arq, " %d;", &origem) )
		{

			throw(new std::string("Arquivo no formato invalido!\n"));
		}

		do
		{

			resultadoFscanf= fscanf(arq, "%d[%d];", &destino, &peso);
			if(2 != resultadoFscanf)
			{
				break;
			}
			grafo[origem - 1][destino - 1]= peso;
			grafo[destino - 1][origem - 1]= peso;
			
		}
		while(1);
	}
	//Atribui a distância zero de cada nó para ele mesmo
	for(unsigned int cont =0; cont < grafo.size(); cont++)
	{
		grafo[cont][cont]= 0;
	}

	fclose(arq);

}
//Método para retornar o tamanho(dimensão) da matriz ou grafo
int Grafo::obterNumNos(void)
{
	return(grafo.size());
}
//Redefinição do operador '[]' nessa classe.O mesmo passa a retornar uma linha inteira da matriz
std::vector<int>& Grafo::operator[](int pos)
{

	return grafo.at(pos);
}
