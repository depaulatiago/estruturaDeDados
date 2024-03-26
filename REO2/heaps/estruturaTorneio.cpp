#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class torneio
{
private:
    dado *heap;
    int capacidade;
    int tamanho;
    int inicioDados;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void arruma(); // heapify()
    void copiaMaior(int i);
    void copiaSubindo(int i);

public:
    torneio(dado vet[], int tam);
    torneio(int numFolhas);
    ~torneio();
    void insere(dado d);
    void imprime();
};

torneio::torneio(dado vet[], int tam)
{
    capacidade = 1;
    while (capacidade < tam)
    {
        capacidade *= 2;
    }

    capacidade = capacidade - 1 + tam;

    heap = new dado[capacidade];
    inicioDados = capacidade - tam;
    cout << "inicioDados: " << inicioDados << endl;
    cout << "capacidade: " << capacidade << endl;

    memcpy(&heap[inicioDados], vet, tam * sizeof(dado));

    tamanho = tam;
    arruma();
}

torneio::torneio(int numFolhas)
{
    capacidade = 1;
    while (capacidade < numFolhas)
    {
        capacidade *= 2;
    }

    capacidade = capacidade - 1 + numFolhas;
    heap = new dado[capacidade];
    inicioDados = capacidade - numFolhas;

    cout << "inicioDados: " << inicioDados << endl;
    cout << "capacidade: " << capacidade << endl;

    for (int i = 0; i < numFolhas; i++)
    {
        heap[i] = INVALIDO;
    }
}

torneio::~torneio()
{
    delete[] heap;
}

int torneio::pai(int i)
{
    return (i - 1) / 2;
}

int torneio::esquerdo(int i)
{
    return 2 * i + 1;
}

int torneio::direito(int i)
{
    return 2 * i + 2;
}

void torneio::copiaMaior(int i)
{
    int esq = esquerdo(i);
    int dir = direito(i);
    cout << " i: " << i << " e: " << esq << " d:" << dir << endl;
    int maior = INVALIDO;
    if (esq < capacidade)
    {
        if ((dir < capacidade) and (heap[dir] > heap[esq]))
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
        heap[i] = INVALIDO;
    }
}

void torneio::copiaSubindo(int i)
{
    int p = pai(i);
    if (p >= 0)
    {
        if (heap[i] > heap[p])
        {
            heap[p] = heap[i];
            copiaSubindo(p);
        }
    }
}

void torneio::insere(dado d)
{
    if (tamanho == capacidade)
    {
        cout << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    heap[inicioDados + tamanho] = d;
    copiaSubindo(inicioDados + tamanho);
    tamanho++;
}

void torneio::imprime()
{
    for (int i = 0; i < capacidade; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void torneio::arruma()
{
    cout << "arruma: " << inicioDados - 1 << endl;
    for (int i = inicioDados - 1; i >= 0; i--)
    {
        copiaMaior(i);
    }
}

int main()
{
    int tam = 9;
    dado vet1[] = {50, 2, 90, 20, 230, 43, 8, 34, 66};

    torneio *h = new torneio(vet1, tam);
    h->imprime();
    delete h;

    tam = 13;
    dado vet2[] = {50, 2, 90, 20, 230, 43, 8, 34, 66, 100, 110, 3, 13};

    h = new torneio(vet2, tam);
    h->imprime();
    delete h;

    tam = 9;
    h = new torneio(tam);
    for (int i = 0; i < tam; i++)
    {
        h->insere(vet1[i]);
        h->imprime();
    }
    delete h;

    return 0;
}
