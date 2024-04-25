/*
Crie um programa que seja capaz de armazenar em uma lista duplamente encadeada as ações de usuários em um programa. Cada elemento da lista deve ter um identificador, o nome da ação, tempo para execução total e tempo já consumido de processamento. Você poderá utilizar o código fornecido como base de implementação.

Os comandos que deverão ser utilizados para execução do programa são:

i: inserir uma nova ação no inicio da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
h: inserir uma nova ação no final da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
m: inserir uma nova equipe na posição informada pelo inteiro. Considere 0 como no início e imprima "Posição Inexistente!" caso não seja possível inserir na posição indicada. O formato de entrada é: posiçãoASerInserida Identificador NomeAcao TempoExecução TempoConsumido
r: apagar uma determinada ação do início da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
a: apagar uma determinada ação do fim da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
p: imprimir lista de ações cadastradas em ordem de inserção e, em seguida, em ordem inversa. Imprimir Lista vazia! quando não tiver elemento a ser impresso.
s: buscar por uma ação a partir de seu nome. Imprimir Nao encontrado quando a busca não obtiver sucesso.
Nota: o formato de saída das ações deve ser: (Identificador, NomeAcao, TempoExecução, TempoConsumido). Para mais instâncias de ações (comando de impressão), separar cada uma delas por quebras de linha.

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
s empilharProcessos
Lista vazia!
i 1 limparCache 123 99
h 2 semaforoProc 32 11
m 1 3 paralelismoProc 65 23
p
(1, limparCache, 123, 99)
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO 
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
(1, limparCache, 123, 99)
s empilharProcessos
Nao encontrado
r
p
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO 
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
a
p
(3, paralelismoProc, 65, 23)
 IMPRIMINDO REVERSO 
(3, paralelismoProc, 65, 23)
f
*/

/*
NOTA DREDD UFLA: 100
Questão 2: Lista Duplamente Encadeada - Ações de usuários em um programa
Crie um programa que seja capaz de armazenar em uma lista duplamente encadeada as ações de usuários em um programa. Cada elemento da lista deve ter um identificador, o nome da ação, tempo para execução total e tempo já consumido de processamento. Você poderá utilizar o código fornecido como base de implementação.

Os comandos que deverão ser utilizados para execução do programa são:

i: inserir uma nova ação no inicio da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
h: inserir uma nova ação no final da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
m: inserir uma nova equipe na posição informada pelo inteiro. Considere 0 como no início e imprima "Posição Inexistente!" caso não seja possível inserir na posição indicada. O formato de entrada é: posiçãoASerInserida Identificador NomeAcao TempoExecução TempoConsumido
r: apagar uma determinada ação do início da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
a: apagar uma determinada ação do fim da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
p: imprimir lista de ações cadastradas em ordem de inserção e, em seguida, em ordem inversa. Imprimir Lista vazia! quando não tiver elemento a ser impresso.
s: buscar por uma ação a partir de seu nome. Imprimir Nao encontrado quando a busca não obtiver sucesso.
Nota: o formato de saída das ações deve ser: (Identificador, NomeAcao, TempoExecução, TempoConsumido). Para mais instâncias de ações (comando de impressão), separar cada uma delas por quebras de linha.

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
s empilharProcessos
Lista vazia!
i 1 limparCache 123 99
h 2 semaforoProc 32 11
m 1 3 paralelismoProc 65 23
p
(1, limparCache, 123, 99)
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
(1, limparCache, 123, 99)
s empilharProcessos
Nao encontrado
r
p
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
a
p
(3, paralelismoProc, 65, 23)
 IMPRIMINDO REVERSO
(3, paralelismoProc, 65, 23)
f
*/

