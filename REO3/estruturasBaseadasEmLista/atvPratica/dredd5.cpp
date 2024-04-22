/*
Utilizando como base o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" faça as adaptações necessárias para que ela funcione como deque. Todos os métodos que não devem ser permitidos para uso em uma deque devem retornar ao usuário que o procedimento não é permitido.

Uma deque é uma estrutura de dados lista em que a remoção e inserção só é permitida em suas pontas (ou seja: no início e no final da lista).

Feito isso, você deverá adicionar mais um procedimento fora da classe, que recebe uma deque e uma string e remove um elemento qualquer, mas sem quebrar a estrutura. Ou seja: a remoção deverá ser implementada de maneira similar à remoção em uma pilha ou fila. Utilizando esse procedimento, adicione a seguinte opção no menu da função principal:

x seguido de uma string: remove da lista o elemento que possui o nome da ação informado pelo usuário. Imprimir Remoção em lista vazia! caso a chamada ao procedimento seja chamada com a lista vazia. Imprimir Nao encontrado caso não encontre o elemento em uma lista que possua pelo menos um elemento
Lembrando novamente: esse comando deverá ser implementado sem quebra de estrutura.

Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para remover o elemento solicitado. Ao terminar a execução do programa, todos os itens da listas são escritos.

Exemplo de Entrada e Saída juntas:

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
Operação não permitida!
i 3 paralelismoProc 65 23
p
(3, paralelismoProc, 65, 23)
(1, limparCache, 123, 99)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO 
(2, semaforoProc, 32, 11)
(1, limparCache, 123, 99)
(3, paralelismoProc, 65, 23)
s empilharProcessos
Nao encontrado
x limparCache
p
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO 
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
r
p
(2, semaforoProc, 32, 11)
 IMPRIMINDO REVERSO 
(2, semaforoProc, 32, 11)
f
*/

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

typedef int Dado;

class noh {
    friend class deque;
    private:
        Dado dado;
        noh* proximo;
        noh* anterior;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
    anterior = NULL;
}

class deque {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        void removeTodos();
        void imprimeReversoAux(noh* umNoh);
    public:
        deque();
        deque(const deque& umadeque);
        ~deque();
        deque& operator=(const deque& umadeque);
        inline void insereInicio(Dado dado);
        inline void insereFim(Dado dado);
        void imprime();
        void imprimeReverso();
        inline bool vazia();
        void removeInicio();
        void removeFim();
        void removeValor(Dado valor);
        void removeElemento(string nome);
};

deque::deque() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

deque::deque(const deque& umadeque) {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
    noh* aux = umadeque.primeiro;
    while (aux != NULL) {
        insereFim(aux->dado);
        aux = aux->proximo;
    }
}

deque::~deque() {
    removeTodos();
}

deque& deque::operator=(const deque& umadeque) {
    removeTodos();
    noh* aux = umadeque.primeiro;
    while (aux != NULL) {
        insereFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
}

void deque::removeTodos() {
    noh* aux = primeiro;
    noh* temp;
    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

inline void deque::insereInicio(Dado dado) {
    noh* novo = new noh(dado);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        novo->proximo = primeiro;
        primeiro->anterior = novo;
        primeiro = novo;
    }
    ++tamanho;
}

inline void deque::insereFim(Dado dado) {
    noh* novo = new noh(dado);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    ++tamanho;
}

void deque::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

void deque::imprimeReversoAux(noh* umNoh) {
    if (umNoh != NULL) {
        imprimeReversoAux(umNoh->proximo);
        cout << umNoh->dado << " ";
    }
}

void deque::imprimeReverso() {
    imprimeReversoAux(primeiro);
    cout << endl;
}

inline bool deque::vazia() {
    return (tamanho == 0);
}

void deque::removeInicio() {
    if (vazia()) {
        cerr << "Remocao em deque vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    if (primeiro != NULL) {
        primeiro->anterior = NULL;
    }
    delete removido;
    --tamanho;
    if (vazia()) {
        ultimo = NULL;
    }
}

void deque::removeFim() {
    if (vazia()) {
        cerr << "Remocao em deque vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    noh* removido = ultimo;
    ultimo = ultimo->anterior;
    if (ultimo != NULL) {
        ultimo->proximo = NULL;
    }
    delete removido;
    --tamanho;
    if (vazia()) {
        primeiro = NULL;
    }
}

void deque::removeValor(Dado valor) {
    noh* atual = primeiro;
    noh* anterior = NULL;
    while ((atual != NULL) and (atual->dado != valor)) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL) {
        if (atual == primeiro) {
            removeInicio();
        } else if (atual == ultimo) {
            removeFim();
        } else {
            anterior->proximo = atual->proximo;
            atual->proximo->anterior = anterior;
            delete atual;
            --tamanho;
        }
    }
}

void deque::removeElemento(string nome) {
    noh* atual = primeiro;
    noh* anterior = NULL;
    while ((atual != NULL) and (atual->dado != nome)) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual != NULL) {
        if (atual == primeiro) {
            removeInicio();
        } else if (atual == ultimo) {
            removeFim();
        } else {
            anterior->proximo = atual->proximo;
            atual->proximo->anterior = anterior;
            delete atual;
            --tamanho;
        }
    } else {
        cout << "Nao encontrado" << endl;
    }
}

int main() {
    deque minhaDeque;
    char opcao;
    Dado valor;
    string nome;
    do {
        cin >> opcao;
        switch(opcao) {
            case 'i': // inserir
                cin >> valor;
                minhaDeque.insereFim(valor);
                break;
            case 'r': // remover
                if (minhaDeque.vazia()) {
                    cout << "Remoção em lista vazia!" << endl;
                } else {
                    minhaDeque.removeInicio();
                }
                break;
            case 'p': // imprimir
                if (minhaDeque.vazia()) {
                    cout << "Lista vazia!" << endl;
                } else {
                    minhaDeque.imprime();
                }
                break;
            case 'h': // inserir no inicio
                cin >> valor;
                minhaDeque.insereInicio(valor);
                break;
            case 'm': // inserir no meio
                cout << "Operação não permitida!" << endl;
                break;
            case 'f': // inserir no fim
                cout << "Operação não permitida!" << endl;
                break;
            case 's': // imprimir reverso
                if (minhaDeque.vazia()) {
                    cout << "Lista vazia!" << endl;
                } else {
                    cout << " IMPRIMINDO REVERSO " << endl;
                    minhaDeque.imprimeReverso();
                }
                break;
            case 'x': // remover elemento
                cin >> nome;
                minhaDeque.removeElemento(nome);
                break;
        }
    } while (opcao != 'q');
    minhaDeque.imprime();
    return 0;
}
