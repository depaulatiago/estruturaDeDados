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

// Estrutura para armazenar informações da equipe
struct equipe
{
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

// Classe para representar um nó da lista encadeada
class noh
{
    friend class lista;

private:
    equipe elenco; // Dados da equipe
    noh *proximo;  // Ponteiro para o próximo nó na lista

public:
    noh(equipe d); // Construtor
};

// Construtor do nó
noh::noh(equipe d)
{
    elenco = d;
    proximo = nullptr;
}

// Classe para representar a lista encadeada
class lista
{
private:
    noh *primeiro; // Ponteiro para o primeiro nó da lista
    noh *ultimo;   // Ponteiro para o último nó da lista
    int tamanho;   // Tamanho da lista

    // Função privada para remover todos os nós da lista
    void removeTodos();

public:
    // Construtores e destrutor
    lista();                      // Construtor padrão
    lista(const lista &umaLista); // Construtor de cópia
    ~lista();                     // Destrutor

    // Sobrecarga do operador de atribuição
    lista &operator=(const lista &umaLista);

    // Métodos de inserção
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);

    // Método de busca
    int procura(string valor);

    // Métodos de impressão
    void imprime();
    void imprimeReverso(); // Método não implementado na classe atual

    // Métodos de remoção
    void removeNoFim();
    void removeNoInicio();

    // Outros métodos
    bool vazia();
    int Tamanho();
};

// Método para retornar o tamanho da lista
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

// Construtor padrão da lista
lista::lista()
{
    tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

// Construtor de cópia da lista
lista::lista(const lista &umaLista)
{
    tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;

    noh *aux = umaLista.primeiro;

    // Copia os elementos da lista umaLista para a nova lista
    while (aux != nullptr)
    {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

// Destrutor da lista (chama função privada para remover todos os nós)
lista::~lista()
{
    removeTodos();
}

// Função privada para remover todos os nós da lista
void lista::removeTodos()
{
    noh *aux = primeiro;
    noh *temp;

    // Percorre a lista removendo cada nó
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

// Sobrecarga do operador de atribuição
lista &lista::operator=(const lista &umaLista)
{
    // Limpa a lista atual
    removeTodos();

    // Copia os elementos da lista umaLista para a lista atual
    noh *aux = umaLista.primeiro;

    while (aux != nullptr)
    {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

// Método para inserir no final da lista
void lista::insereNoFim(equipe elenco)
{
    noh *novo = new noh(elenco);

    // Se a lista está vazia, o novo nó é o primeiro e o último
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        // Insere o novo nó no final da lista
        ultimo->proximo = novo;
        ultimo = novo;
    }

    tamanho++;
}

// Método para inserir no início da lista
void lista::insereNoInicio(equipe elenco)
{
    noh *novo = new noh(elenco);

    // Se a lista está vazia, o novo nó é o primeiro e o último
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        // Insere o novo nó no início da lista
        novo->proximo = primeiro;
        primeiro = novo;
    }

    tamanho++;
}

// Método para inserir em uma posição específica da lista
void lista::insereNaPosicao(int posicao, equipe elenco)
{
    noh *novo = new noh(elenco);

    // Verifica se a posição é válida
    if ((posicao <= tamanho) && (posicao >= 0))
    {
        // Se a lista está vazia, insere o novo nó como primeiro e último
        if (vazia())
        {
            primeiro = novo;
            ultimo = novo;
        }
        else if (posicao == 0) // Insere no início da lista
        {
            insereNoInicio(elenco);
        }
        else if (posicao == tamanho) // Insere no fim da lista
        {
            insereNoFim(elenco);
        }
        else
        {
            // Insere na posição desejada
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

// Método para procurar a posição de um elemento na lista
int lista::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;
    int posAux = 0;

    // Percorre a lista procurando pelo valor
    while ((aux != nullptr) && (aux->elenco.nomeEquipe != valor))
    {
        posAux++;
        aux = aux->proximo;
    }

    // Retorna a posição do elemento, ou -1 se não encontrado
    if (aux == nullptr)
    {
        posAux = -1;
    }

    return posAux;
}

// Método para imprimir todos os elementos da lista
void lista::imprime()
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }

    noh *aux = primeiro;

    // Percorre a lista imprimindo os elementos
    while (aux != nullptr)
    {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", "
             << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

// Método para verificar se a lista está vazia
bool lista::vazia()
{
    return (tamanho == 0);
}

// Método para remover o último elemento da lista
void lista::removeNoFim()
{
    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;
    noh *anterior = nullptr;

    // Percorre a lista até o último nó
    while (aux->proximo != nullptr)
    {
        anterior = aux;
        aux = aux->proximo;
    }

    // Remove o último nó
    delete ultimo;
    anterior->proximo = nullptr;
    ultimo = anterior;

    tamanho--;

    // Caso a lista fique vazia, atualiza o primeiro
    if (tamanho == 0)
    {
        primeiro = nullptr;
    }
}

// Método para remover o primeiro elemento da lista
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

    // Caso a lista fique vazia, atualiza o último
    if (vazia())
    {
        ultimo = nullptr;
    }
}

// Função principal (main) para interagir com a lista
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
            cin >> comando; // Lê o comando

            switch (comando)
            {
            case 'i': // Inserir no início
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // Inserir no fim
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // Inserir na posição
                cin >> posicao >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // Procurar posição pelo nome da equipe
                cin >> nomeEquipe;
                if (minhaLista.procura(nomeEquipe) != -1)
                    cout << minhaLista.procura(nomeEquipe) << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 'r': // Remover do início
                minhaLista.removeNoInicio();
                break;
            case 'a': // Remover do fim
                minhaLista.removeNoFim();
                break;
            case 'p': // Imprimir lista
                minhaLista.imprime();
                break;
            case 't': // Imprimir tamanho da lista
                cout << minhaLista.Tamanho() << endl;
                break;
            case 'f': // Finalizar
                // Sai do laço
                break;
            default:
                cerr << "Comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // Repete até receber o comando 'f'

    return 0;
}
