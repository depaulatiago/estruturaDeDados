/*
Implemente uma estrutura de dados fila, utilizando encadeamento de nós, para implementar uma lista de tarefas do jogador, usando como base o código fornecido. A estrutura deve possibilitar, pelo menos, as seguintes ações: enfileiramento e desenfileiramento de itens, verificação do item no frente da fila e limpeza da lista (remoção de todos os elementos da fila). O desenfileiramento deve escrever mensagem de erro na saída ("Erro: fila vazia!"), quando a fila já estiver vazia. Os itens da lista possuem os seguintes atributos: nome da tarefa (uma string sem espaços), prêmio (uma string sem espaços), tipo (um único caracter) e tempo para realização (um inteiro).

Entradas:

O programa deve aceitar os seguintes comandos:

i seguido de duas string, um caracter e um inteiro: para inserir um item na lista de tarefas
r: para retirar um item da lista de tarefas
l: para limpar (remover todos) os itens da lista de tarefas
e: para espiar a frente da lista de tarefas (escreve o topo sem removê-lo)
f: para finalizar a execução do programa
Saídas:

Todas as saídas de comandos já estão implementadas na função principal desse código exemplo fornecido. Ao terminar a execução do programa, todos os itens da fila são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: Fila vazia!
i destruirArmazen jaqueta f 100
i salvarDonzela hb20 e 300
i montarObservatorioMonteM2 binoculo d 400
i eliminarChefao milDolares a 2000
i eliminarBando dezmilDolares a 30000
r
Nome: destruirArmazen Premio: jaqueta Tipo: f tempo: 100
e
Nome: salvarDonzela Premio: hb20 Tipo: e tempo: 300
f
Nome: salvarDonzela Premio: hb20 Tipo: e tempo: 300
Nome: montarObservatorioMonteM2 Premio: binoculo Tipo: d tempo: 400
Nome: eliminarChefao Premio: milDolares Tipo: a tempo: 2000
Nome: eliminarBando Premio: dezmilDolares Tipo: a tempo: 30000

*/

#include <iostream>
using namespace std;

class noh
{
    friend class fila;

private:
    string nNome;
    string nPremio;
    char nTipo;
    int nTempo;
    noh *nProximo;

public:
    noh(string nome; string premio; char tipo; int tempo);
};

noh::noh(string nome; string premio; char tipo; int tempo)
{
    nnome = nome;
    npremio = premio;
    ntipo = tipo;
    ntempo = tempo;
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
    void enfileira(string nome, string premio, char tipo, int tempo);
    int desenfileira();
    void limpaFila();
    bool vazia();
    void espiar();
};

fila::fila()
{
    noh* mInicio = NULL;
    noh* mFim = NULL;
    int mTamanho = 0;
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

void fila::enfileira(string nome, string premio, char tipo, int tempo)
{
    noh *novo = new noh(nome, premio, tipo, tempo);
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
    if (vazia())
    {
        cout << "Erro: fila vazia!" << endl;
    }
    else
    {
        noh *temp = mInicio;
        int valor = mInicio->nValor;
        mInicio = mInicio->nProximo;
        delete temp;
        mTamanho--;
        return valor;
    }
}

void espiar()
{
    cout << "Nome: " << mInicio->nNome << " Premio: " << mInicio->nPremio << " Tipo: " << mInicio->nTipo << " tempo: " << mInicio->nTempo << endl;
}

int main()
{
    fila f1;

    char comando;

    while (comando != f)
    {
        cin >> comando;
        if (comando == i)
        {
            int valor;
            string nome;
            string premio;
            char tipo;
            int tempo;
            cin >> valor >> nome >> premio >> tipo >> tempo;
            f1.enfileira(valor, nome, premio, tipo, tempo);
        }
        else if (comando == r)
        {
            cout << f1.desenfileira() << endl;
        }
        else if (comando == l)
        {
            f1.limpaFila();
        }
        else if (comando == e)
        {
            cout << f1.espiar() << endl;
        }
    }

    return 0;
}