/*
O jogador resolveu realizar o maior número de tarefas da lista abaixo de um determinado tempo que é informado (valor inteiro positivo). Para isso ele resolveu fazer primeiro as tarefas que tem menor custo até atingir o valor especificado (mas este não incluso). Implemente uma função que imprima o maior número de tarefas da fila em que a soma das tarefas seja menor que o valor informado. Além disso, elimine as atividades da fila.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Fila com encadeamento - Lista de tarefas do jogador" como base.

Com essa finalidade, você deverá adicionar mais um comando, como segue:

t seguido de um inteiro: para contabilizar (e imprimir) as atividades que foram realizadas dentro do valor determinado.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: Fila vazia!
i destruirArmazen jaqueta f 100
i salvarDonzela hb20 e 300
i montarObservatorioMonteM2 binoculo d 400
i eliminarChefao milDolares a 2000
i eliminarBando dezmilDolares a 30000
t 800
Nome: destruirArmazen Premio: jaqueta Tipo: f tempo: 100
Nome: salvarDonzela Premio: hb20 Tipo: e tempo: 300
r
Nome: montarObservatorioMonteM2 Premio: binoculo Tipo: d tempo: 400
e
Nome: eliminarChefao Premio: milDolares Tipo: a tempo: 2000
f
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
    noh(string nome, string premio, char tipo, int tempo);
};

noh::noh(string nome, string premio, char tipo, int tempo)
{
    nNome = nome;
    nPremio = premio;
    nTipo = tipo;
    nTempo = tempo;
    nProximo = NULL;
}

class fila
{
private:
    noh *nInicio;
    noh *nFim;

public:
    fila();
    ~fila();
    void enfileira(string nome, string premio, char tipo, int tempo);
    void desenfileira();
    void limpa();
    void espiar();
    int tempoTipo(char tipo);
    void contabiliza(int tempoMax);
};

fila::fila()
{
    nInicio = NULL;
    nFim = NULL;
}

fila::~fila()
{
    limpa();
}

void fila::enfileira(string nome, string premio, char tipo, int tempo)
{
    noh *nNovo = new noh(nome, premio, tipo, tempo);
    if (nInicio == NULL)
    {
        nInicio = nNovo;
        nFim = nNovo;
    }
    else
    {
        nFim->nProximo = nNovo;
        nFim = nNovo;
    }
}

void fila::desenfileira()
{
    if (nInicio == NULL)
    {
        cout << "Erro: Fila vazia!" << endl;
    }
    else
    {
        noh *nAux = nInicio;
        nInicio = nInicio->nProximo;
        cout << "Nome: " << nAux->nNome << " Premio: " << nAux->nPremio << " Tipo: " << nAux->nTipo << " tempo: " << nAux->nTempo << endl;
        delete nAux;
    }
}

void fila::limpa()
{
    while (nInicio != NULL)
    {
        desenfileira();
    }
}

void fila::espiar()
{
    if (nInicio == NULL)
    {
        cout << "Erro: Fila vazia!" << endl;
    }
    else
    {
        cout << "Nome: " << nInicio->nNome << " Premio: " << nInicio->nPremio << " Tipo: " << nInicio->nTipo << " tempo: " << nInicio->nTempo << endl;
    }
}

int fila::tempoTipo(char tipo)
{
    int tempo = 0;
    noh *nAux = nInicio;
    while (nAux != NULL)
    {
        if (nAux->nTipo == tipo)
        {
            tempo += nAux->nTempo;
        }
        nAux = nAux->nProximo;
    }
    return tempo;
}

void fila::contabiliza(int tempoMax)
{
    while (nInicio != NULL && nInicio->nTempo < tempoMax)
    {
        desenfileira();
    }
}
int main()
{
    fila f;
    char opcao;
    string nome, premio;
    char tipo;
    int tempo;
    do
    {
        cin >> opcao;
        switch (opcao)
        {
        case 'i':
            cin >> nome >> premio >> tipo >> tempo;
            f.enfileira(nome, premio, tipo, tempo);
            break;
        case 'r':
            f.desenfileira();
            break;
        case 'l':
            f.limpa();
            break;
        case 'e':
            f.espiar();
            break;
        case 'a':
            cin >> tipo;
            cout << f.tempoTipo(tipo) << endl;
            break;
        case 't':
            int tempoMax;
            cin >> tempoMax;
            f.contabiliza(tempoMax);
            break;
        }
    } while (opcao != 'f');
    return 0;
}

