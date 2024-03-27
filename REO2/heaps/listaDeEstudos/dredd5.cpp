/*
Implemente o método alteraPrioridade() em um maxheap que armazena estruturas contendo um valor e uma prioridade.
A alteração de prioridade implica que o dado alterado deva ser rearranjado, de forma a manter as propriedades do heap.
Recomendamos que você utilize o código fornecido como base para sua implementação.

Entradas e Saídas:

A aplicação possui uma série de comandos para seu correto funcionamento, a saber:

I seguido de um valor e uma prioridade (ambos inteiros) - insere um dado no heap
R retira um elemento da raiz, imprimindo seu valor
A altera a prioridade de um elemento com um dado valor
P imprime os dados válidos do heap, para depuração
Q encerra a aplicação
Exemplo de Entrada:

10
I 10 5
I 5 10
I 13 3
I 3 13
I 8 51
I 51 8
I 4 4
I 3 3
P
R
P
I 14 15
P
R
P
A 51 0
A 5 90
P
Q
Exemplo de Saída:

[8/51] [3/13] [51/8] [10/5] [5/10] [13/3] [4/4] [3/3]
8
[3/13] [5/10] [51/8] [10/5] [3/3] [13/3] [4/4]
[14/15] [3/13] [51/8] [5/10] [3/3] [13/3] [4/4] [10/5]
14
[3/13] [5/10] [51/8] [10/5] [3/3] [13/3] [4/4]
[5/90] [3/13] [4/4] [10/5] [3/3] [13/3] [51/0]
Exemplo de Entrada:

8
I 1 1
I 2 2
I 3 3
I 4 4
I 5 5
I 6 6
I 7 7
I 8 8
P
R
R
P
I 9 9
I 10 10
P
A 3 13
A 10 0
A 2 10
A 9 2
P
Q
Exemplo de Saída:

[8/8] [7/7] [6/6] [4/4] [3/3] [2/2] [5/5] [1/1]
8
7
[6/6] [4/4] [5/5] [1/1] [3/3] [2/2]
[10/10] [9/9] [6/6] [4/4] [3/3] [2/2] [5/5] [1/1]
[3/13] [4/4] [2/10] [9/2] [10/0] [6/6] [5/5] [1/1]
*/

