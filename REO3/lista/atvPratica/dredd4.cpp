/*
Questão 4: Lista Simplesmente Encadeada - Equipes de Maratona - Remover no fim da lista
Implemente uma função que realize a remoção de um elemento no fim da lista. Para esta atividade você não poderá utilizar um ponteiro para o último elemento. Caso a lista não possua elementos imprima Lista vazia!.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" como base.

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
#include <cstdlib>

using namespace std;

struct equipe
{
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh
{
    friend class lista;

private:
    equipe elenco; // poderia ser outro tipo de variável
    noh *proximo;

public:
    // noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d)
{
    elenco = d;
    proximo = NULL;
}

// lista dinamicamente encadeada
class lista
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
                        // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh *umNoh);

public:
    // construtores e destrutor
    lista();
    lista(const lista &umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista &operator=(const lista &umaLista);
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
    int Tamanho();
};

int lista::Tamanho()
{
    if (vazia())
        return 0;

    noh *aux = primeiro;

    int tam = 0;

    while (aux != nullptr)
    {
        aux = aux->proximo;
        tam++;
    }
    return tam;
}
// constrói uma lista inicialmente vazia
lista::lista()
{
    tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

// construtor de cópia
lista::lista(const lista &umaLista)
{
    tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;

    noh *aux = umaLista.primeiro;

    while (aux != nullptr)
    {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista()
{
    removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos()
{

    noh *aux = primeiro;
    noh *temp;

    while (aux != nullptr)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

// sobrecarga do operador de atribuição
lista &lista::operator=(const lista &umaLista)
{
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh *aux = umaLista.primeiro;

    while (aux != NULL)
    {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

// insere no final da lista
void lista::insereNoFim(equipe elenco)
{

    noh *novo = new noh(elenco);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco)
{
    noh *novo = new noh(elenco);
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco)
{
    noh *novo = new noh(elenco);

    if ((posicao <= tamanho) && (posicao >= 0))
    {
        if (vazia())
        {
            primeiro = novo;
            ultimo = novo;
        }
        else if (posicao == 0)
        {
            insereNoInicio(elenco);
        }
        else if (posicao == tamanho)
        {
            insereNoFim(elenco);
        }
        else
        {
            noh *aux = primeiro;
            int posAux = 0;

            while (posAux < (posicao - 1))
            {
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    }
    else
    {
        cout << "Posição Inexistente!" << endl;
    }
}

// procura a posição de um determinado elemento
int lista::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }
    noh *aux = primeiro;
    int posAux = 0;

    while ((aux != nullptr) && (aux->elenco.nomeEquipe != valor))
    {
        posAux++;
        aux = aux->proximo;
    }

    if (aux == nullptr)
    {
        posAux = -1;
    }
    return posAux;
}

// método básico que percorre uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime()
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;

    while (aux != nullptr)
    {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

// verifica se a lista está vazia
inline bool lista::vazia()
{
    return (tamanho == 0);
}

void lista::removeNoFim()
{

    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;
    noh *anterior;

    while (aux->proximo != nullptr)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    delete ultimo;
    anterior->proximo = nullptr;
    ultimo = anterior;

    tamanho--;
    if (tamanho == 0)
    {
        primeiro = nullptr;
    }
}

void lista::removeNoInicio()
{
    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }
    noh *aux = primeiro;
    primeiro = primeiro->proximo;
    delete aux;

    tamanho--;
    if (vazia())
    {
        ultimo = nullptr;
    }
}

int main()
{
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // remover
                cin >> nomeEquipe;
                if (minhaLista.procura(nomeEquipe) != -1)
                    cout << minhaLista.procura(nomeEquipe) << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 'r': // remover
                minhaLista.removeNoInicio();
                break;
            case 'a': // remover
                minhaLista.removeNoFim();
                break;
            case 'p': // limpar tudo
                minhaLista.imprime();
                break;
            case 't':
                cout << minhaLista.Tamanho() << endl;
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}