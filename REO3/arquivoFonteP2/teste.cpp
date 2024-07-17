#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const int UMPRIMO = 7; // Constante para a função de hash

// Classe que representa um nó na lista encadeada
class noh {
    friend class lista;      // A classe 'lista' pode acessar membros privados de 'noh'
    friend class tabelaHash; // A classe 'tabelaHash' pode acessar membros privados de 'noh'

private:
    string chave; // Chave do nó
    char tipo;    // Tipo do elemento
    int valor;    // Valor do elemento
    noh *proximo; // Ponteiro para o próximo nó na lista encadeada
    // Construtor da classe 'noh'
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = nullptr) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

// Classe que representa uma lista encadeada de nós
class lista {
    friend class tabelaHash; // A classe 'tabelaHash' pode acessar membros privados de 'lista'

private:
    noh *primeiro;               // Ponteiro para o primeiro nó da lista
    unsigned short numElementos; // Quantidade de nós na lista
public:
    // Construtor
    lista() : primeiro(nullptr), numElementos(0) {}
    // Destrutor
    ~lista() {}
    // Consulta o tamanho da lista
    unsigned short tamanho() { return numElementos; }

    // Adiciona um novo nó (chave, tipo, valor) no início da lista
    void insere(const string &c, const char &t, const int &v) {
        noh *novo = new noh(c, t, v, primeiro);
        primeiro = novo;
        ++numElementos;
    }

    // Remove o nó com uma determinada chave da lista
    bool remove(const string &c) {
        noh *anterior = nullptr;
        noh *atual = primeiro;
        while ((atual != nullptr) and (atual->chave != c)) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == nullptr)
            return false; // Chave não encontrada
        if (anterior == nullptr)
            primeiro = atual->proximo;
        else
            anterior->proximo = atual->proximo;
        delete atual;
        --numElementos;
        return true;
    }

    // Busca um nó na lista por sua chave, retornando seu tipo e valor por referência
    bool busca(const string &c, char &tipoBuscado, int &valorBuscado) {
        noh *atual = primeiro;
        while ((atual != nullptr) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == nullptr)
            return false; // Chave não encontrada
        tipoBuscado = atual->tipo;
        valorBuscado = atual->valor;
        return true;
    }

    // Verifica se já existe um nó na lista com uma determinada chave
    bool verificaOcorrencia(const string &c) {
        noh *atual = primeiro;
        while ((atual != nullptr) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == nullptr)
            return false; // Chave não encontrada
        return true;
    }

    // Imprime o conteúdo da lista
    void imprime() {
        noh *atual = primeiro;
        while (atual != nullptr) {
            cout << "[" << atual->chave << "/" << atual->valor << "]";
            atual = atual->proximo;
        }
    }

    // Retorna todos os nós da lista para re-hash
    vector<noh> obterElementos() {
        vector<noh> elementos;
        noh *atual = primeiro;
        while (atual != nullptr) {
            elementos.push_back(*atual);
            atual = atual->proximo;
        }
        return elementos;
    }
};

// Classe que representa a tabela hash com encadeamento
class tabelaHash {
private:
    lista *tabela;        // Vetor de ponteiros para lista
    unsigned numPosicoes; // Quantidade de posições na tabela hash
    unsigned tamanho;     // Número de elementos na tabela hash

    // Função de hash para converter uma chave em um endereço na tabela
    unsigned funcaoHash(const string &s) {
        return funcaoHash(s, numPosicoes);
    }

    // Função de hash (versão para redimensionamento)
    unsigned funcaoHash(const string &s, int cap) {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // Construtor padrão
    tabelaHash(unsigned cap = 100) {
        numPosicoes = cap;
        tabela = new lista[numPosicoes];
        tamanho = 0;
    }

    // Destrutor
    ~tabelaHash() {
        for (unsigned i = 0; i < numPosicoes; i++) {
            noh *atual = tabela[i].primeiro;
            while (atual != nullptr) {
                noh *proximo = atual->proximo;
                delete atual;
                atual = proximo;
            }
        }
        delete[] tabela;
    }

    // Insere um nó com uma determinada chave e valor na tabela hash
    bool insere(const string &c, char &t, const int &v) {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].verificaOcorrencia(c))
            return false; // Chave já existente
        tabela[posicao].insere(c, t, v);
        tamanho++;
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;

