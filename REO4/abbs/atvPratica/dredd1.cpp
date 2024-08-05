#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo

enum posicao {dir, esq};

class noh {
    friend class abb;
    private:
        Dado valor;
        noh* esq;
        noh* dir;
        noh* pai;
    public:
        noh(Dado d = 0);
        ~noh();
};

noh::noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

noh::~noh() {
    delete esq; // não precisa checar se é nulo em C++
    delete dir;
}

class abb {
    private:
        noh* raiz;
        void percorreEmOrdemAux(noh* atual, int nivel);
        void percorrePreOrdemAux(noh* atual);
        void percorrePosOrdemAux(noh* atual);
        // menor e maior valor de uma subárvore com pai em raizSub
        noh* minimoAux(noh* raizSub);
        noh* maximoAux(noh* raizSub);
        // transplanta o nó novo para o local onde estava o nó antigo
        void transplanta(noh* antigo, noh* novo);
        int calculaAlturaAux(noh* atual);
    public:
        abb() { raiz = NULL; }
        ~abb();
        void insere(Dado d);
        void remove(Dado d);
        noh* busca(Dado d);
        Dado minimo();
        Dado maximo();
        void percorreEmOrdem();
        void percorrePreOrdem();
        void percorrePosOrdem();
        int calculaAltura();
};

abb::~abb() {
    delete raiz;
}

void abb::insere(Dado d) {
    noh* novo = new noh(d);
    posicao posInsercao;

    // primeiro caso: árvore vazia
    if (raiz == NULL) {
        raiz = novo;
    } else {
        noh* atual = raiz;
        noh* anterior = NULL;

        // encontrando ponto de inserção
        while (atual != NULL) {
            anterior = atual;

            // trocar por >=, se quiser elementos iguais
            if (atual->valor > d) {
                atual = atual->esq;
                posInsercao = esq;
            } else {
                atual = atual->dir;
                posInsercao = dir;
            }
        }

        // inserindo o novo nó na árvore
        novo->pai = anterior;

        if (posInsercao == dir) {
            anterior->dir = novo;
        } else {
            anterior->esq = novo;
        }
    }
}

noh* abb::busca(Dado d) {
    noh* atual = raiz;

    while (atual != NULL) {
        if (atual->valor == d) {
            return atual;
        } else if (atual->valor > d) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    return NULL;
}

Dado abb::minimo() {
    if (raiz == NULL) {
        cerr << "Árvore vazia!" << endl;
        exit(EXIT_FAILURE);
    } else {
        noh* nohMin = minimoAux(raiz);
        return nohMin->valor;
    }
}

noh* abb::minimoAux(noh* raizSub) {
    while (raizSub->esq != NULL) {
        raizSub = raizSub->esq;
    }
    return raizSub;
}

Dado abb::maximo() {
    if (raiz == NULL) {
        cerr << "Árvore vazia!" << endl;
        exit(EXIT_FAILURE);
    } else {
        noh* nohMax = maximoAux(raiz);
        return nohMax->valor;
    }
}

noh* abb::maximoAux(noh* raizSub) {
    while (raizSub->dir != NULL) {
        raizSub = raizSub->dir;
    }
    return raizSub;
}

void abb::transplanta(noh* antigo, noh* novo) {
    if (antigo->pai == NULL) {
        raiz = novo;
    } else if (antigo == antigo->pai->esq) {
        antigo->pai->esq = novo;
    } else {
        antigo->pai->dir = novo;
    }
    if (novo != NULL) {
        novo->pai = antigo->pai;
    }
}

void abb::remove(Dado dado) {
    noh* nohRemover = busca(dado);

    if (nohRemover == NULL) {
        cerr << "Valor não está na árvore!" << endl;
    } else {
        if (nohRemover->esq == NULL) {
            transplanta(nohRemover, nohRemover->dir);
        } else if (nohRemover->dir == NULL) {
            transplanta(nohRemover, nohRemover->esq);
        } else {
            noh* sucessor = minimoAux(nohRemover->dir);

            if (sucessor->pai != nohRemover) {
                transplanta(sucessor, sucessor->dir);
                sucessor->dir = nohRemover->dir;
                sucessor->dir->pai = sucessor;
            }

            transplanta(nohRemover, sucessor);
            sucessor->esq = nohRemover->esq;
            sucessor->esq->pai = sucessor;
        }

        nohRemover->esq = NULL;
        nohRemover->dir = NULL;
        delete nohRemover;
    }
}

void abb::percorreEmOrdem() {
    percorreEmOrdemAux(raiz, 1); // Começa do nível 1
    cout << endl;
}

void abb::percorreEmOrdemAux(noh* atual, int nivel) {
    if (atual != NULL) {
        percorreEmOrdemAux(atual->esq, nivel + 1);
        cout << atual->valor << "/" << nivel << " ";
        percorreEmOrdemAux(atual->dir, nivel + 1);
    }
}

void abb::percorrePreOrdem() {
    percorrePreOrdemAux(raiz);
    cout << endl;
}

void abb::percorrePreOrdemAux(noh* atual) {
    if (atual != NULL) {
        cout << atual->valor << " ";
        percorrePreOrdemAux(atual->esq);
        percorrePreOrdemAux(atual->dir);
    }
}

void abb::percorrePosOrdem() {
    percorrePosOrdemAux(raiz);
    cout << endl;
}

void abb::percorrePosOrdemAux(noh* atual) {
    if (atual != NULL) {
        percorrePosOrdemAux(atual->esq);
        percorrePosOrdemAux(atual->dir);
        cout << atual->valor << " ";
    }
}

int abb::calculaAltura() {
    return calculaAlturaAux(raiz) + 1; // Ajusta para que a altura mínima seja 1
}

int abb::calculaAlturaAux(noh* atual) {
    if (atual == NULL) {
        return -1; // base case: altura de árvore vazia é -1
    } else {
        int alturaEsq = calculaAlturaAux(atual->esq);
        int alturaDir = calculaAlturaAux(atual->dir);
        return 1 + max(alturaEsq, alturaDir);
    }
}

int main() {
    abb minhaArvore;
    int valor;
    int num;

    // Leitura e inserção dos elementos na árvore
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> valor;
        minhaArvore.insere(valor);
        cout << minhaArvore.calculaAltura() << " ";
    }
    cout << endl;
    minhaArvore.percorreEmOrdem();

    // Leitura e remoção dos elementos na árvore
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> valor;
        minhaArvore.remove(valor);
        cout << minhaArvore.calculaAltura() << " ";
    }
    cout << endl;
    minhaArvore.percorreEmOrdem();

    return 0;
}
