/*
Implemente um método para mesclar duas filas encadeadas de números inteiros previamente ordenadas
e retornar uma nova fila totalmente ordenada.
Não é necessário verificar se as filas estavam ordenadas, simplesmente suponha que estavam.

O programa tem duas filas (A e B) e pode inserir elementos em qualquer uma,
 escrever os dados de qualquer uma ou mesclar A com B numa fila temporária.

Entradas:

Uma sequência de comandos para o programa executar, a saber:

i: seguido de um identificador de fila (a ou b), seguida de um número inteiro, insere a palavra na fila
e: seguido de um identificador de fila (a ou b), escreve o conteúdo da fila
m: mescla a fila a com a fila b numa fila temporária e escreve o seu conteúdo
t: termina a execução do programa
Saídas:

O comando e escreve o conteúdo de uma das listas sem precisar desenfileirar.

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
    int tamanho(); // usa para dar somente positivos
    void enfileira(int valor);
    int desenfileira();
    void limpaFila();
    bool vazia();
    void imprime();
    int valor();
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

int fila::valor()
{
    return mInicio->nValor;
}

void fila::imprime()
{
    noh *aux = mInicio;
    while (aux != NULL)
    {
        cout << aux->nValor << " ";
        aux = aux->nProximo;
    }
    cout << endl;
}

int main()
{
    fila fa;
    fila fb;
    fila fc;

    char comando;

    while (comando != 't')
    {
        cin >> comando;
        if (comando == 'i')
        {
            char fila;
            int valor;
            cin >> fila >> valor;
            if (fila == 'a')
            {
                fa.enfileira(valor);
            }
            else
            {
                fb.enfileira(valor);
            }
        }

        if (comando == 'e')
        {
            char fila;
            cin >> fila;
            if (fila == 'a')
            {
                fa.imprime();
            }
            else
            {
                fb.imprime();
            }
        }

        if (comando == 'm')
        {
            while (!fa.vazia() and !fb.vazia())
            {
                if (fa.valor() < fb.valor())
                {
                    fc.enfileira(fa.desenfileira());
                }
                else
                {
                    fc.enfileira(fb.desenfileira());
                }
            }
            while (!fa.vazia())
            {
                fc.enfileira(fa.desenfileira());
            }
            while (!fb.vazia())
            {
                fc.enfileira(fb.desenfileira());
            }
            fc.imprime();
        }
    }

    return 0;
}