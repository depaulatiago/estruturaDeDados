/*
Giovani decidiu ordenar sua grande coleção de cartas de "Yu-Gi-Oh!". Para isso pediu sua ajuda e lhe informou que queria um monte ordenado em ordem crescente pelo poder das cartas, e não teria cartas repetidas. Como tinha muitas, ele decidiu ordenar dois montes em ordem crescente (podendo conter cartas repetidas). Sua missão agora é ajudar Giovani a unir os dois montes retirando suas cartas repetidas. Utilizando-se da estrutura da dado fila, faça um programa que lê duas filas já em ordem crescente e cria uma terceira fila com os valores das duas primeiras em ordem crescente sem que haja repetição de elementos.

Não é permitido utilizar a STL ou similares para resolver o problema, bem como acessar os dados desrespeitando as propriedades da estrutura.

Entradas:

Quantidade de elementos da fila 1.
Elementos da fila 1 em ordem crescente.
Quantidade de elementos da fila 2.
Elementos da fila 2 em ordem crescente.
Saídas:

Elementos da fila de resultados.
Exemplo de Entrada:

7
1 3 5 7 10 10 11
6
2 4 6 8 10 12
Exemplo de Saída:

1 2 3 4 5 6 7 8 10 11 12
*/

#include <iostream>
using namespace std;

class noh
{
    friend class fila;

private:
    int nValor;
    noh *nProximo;

public:
    noh(int valor);
};

noh::noh(int valor)
{
    nValor = valor;
    nProximo = NULL;
}

class fila
{
private:
    noh *mInicio;
    noh *mFim;
    int mTamanho;

public:
    fila();
    ~fila();
    int tamanho();
    void enfileira(int valor);
    int desenfileira();
    void limpaFila();
    bool vazia();
    int inicio();
};

fila::fila()
{
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

fila::~fila()
{
    limpaFila();
}

void fila::limpaFila()
{
    while (!vazia())
    {
        desenfileira();
    };
}

int fila::tamanho()
{
    return mTamanho;
}

bool fila::vazia()
{
    return (mTamanho == 0);
}

void fila::enfileira(int valor)
{
    noh *novo = new noh(valor);
    if (mTamanho == 0)
    {
        mInicio = novo;
    }
    else
    {
        mFim->nProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int fila::desenfileira()
{
    int valor = mInicio->nValor;
    noh *temp = mInicio;
    mInicio = mInicio->nProximo;
    delete temp;
    mTamanho--;
    if (mTamanho == 0)
    {
        mFim = NULL;
    }
    return valor;
}

int fila::inicio()
{
    return mInicio->nValor;
}

int main()
{
    fila fila1, fila2, filaResultado;
    int tamanhoFila1, tamanhoFila2;

    cin >> tamanhoFila1;
    for (int i = 0; i < tamanhoFila1; i++)
    {
        int elemento;
        cin >> elemento;
        fila1.enfileira(elemento);
    }

    cin >> tamanhoFila2;
    for (int i = 0; i < tamanhoFila2; i++)
    {
        int elemento;
        cin >> elemento;
        fila2.enfileira(elemento);
    }

    while (!fila1.vazia() && !fila2.vazia())
    {
        if (fila1.inicio() < fila2.inicio())
        {
            filaResultado.enfileira(fila1.desenfileira());
        }
        else if (fila1.inicio() > fila2.inicio())
        {
            filaResultado.enfileira(fila2.desenfileira());
        }
        else
        {
            filaResultado.enfileira(fila1.desenfileira());
            fila2.desenfileira();
        }
    }

    while (!fila1.vazia())
    {
        filaResultado.enfileira(fila1.desenfileira());
    }

    while (!fila2.vazia())
    {
        filaResultado.enfileira(fila2.desenfileira());
    }

    while (!filaResultado.vazia())
    {
        cout << filaResultado.desenfileira() << " ";
    }

    return 0;
}