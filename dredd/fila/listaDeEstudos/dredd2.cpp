/*
Filas podem ser implementadas com armazenamento de dados em vetor, se a capacidade fixa não for um problema. Nesse caso, é importante controlar os índices para "dar a volta" no vetor sempre que for necessário. Uma fila assim pode ser chamada de fila circular.

Faça a implementação de uma fila circular fazendo com que a inserção (método Enfileirar) sempre use o início do vetor (posição zero) quando a fila estiver vazia.

Entradas:

Inicialmente, o programa lê um número inteiro que é capacidade da fila a ser criada.

Depois, o programa lê códigos de comandos a executar. Sempre um caractere identificando o comando seguido dos parâmetros necessários para executar o comando, se houverem. Os códigos de comandos são:

t - para terminar a execução do programa
e - para enfileirar um valor - seguido do valor (número inteiro)
d - para desenfileirar um valor
i - para escrever as informações da fila (atributos e conteúdo)
Saídas:

Os comandos d e i são os únicos que produzem saída de dados. Cada um pode ser observado no exemplo.

Exemplo de Entrada e Saída juntos:

3
e 1
e 2
e 3
i
tamanho=3 capacidade=3 inicio=0 fim=2
1 2 3 
d
1
e 4
i
tamanho=3 capacidade=3 inicio=1 fim=0
2 3 4
d
2
d
3
i
tamanho=1 capacidade=3 inicio=0 fim=0
4
t
*/