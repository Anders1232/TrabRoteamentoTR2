#include "Grafo.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char **argv){

	string nomeArq;

	if(1 == argc){

		cout <<"Informe o nome do arquivo\n";
		cin >> nomeArq;

	}

	else {

		nomeArq = argv[1];

	}
	try{
		Grafo g(nomeArq);
	}
	catch(string *str)
	{
		cout << *str << endl;
	}
	return(0);
}

	
