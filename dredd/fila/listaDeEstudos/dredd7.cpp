/*
Implemente um método para mesclar duas filas encadeadas de números inteiros previamente ordenadas e retornar uma nova fila totalmente ordenada. Não é necessário verificar se as filas estavam ordenadas, simplesmente suponha que estavam.

O programa tem duas filas (A e B) e pode inserir elementos em qualquer uma, escrever os dados de qualquer uma ou mesclar A com B numa fila temporária.

Entradas:

Uma sequência de comandos para o programa executar, a saber:

i: seguido de um identificador de fila (a ou b), seguida de um número inteiro, insere a palavra na fila
e: seguido de um identificador de fila (a ou b), escreve o conteúdo da fila
m: mescla a fila a com a fila b numa fila temporária e escreve o seu conteúdo
t: termina a execução do programa
Saídas:

O comando e escreve o conteúdo de uma das listas sem precisar desenfileirar. O comando m escreve o conteúdo da fila temporária sem precisar desenfileirar.

Exemplo de Entrada:

i a 1
i a 3
i a 5
i b 2
i b 4
i b 6
e a
e b
m
t
Exemplo de Saída:

1 3 5
2 4 6
1 2 3 4 5 6
*/