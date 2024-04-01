/*
Um torneio é uma árvore estritamente binária na qual cada nó não folha contém uma cópia do maior elemento entre seus dois filhos. O conteúdo das folhas de um torneio determina o conteúdo de todos os seus nós. Um torneio com n folhas representa um conjunto de n elementos.

Implemente um torneio utilizando uma estratégia semelhante a um Heap. Entretanto, a cada etapa, o elemento vencedor irá para a próxima etapa com o seu valor reduzido do valor do oponente. Neste caso, a estrutura de dados utilizada para representar um elemento deve possuir um valor base, que é o valor inicial e, caso ele vença o torneio, o valor que será utilizado é um valor relativo que será utilizado para contabilizar a progressão. Caso exista um empate, o elemento com maior valor base avança. O vencedor do torneio deverá ter seu valor base impresso.

Note que normalmente um torneio é uma árvore estritamente binária, cheia. Como, neste problema, temos que o tamanho da entrada pode não ser uma potência de 2, será necessário fazer ajustes para trabalhar com o que costumamos chamar de torneio incompleto. Uma das abordagens possíveis é apresentada nos slides e vídeo do assunto, verifique.

Faça um programa que funcione como um torneio.

A entrada deve conter o número de participantes seguido dos participantes. A saída apresenta o valor base do participante campeão do torneio.
Entradas:

Quantidade de participantes
Identificação dos participantes
Saídas:

Valor base do campeão do torneio
Exemplo de Entrada:

8
2 7 4 1 3 9 6 8
Exemplo de Saída:

9
Exemplo de Entrada:

13
11 5 3 4 2 15 7 9 10 8 12 6 13
Exemplo de Saída:

13
*/

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef int dado;

class torneio
{
private:
    int *heap;
    int tamanho;
    int capacidade;
    int inicioDados;
    inline int pai(int filho);
    inline int esquerda(int getPai);
    inline int direita(int getPai);
    void arruma();
    void compete(int i);

public:
    torneio(int vet[], int tam);
    ~torneio();
    void verBaseMaior();
};

// Construtor da classe
torneio::torneio(int vet[], int tam)
{
    capacidade = 1;
    while (capacidade < tam)
    {
        capacidade *= 2;
    }

    capacidade = capacidade - 1 + tam;

    heap = new dado[capacidade];
    inicioDados = capacidade - tam;

    memcpy(&heap[inicioDados], vet, tam * sizeof(dado));

    tamanho = tam;
    arruma();
}

// Destrutor da classe
torneio::~torneio()
{
    delete[] heap;
}

// Retorno a posição do nó pai de um determinado elemento
int torneio::pai(int filho)
{
    return (filho - 1) / 2;
}

// Retorna o filho à esquerda de um determinado nó
int torneio::esquerda(int pai)
{
    return 2 * pai + 1;
}

// Retorna o filho à direita do nó pai
int torneio::direita(int pai)
{
    return 2 * pai + 2;
}

// Faz a competição por cada posição vencedora no vetor e imprime o vencedor
void torneio::arruma()
{
    for (int i = inicioDados - 1; i >= 0; i--)
    {
        compete(i);
    }
}

// Faz a competição entre os elementos
void torneio::compete(int i)
{
    int esq = esquerda(i);
    int dir = direita(i);
    int maior = -1;

    if (esq < capacidade)
    {
        if ((dir < capacidade) && (heap[dir] > heap[esq]))
        {
            maior = dir;
        }
        else
        {
            maior = esq;
        }
        heap[i] = heap[maior];
    }
    else
    {
        heap[i] = -1;
    }
}

void torneio::verBaseMaior()
{
    cout << heap[0];
}

int main()
{
    int tam;
    cin >> tam;
    

    int vet[tam];
    for (int i = 0; i < tam; i++)
    {
        cin >> vet[i];
    }

    torneio participantes(vet, tam);

    participantes.verBaseMaior();

    return 0;
}