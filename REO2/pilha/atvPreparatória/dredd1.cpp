/*
Implemente uma função que realize a remoção dos jogos com valores inferiores a um valor informado, denominada remoção especial. Você poderá utilizar somente como estrutura auxiliar outra pilha. Os demais valores da pilha devem permanecer na posição original. Os valores removidos devem ser impressos no momento da remoção.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Pilha com encadeamento - Inventário de itens de jogo" como base.

Entradas:

Com essa finalidade, você deverá adicionar mais um comando, como segue:

x: seguido de um inteiro: para remover (e imprimir) todos os elementos com valor inferiores ao informado
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção especial. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: pilha vazia!
i um a 1
i dois b 2
i dez j 10
i quatro d 4
i sete g 7
i oito h 8
r
Nome: oito Tipo: h Valor: 8
e
Nome: sete Tipo: g Valor: 7
x 4
Nome: dois Tipo: b Valor: 2
Nome: um Tipo: a Valor: 1
f
Nome: sete Tipo: g Valor: 7
Nome: quatro Tipo: d Valor: 4
Nome: dez Tipo: j Valor: 10

*/

/*
Questão 1: Pilha com encadeamento - Inventário de itens de jogo
Implemente uma estrutura de dados pilha, utilizando encadeamento de nós, para implementar um inventário de itens em um jogo digital. A estrutura deve possibilitar, pelo menos, as seguintes ações: empilhamento e desempilhamento de itens, verificação do item no topo da pilha e limpeza do inventário (remoção de todos os elementos da pilha). O desempilhamento deve escrever mensagem de erro na saída ("
Erro: pilha vazia!
"), quando a pilha já estiver vazia. Os itens do inventários possuem os seguintes atributos: nome (uma string sem espaços), tipo (um único caracter) e valor (um inteiro).
Entradas:
O programa deve aceitar os seguintes comandos:
i: seguido de uma string, um caracter e um inteiro: para inserir um item no inventário
r: para retirar um item do inventário
l: para limpar (remover todos) os itens do inventário
e: para espiar o topo do inventário (escreve o topo sem removê-lo)
f: para finalizar a execução do programa
Saídas:
Todas as saídas de comandos já estão implementadas na função principal desse
código exemplo fornecido
. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.
Exemplo de Entrada e Saída juntas:
r
Erro: pilha vazia!
i um a 1
i dois b 2
i quatro d 4
i sete g 7
i oito h 8
r
Nome: oito Tipo: h Valor: 8
e
Nome: sete Tipo: g Valor: 7
r
Nome: sete Tipo: g Valor: 7
f
Nome: quatro Tipo: d Valor: 4
Nome: dois Tipo: b Valor: 2
Nome: um Tipo: a Valor: 1
*/

