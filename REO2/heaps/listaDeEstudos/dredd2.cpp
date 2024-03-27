/*
O professor Bruno, com o intuito de motivar ainda mais os alunos a realizarem as atividades propostas para a sua disciplina, resolveu presentear o aluno que mais teve boas notas em suas atividades. Para isso, você deverá fazer um programa que faça esta classificação, com o intuito de automatizar o processo e aplicar os conceitos das estruturas vistas em Estruturas de Dados.

Os dados são classificados pelas informações básicas do aluno (matricula e nome) e uma lista de atividades realizadas. Para cada atividade, existe sua nota e também a quantidade de tentativas que o aluno realizou.

Observações: Para facilitar, a classificação deverá ser feita utilizando a média aritmética simples das notas dos alunos nas atividades (a quantidade de atividades informada será fixa para todos os alunos). O critério de desempate deve ser tomado por: 1) quantidade de tentativas e 2) ordem alfabética.

A resolução deste problema deve ser feita utilizando a estrutura de dados Heap genérica. Ou seja, a implementação dos critérios de desempate não deverá ser realizada dentro de sua estrutura, e sim no TAD especifico para o aluno. Você pode utilizar o código fornecido para agilizar o processo de implementação.

Entradas:

Quantidade de alunos que serão informados.
Número de atividades que será informado de cada aluno.
Matricula (número natural) e nome (texto sem espaços) de cada aluno, seguido das atividades do mesmo (nota e tentativas)
Saídas:

Matrícula e nome do aluno destaque no formato: [Matricula] Nome.
Exemplo de Entrada:

2
3
2015342 Marcos
100 1
30 4
80 2
2014234 Jose
100 1
100 3
100 2
Exemplo de Saída:

[2014234] Jose
Exemplo de Entrada:

2
3
2017232 Antonio
100 1
100 4
100 1
2017334 Leonardo
100 3
100 1
100 2
Exemplo de Saída:

[2017232] Antonio
Exemplo de Entrada:

3
1
2017211 Bruno
100 1
2017212 Matheus
100 2
2018001 Martha
100 3
Exemplo de Saída:

[2017211] Bruno
*/

