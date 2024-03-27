/*
Implemente uma classe MaxHeap que tem um construtor que recebe um vetor de elementos. Durante a criação do MaxHeap, alguns elementos deverão ser reposicionados para que passem a ter as propriedades de um max heap. O construtor (ou método usado no construtor) deverá escrever passo a passo como fica o armazenamento após a correção descendo de cada posição.

Note que não é para escrever os valores do heap após cada troca, os valores do heap devem ser escritos após todas as trocas (zero ou mais) realizadas para a correção de uma posição.

Implemente a função principal que cria um heap a partir do vetor.

Entradas:

A quantidade de elementos a serem lidos.
Os elementos (números inteiros) a serem armazenados no heap.
Saídas:

Para cada posição a ser corrigida:

A posição, seguida de dois pontos;
Todos os elementos armazenados após a reorganização iniciada na posição em questão.
Note a ausência de espaço antes do dois pontos e a presença do espaço depois, como em qualquer sinal de pontuação.

Exemplo de Entrada:

6
-3 -1 5 7 8 9
Exemplo de Saída:

2: -3 -1 9 7 8 5
1: -3 8 9 7 -1 5
0: 9 8 5 7 -1 -3
*/

#include <iostream>
#include <algorithm>
using namespace std;

typedef int dado;

class MaxHeap
{
    dado *heap;
    int capacidade;
    int tamanho;

public:
    MaxHeap(dado vet[], int tam)
    {
        heap = new dado[tam];
        capacidade = tam;
        tamanho = tam;
        copy(vet, vet + tam, heap);
        for (int i = tamanho - 1; i >= 0; i--)
        {
            corrigeDescendo(i);
        }
    }

    void corrigeDescendo(int pos)
    {
        int esq = 2 * pos + 1;
        int dir = 2 * pos + 2;
        int maior = pos;

        if (esq < tamanho && heap[esq] > heap[maior])
        {
            maior = esq;
        }

        if (dir < tamanho && heap[dir] > heap[maior])
        {
            maior = dir;
        }

        if (maior != pos)
        {
            swap(heap[pos], heap[maior]);
            cout << pos << ": ";
            for (int i = 0; i < tamanho; i++)
            {
                cout << heap[i] << " ";
            }
            cout << endl;
            corrigeDescendo(maior);
        }
    }
};

int main()
{
    int tam;
    cin >> tam;
    dado vet[tam];
    for (int i = 0; i < tam; i++)
    {
        cin >> vet[i];
    }
    new MaxHeap(vet, tam);
    return 0;
}