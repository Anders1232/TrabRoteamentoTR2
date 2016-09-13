# TrabRoteamentoTR2

Componentes do grupo:

Vitor Silva de Deus 110143574
Francisco Anderson 

Limitações:

A simulação não considera concorrência nas trocas e cálculos realizados por cada nó do grafo.
Fato este que pode alterar o tempo de convergência visto que nessa implementação cada nó recebe 
vetores de vizinhos e os computa antes de distribuir vetores já atualizados.

Formato da entrada:

nodo; vizinho1[custo]; vizinho2[custo]; · · · , vizinhoN[custo]

Exemplo:
1; 2[4]; 3[1];
2; 1[4]; 3[2];
3; 1[1]; 2[3];

Considerações importantes:

1)O grafo é unidirecional.Por isso não é necessário definir o custo de um nó x a um nó y e de y para x,basta um dos casos.
Se for feita a definição para os dois casos o programa considerará o ultimo.
2)O programa possui a premissa de que o número de linhas do arquivo é igual ao número de nós do grafo
3)As três topologias estão em "grafo6.txt","grafo8.txt" e "grafo16.txt".

Instruções para compilação: make

Instruções para execução:

./a.out [OPCOES]*
As possiveis opcoes sao:
-i 'NomeDoArquivo'		para informar o arquivo com a descricao do grafo
-s 				para rodar o programa no modo silencioso
-v 				para rodar o programa no modo verboso
--verboso 			para rodar o programa no modo muito verboso
-h 				para exibir essa mensagem

OU

./a.out e informar o nome do arquivo após iniciar a execução.



