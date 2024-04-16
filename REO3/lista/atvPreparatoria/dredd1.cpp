/*
Crie um programa que seja capaz de armazenar em uma lista encadeada as equipes de uma maratona de programação. Para cada equipe deverá ser informado o seu nome, o nome do líder da equipe, a linguagem de programação que será utilizada e a quantidade de membros. Você poderá utilizar o código fornecido como base de implementação.

Os comandos que deverão ser utilizados para execução do programa são:

i: inserir uma nova equipe no inicio da lista. O formato de entrada é: NomeEquipe Lider Linguagem QtdMembros
h: inserir uma nova equipe no fim da lista. O formato de entrada é: NomeEquipe Lider Linguagem QtdMembros
m: inserir uma nova equipe na posição informada pelo usuário através de um número inteiro. Considere 0 como a posição inicial da lista. Caso não seja possível inserir na posição indicada imprima "Posição Inexistente!". O formato de entrada é: posiçãoASerInserida NomeEquipe Lider Linguagem QtdMembros
r: apagar uma determinada equipe do início da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
a: apagar uma determinada equipe do fim da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
p: imprimir lista de equipes cadastradas. Imprimir Lista vazia! quando não tiver elemento a ser impresso.
s: buscar por uma equipe a partir de seu nome. Imprimir Nao encontrado quando a busca não obtiver sucesso.
Nota: o formato de saída das equipes deve ser: (Nome, Lider, Linguagem, QtdMembros). Para mais instâncias de equipes (comando de impressão), cada uma delas devem ser separadas por quebras de linha.

Entradas:

Comandos detalhados no exercício
Saídas:

Impressões detalhadas no exercício
Exemplo de Entrada e Saída misturados:

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
f
*/
#include <iostream>
#include <string>
using namespace std;

struct noh
{
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
    noh *proximo;
};

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
    noh *novo = new noh;
    novo->nomeEquipe = nomeEquipe;
    novo->lider = lider;
    novo->linguagem = linguagem;
    novo->qtdMembros = qtdMembros;
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
    noh *novo = new noh;
    novo->nomeEquipe = nomeEquipe;
    novo->lider = lider;
    novo->linguagem = linguagem;
    novo->qtdMembros = qtdMembros;
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
            noh *novo = new noh;
            novo->nomeEquipe = nomeEquipe;
            novo->lider = lider;
            novo->linguagem = linguagem;
            novo->qtdMembros = qtdMembros;
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
        cout << "Remoção em lista vazia!" << endl;
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
        cout << "Remoção em lista vazia!" << endl;
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
        }
    }
    return 0;
}
