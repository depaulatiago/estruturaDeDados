/*
Modifique o tipo do campo prêmio para inteiro, sendo o valor a ser recebido em moedas digitais pela atividade realizada pelo jogador. Implemente uma função que imprima a soma das recompensas das atividades com tempo menor que o informado e coloque essas atividade no início da fila.
Caso não exista nenhuma atividade menor que o valor informado, deve ser impresso o valor 0.
Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Fila com encadeamento - Lista de tarefas do jogador" como base.

Com essa finalidade, você deverá adicionar mais um comando, como segue:

p seguido de um inteiro: para contabilizar (e imprimir) o valor total do premio das atividades que foram realizadas dentro do valor determinado.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: Fila vazia!
i destruirArmazen 252 f 100
i salvarDonzela 888 e 300
i montarObservatorioMonteM2 582 d 400
i eliminarChefao 12585 a 2000
i eliminarBando 25354 a 30000
p 500
1722
r
Nome: destruirArmazen Premio: 252 Tipo: f tempo: 100
e
Nome: salvarDonzela Premio: 888 Tipo: e tempo: 300
f
Nome: salvarDonzela Premio: 888 Tipo: e tempo: 300
Nome: montarObservatorioMonteM2 Premio: 582 Tipo: d tempo: 400
Nome: eliminarChefao Premio: 12585 Tipo: a tempo: 2000
Nome: eliminarBando Premio: 25354 Tipo: a tempo: 30000
*/

#include <iostream>
using namespace std;

class noh
{
    friend class fila;

private:
    string nNome;
    int nPremio;
    char nTipo;
    int nTempo;
    noh *nProximo;

public:
    noh(string nome, int premio, char tipo, int tempo);
};

noh::noh(string nome, int premio, char tipo, int tempo)
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
    void enfileira(string nome, int premio, char tipo, int tempo);
    void desenfileira();
    void limpa();
    void espiar();
    int contabilizarPontos(int margem);
    bool vazia();
    int getPremio();
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

void fila::enfileira(string nome, int premio, char tipo, int tempo)
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

int fila::contabilizarPontos(int margem)
{
    int pontos = 0;
    noh *nAux = nInicio;
    while (nAux != NULL)
    {
        if (nAux->nTempo < margem)
        {
            pontos += nAux->nPremio;
        }
        nAux = nAux->nProximo;
    }
    return pontos;
}

bool fila::vazia()
{
    return (nInicio == NULL);
}

int fila::getPremio()
{
    return nInicio->nPremio;
}
int main()
{
    fila f;
    char opcao;
    string nome;
    int premio;
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
        case 'p':
            int margem;
            cin >> margem;
            cout << f.contabilizarPontos(margem) << endl;
            break;
        }
    } while (opcao != 'f');
    return 0;
}