        if (tamanho >= 0.6 * numPosicoes)
            redimensiona();
        
        return true;
    }

    // Insere um nó de forma ordenada na tabela hash
    bool insereOrdenado(const string &c, char &t, const int &v) {
        unsigned posicao = funcaoHash(c);
        noh **ptr = &tabela[posicao].primeiro;
        while (*ptr != nullptr && (*ptr)->chave < c) {
            ptr = &(*ptr)->proximo;
        }
        if (*ptr != nullptr && (*ptr)->chave == c) {
            return false; // Chave já existe, não insere.
        }
        noh *novo = new noh(c, t, v);
        novo->proximo = *ptr; // O próximo do novo é o atual *ptr.
        *ptr = novo;          // Atualiza o ponteiro anterior (ou primeiro) para apontar para o novo.
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;

        tamanho++;
        if (tamanho >= 0.6 * numPosicoes)
            redimensiona();
        
        return true;
    }

    // Retorna um valor associado a uma dada chave
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno) {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
            return true;
        return false;
    }

    // Remove um nó com uma determinada chave da tabela hash
    noh* remove(const string &c) {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c)) {
            tamanho--;
            return tabela[posicao].primeiro;
        }
        return nullptr;
    }

    // Imprime o conteúdo interno da tabela hash
    void imprime() {
        for (unsigned i = 0; i < numPosicoes; i++) {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }

    // Função para modificar um elemento
    void modificar(const string &chave, const string &novaChave, char novoTipo, int novoValor) {
        // Passo 1 & 2: Remover o elemento com a chave original
        noh *elementoModificado = remove(chave);

        if (elementoModificado != nullptr) {
            // Passo 3: Modificar os dados do elemento
            elementoModificado->chave = novaChave;
            elementoModificado->tipo = novoTipo;
            elementoModificado->valor = novoValor;

            // Passo 4 & 5: Inserir o elemento modificado na nova posição
            insere(novaChave, novoTipo, novoValor);

            // Libera o nó removido
            delete elementoModificado;
        } else {
            cout << "Elemento com a chave " << chave << " não encontrado." << endl;
        }
    }

    // Função para redimensionar a tabela hash
    void redimensiona() {
        int capAux = numPosicoes;
        numPosicoes = static_cast<unsigned>(numPosicoes * 1.5);
        lista *novaTabela = new lista[numPosicoes];

        for (int i = 0; i < capAux; i++) {
            vector<noh> elementos = tabela[i].obterElementos();
            for (noh &elemento : elementos) {
                unsigned novaPos = funcaoHash(elemento.chave, numPosicoes);
                novaTabela[novaPos].insere(elemento.chave, elemento.tipo, elemento.valor);
            }
        }

        delete[] tabela;
        tabela = novaTabela;
    }
};

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;             // Lê o tamanho da tabela hash
    tabelaHash tabela(tamanhoTH); // Cria uma tabela hash com o tamanho lido
    char comando;
    string chave;
    string novaChave;
    char tipo = 'a';
    int valor = -1;

    // Loop para processar os comandos
    do {
        try {
            cin >> comando; // Lê o comando
            switch (comando) {
            case 'i': // Inserir
                cin >> chave >> tipo >> valor;
                if (!tabela.insereOrdenado(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // Remover
                cin >> chave;
                if (!tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // Buscar
                cin >> chave;
                if (!tabela.valor(chave, tipo, valor))
                    cout << "Erro na busca: chave não encontrada!" << endl;
                else
                    cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                break;
            case 'p': // Imprimir estrutura da tabela hash
                tabela.imprime();
                break;
            case 'm': // Modificar elemento
                cin >> chave >> novaChave >> tipo >> valor;
                tabela.modificar(chave, novaChave, tipo, valor);
                break;
            case 'f': // Finalizar execução
                // Verificado no do-while
                break;
            default:
                cerr << "Comando inválido\n";
            }
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // Loop continua até o comando 'f'

    tabela.imprime(); // Imprime a tabela hash final
    cout << endl;
    return 0;
}
