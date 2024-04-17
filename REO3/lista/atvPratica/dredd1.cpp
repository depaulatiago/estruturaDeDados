/*
Implemente uma função que realize a contabilidade dos elementos de uma lista simplesmente encadeada. Para esta atividade você não poderá utilizar a variável tamanho, ou qualquer outra que contabilize o número de elementos na lista, na sua estrutura. Ou seja, a verificação do tamanho deverá ser feita contando os elementos da lista. Caso a lista não possua elementos imprima 0.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" como base.

Com essa finalidade, você deverá adicionar mais um comando, como segue:

t : imprime a quantidade de elementos existentes na lista.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a calcular o tamanho da lista. Ao terminar a execução do programa, todos os itens da listas são escritos.

Exemplo de Entrada e Saída juntas:

r
Remoção em lista vazia!
a
Remoção em lista vazia!
p
Lista vazia!
s Thundercats
Lista vazia!
i Vingadores Stark Ruby 3
h LigaDaJustica Batman C++ 4
m 1 MuppetBabies Kermit Phyton 9
t
3
p
(Vingadores, Stark, Ruby, 3)
(MuppetBabies, Kermit, Phyton, 9)
(LigaDaJustica, Batman, C++, 4)
s Thundercats
Nao encontrado
r
p
(MuppetBabies, Kermit, Phyton, 9)
(LigaDaJustica, Batman, C++, 4)
a
p
(MuppetBabies, Kermit, Phyton, 9)
t
1
f
*/
#include <iostream>
#include <string>
using namespace std;

class noh
{
    friend class lista;
private:
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
    noh *proximo;

public:
    noh(string nomeEquipe, string lider, string linguagem, int qtdMembros);
};

noh::noh(string nomeEquipe, string lider, string linguagem, int qtdMembros)
{
    this->nomeEquipe = nomeEquipe;
    this->lider = lider;
    this->linguagem = linguagem;
    this->qtdMembros = qtdMembros;
    this->proximo = NULL;
}


class lista
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;

public:
    lista();
    ~lista();
    void insereInicio(string nomeEquipe, string lider, string linguagem, int qtdMembros);
    void insereFim(string nomeEquipe, string lider, string linguagem, int qtdMembros);
    void insereNaPosicao(string nomeEquipe, string lider, string linguagem, int qtdMembros, int posicao);
    void removeInicio();
    void removeFim();
    void imprime();
    void busca(string nomeEquipe);
    int getTamanho();
};

lista::lista()
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::~lista()
{
    noh *iter = primeiro;
    noh *proximo = NULL;
    while (iter != NULL)
    {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

void lista::insereInicio(string nomeEquipe, string lider, string linguagem, int qtdMembros)
{
    noh *novo = new noh(nomeEquipe, lider, linguagem, qtdMembros);
    novo->proximo = primeiro;
    primeiro = novo;
    if (tamanho == 0)
    {
        ultimo = novo;
    }
    ++tamanho;
}

void lista::insereFim(string nomeEquipe, string lider, string linguagem, int qtdMembros)
{
    noh *novo = new noh(nomeEquipe, lider, linguagem, qtdMembros);
    novo->proximo = NULL;
    if (tamanho == 0)
    {
        primeiro = novo;
    }
    else
    {
        ultimo->proximo = novo;
    }
    ultimo = novo;
    ++tamanho;
}

void lista::insereNaPosicao(string nomeEquipe, string lider, string linguagem, int qtdMembros, int posicao)
{
    if (posicao < 0 or posicao > tamanho)
    {
        cout << "Posição Inexistente!" << endl;
    }
    else
    {
        if (posicao == 0)
        {
            insereInicio(nomeEquipe, lider, linguagem, qtdMembros);
        }
        else if (posicao == tamanho)
        {
            insereFim(nomeEquipe, lider, linguagem, qtdMembros);
        }
        else
        {
            noh *novo = new noh(nomeEquipe, lider, linguagem, qtdMembros);
            noh *aux = primeiro;
            for (int i = 0; i < posicao - 1; ++i)
            {
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            ++tamanho;
        }
    }
}

void lista::removeInicio()
{
    if (tamanho == 0)
    {
        cout << "Remocao em lista vazia!" << endl;
    }
    else
    {
        noh *removido = primeiro;
        primeiro = primeiro->proximo;
        delete removido;
        --tamanho;
    }
}

void lista::removeFim()
{
    if (tamanho == 0)
    {
        cout << "Remocao em lista vazia!" << endl;
    }
    else
    {
        if (tamanho == 1)
        {
            delete primeiro;
            primeiro = NULL;
            ultimo = NULL;
        }
        else
        {
            noh *iter = primeiro;
            while (iter->proximo != ultimo)
            {
                iter = iter->proximo;
            }
            delete ultimo;
            ultimo = iter;
            ultimo->proximo = NULL;
        }
        --tamanho;
    }
}

void lista::imprime()
{
    if (tamanho == 0)
    {
        cout << "Lista vazia!" << endl;
    }
    else
    {
        noh *iter = primeiro;
        while (iter != NULL)
        {
            cout << "(" << iter->nomeEquipe << ", " << iter->lider << ", " << iter->linguagem << ", " << iter->qtdMembros << ")" << endl;
            iter = iter->proximo;
        }
    }
}

void lista::busca(string nomeEquipe)
{
    noh *iter = primeiro;
    while (iter != NULL)
    {
        if (iter->nomeEquipe == nomeEquipe)
        {
            cout << "(" << iter->nomeEquipe << ", " << iter->lider << ", " << iter->linguagem << ", " << iter->qtdMembros << ")" << endl;
            return;
        }
        iter = iter->proximo;
    }
    cout << "Nao encontrado" << endl;
}

int lista::getTamanho()
{
    int cont = 0;
    noh *iter = primeiro;
    while (iter != NULL)
    {
        cont++;
        iter = iter->proximo;
    }
    return cont;
}
int main()
{
    lista maratona;
    char comando;
    string nomeEquipe, lider, linguagem;
    int qtdMembros, posicao;
    while (cin >> comando && comando != 'f')
    {
        switch (comando)
        {
        case 'i':
            cin >> nomeEquipe >> lider >> linguagem >> qtdMembros;
            maratona.insereInicio(nomeEquipe, lider, linguagem, qtdMembros);
            break;
        case 'h':
            cin >> nomeEquipe >> lider >> linguagem >> qtdMembros;
            maratona.insereFim(nomeEquipe, lider, linguagem, qtdMembros);
            break;
        case 'm':
            cin >> posicao >> nomeEquipe >> lider >> linguagem >> qtdMembros;
            maratona.insereNaPosicao(nomeEquipe, lider, linguagem, qtdMembros, posicao);
            break;
        case 'r':
            maratona.removeInicio();
            break;
        case 'a':
            maratona.removeFim();
            break;
        case 'p':
            maratona.imprime();
            break;
        case 's':
            cin >> nomeEquipe;
            maratona.busca(nomeEquipe);
            break;
        case 't':
            cout << maratona.getTamanho() << endl;
            break;
        }
    }
    return 0;
}