/*
 * Classe listadup, uma lista dinamicamente duplamente encadeada
 *
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma
{
    int identificador;
    string nomeAcao;
    int tempoExecucao;
    int tempoConsumido;
};

ostream &operator<<(ostream &os, const acaoPrograma &a)
{
    os << "(" << a.identificador << ", " << a.nomeAcao << ", " << a.tempoExecucao << ", " << a.tempoConsumido << ")" << endl;
    return os;
}

class noh
{
    friend class listadup;

private:
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh *proximo;
    noh *anterior;

public:
    // noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d)
{
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

// lista dinamicamente encadeada
class listadup
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
public:
    listadup();
    listadup(const listadup &umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup &operator=(const listadup &umaLista);
    // inserção, remoção e procura
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

// constrói uma lista inicialmente vazia
listadup::listadup()
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
listadup::listadup(const listadup &umaLista)
{
    noh *aux = umaLista.primeiro;

    while (aux != NULL)
    {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup()
{
    removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos()
{
    noh *aux = primeiro;
    noh *temp;

    while (aux != NULL)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// sobrecarga do operador de atribuição
listadup &listadup::operator=(const listadup &umaLista)
{
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh *aux = umaLista.primeiro;

    while (aux != NULL)
    {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }

    return *this;
}

// insere no final da lista
void listadup::insereNoFim(acaoPrograma acao)
{
    noh *novo = new noh(acao);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
        tamanho++;
    }

    ultimo->proximo = novo;
    novo->anterior = ultimo;
    ultimo = novo;
    tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao)
{
    noh *novo = new noh(acao);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
        tamanho++;
    }
    else
    {
        primeiro->anterior = novo;
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao)
{
    noh *novo = new noh(acao);
    if (posicao <= tamanho && posicao >= 0)
    {
        if (vazia())
        {
            primeiro = novo;
            ultimo = novo;
            tamanho++;
        }
        else if (posicao == tamanho)
        {
            ultimo->proximo = novo;
            novo->anterior = ultimo;
            ultimo = novo;
            tamanho++;
        }
        else if (posicao == 0)
        {
            primeiro->anterior = novo;
            novo->proximo = primeiro;
            primeiro = novo;
            tamanho++;
        }
        else
        {
            noh *aux = primeiro;
            int posAux = 0;

            while (posAux != (posicao - 1))
            {
                aux = aux->proximo;
                posAux++;
            }

            novo->proximo = aux->proximo;
            aux->proximo = novo;
            novo->anterior = aux;
            novo->proximo->anterior = novo;
            tamanho++;
        }
    }
    else
    {
        throw runtime_error("Posição Inexistente!");
    }
}

int listadup::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }
    noh *aux = primeiro;
    int posProcura = 0;

    while (aux != NULL && aux->acao.nomeAcao != valor)
    {
        aux = aux->proximo;
        posProcura++;
    }
    if (aux == NULL || aux->acao.nomeAcao != valor)
    {
        throw runtime_error("Nao encontrado");
    }
    else
    {
        return posProcura;
    }
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime()
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }
    noh *aux = primeiro;

    while (aux != NULL)
    {
        cout << aux->acao;
        aux = aux->proximo;
    }

    cout << " IMPRIMINDO REVERSO" << endl;
    // imprime reverso
    aux = ultimo;
    while (aux != NULL)
    {
        cout << aux->acao;
        aux = aux->anterior;
    }
}

// verifica se a lista está vazia
inline bool listadup::vazia()
{
    return (tamanho == 0);
}

void listadup::removeNoInicio()
{
    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;
    primeiro = primeiro->proximo;
    if (primeiro != NULL)
        primeiro->anterior = NULL;
    delete aux;
    tamanho--;
    if (vazia())
        primeiro = NULL;
}

void listadup::removeNoFim()
{
    if (vazia())
    {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = ultimo;
    ultimo = ultimo->anterior;
    if (ultimo != NULL)
        ultimo->proximo = NULL;
    delete aux;
    tamanho--;
    if (vazia())
        primeiro = NULL;
}

int main()
{
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeAcao;

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // procurar
                cin >> nomeAcao;
                posicao = minhaLista.procura(nomeAcao);
                if (posicao == -1)
                    cout << "Nao encontrado" << endl;
                else
                    cout << posicao << endl;
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