/*
Utilizando como base o código que você desenvolveu na atividade "Hash com encadeamento - Inventário de itens de jogo", faça as alterações necessárias para que a tabela hash seja redimensionada em 3 posições caso a taxa de ocupação seja igual ou maior que 70%

*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

class noh
{
    friend class lista;
    friend class tabelaHash;

private:
    string chave;
    char tipo;
    int valor;
    noh *proximo;
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;               // primeiro nó da lista
    unsigned short numElementos; // quantidade de valores na lista
public:
    lista() : primeiro(NULL), numElementos(0) {}      // Construtor
    ~lista() {}                                       // Destrutor
    unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novo = new noh(c, t, v, primeiro);
        primeiro = novo;
        ++numElementos;
    }

    bool remove(const string &c)
    {
        noh *anterior = NULL;
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
        {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL)
            return false;
        if (anterior == NULL)
            primeiro = atual->proximo;
        else
            anterior->proximo = atual->proximo;
        delete atual;
        --numElementos;
        return true;
    }

    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false;
        tipoBuscado = atual->tipo;
        valorBuscado = atual->valor;
        return true;
    }

    bool verificaOcorrencia(const string &c)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false;
        return true;
    }

    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
        }
    }
};

class tabelaHash
{
private:
    lista *tabela;
    unsigned numPosicoes;
    unsigned numElementos; // quantidade de elementos inseridos
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }
    void redimensiona()
    {
        unsigned novaCapacidade = numPosicoes + 3;
        lista *novaTabela = new lista[novaCapacidade];

        for (unsigned i = 0; i < numPosicoes; i++)
        {
            noh *atual = tabela[i].primeiro;
            while (atual != NULL)
            {
                unsigned novaPosicao = funcaoHash(atual->chave, novaCapacidade);
                noh *novoNoh = new noh(atual->chave, atual->tipo, atual->valor, novaTabela[novaPosicao].primeiro);
                novaTabela[novaPosicao].primeiro = novoNoh;
                atual = atual->proximo;
            }
        }

        delete[] tabela;
        tabela = novaTabela;
        numPosicoes = novaCapacidade;
    }

public:
    tabelaHash(unsigned cap = 100) : numPosicoes(cap), numElementos(0)
    {
        tabela = new lista[numPosicoes];
    }
    ~tabelaHash()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            noh *atual = tabela[i].primeiro;
            while (atual != NULL)
            {
                noh *proximo = atual->proximo;
                delete atual;
                atual = proximo;
            }
        }
        delete[] tabela;
    }
    bool insere(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].verificaOcorrencia(c))
            return false;
        tabela[posicao].insere(c, t, v);
        ++numElementos;
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
        if ((float(numElementos) / numPosicoes) >= 0.7)
        {
            cout << "É necessario redimensionar de " << numPosicoes << " para " << (numPosicoes + 3) << endl;
            redimensiona();
        }
        return true;
    }

    bool insereOrdenado(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        noh **ptr = &tabela[posicao].primeiro;
        while (*ptr != NULL && (*ptr)->chave < c)
        {
            ptr = &(*ptr)->proximo;
        }
        if (*ptr != NULL && (*ptr)->chave == c)
        {
            return false;
        }
        noh *novo = new noh(c, t, v);
        novo->proximo = *ptr;
        *ptr = novo;
        ++numElementos;
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
        if ((float(numElementos) / numPosicoes) >= 0.7)
        {
            cout << "É necessario redimensionar de " << numPosicoes << " para " << (numPosicoes + 3) << endl;
            redimensiona();
        }
        return true;
    }

    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
            return true;
        return false;
    }

    bool remove(const string &c)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c))
        {
            --numElementos;
            return true;
        }
        return false;
    }

    void imprime()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }
};

int main()
{
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> chave >> tipo >> valor;
                if (not tabela.insereOrdenado(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // remover
                cin >> chave;
                if (not tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // buscar
                cin >> chave;
                if (not tabela.valor(chave, tipo, valor))
                    cout << "Erro na busca: chave não encontrada!" << endl;
                else
                    cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                break;
            case 'p': // mostrar estrutura
                tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}