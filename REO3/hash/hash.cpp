#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;
const int MAXOCUPACAO = 70;
// taxa de redimensionamento da lista
const float TXREDIM = 1.05f;

bool primo(int n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    int divisor = 2;
    while ((divisor <= sqrt(n)) and (n % divisor != 0))
        divisor++;
    return (n % divisor != 0);
}

int obterProximoPrimo(int n)
{
    bool achouProximo = false;
    int i = n;
    while (!achouProximo)
    {
        i++;
        if (primo(i))
            achouProximo = true;
    }
    return i;
}

class noh
{
    friend class lista;
    friend class tabelaHash;

private:
    string chave;
    char tipo;
    int valor;
    noh *proximo;
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox){};
};

class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;               // primeiro noh da lista
    unsigned short numElementos; // quantidade de valores na lista
public:
    lista() : primeiro(NULL), numElementos(0){}; // construtor
    ~lista()
    { // destrutor
        noh *atual = primeiro;
        while (atual != NULL)
        {
            noh *aux = atual;
            atual = atual->proximo;
            delete aux;
        }
    }
    unsigned short tamanho() { return numElementos; } // consulta do tamanho

    // adiciona um novo par de valores e insere no início da lista
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novonoh = new noh(c, t, v, primeiro);
        primeiro = novonoh;
        numElementos++;
    }
    // altera o primeiro elemento da lista
    bool alteraValor(const string &c, const int &v)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
        {
            atual = atual->proximo;
        }
        if (atual == NULL)
            return false;
        else
        {
            atual->valor = v;
            return true;
        }
    }
    // remove o noh, se nao existir retorna informacoes
    bool remove(const string &c)
    {
        noh *atual = primeiro;
        noh *anterior = NULL;
        while ((atual != NULL) and (atual->chave != c))
        {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual != NULL)
        {
            if (anterior == NULL)
            {
                primeiro = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            delete atual;
            numElementos--;
            return true;
        }
        else
            return false;
    }

    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
        {
            atual = atual->proximo;
        }
        if (atual == NULL)
        {
            return false;
        }
        else
        {
            tipoBuscado = atual->tipo;
            valorBuscado = atual->valor;
            return true;
        }
    }

    bool verificaOcorrencia(const string &c)
    {
        int inutil;
        char inutil2;
        return busca(c, inutil2, inutil);
    }

    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << atual->chave << " " << atual->valor << endl;
            atual = atual->proximo;
        }
    }
};

class tabelaHash
{
private:
    lista *tabela;
    unsigned numPosicoes;
    unsigned ocupacaoTab = 0;
    unsigned posicao(const string &s)
    {
        return posicao(s, numPosicoes);
    }
    unsigned posicao(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

    void redimensiona(int qtdePos)
    {
        lista *novaTabela = new lista[qtdePos];
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            noh *atual = tabela[i].primeiro;
            while (atual != NULL)
            {
                int novaPosicao = posicao(atual->chave, qtdePos);
                novaTabela[novaPosicao].insere(atual->chave, atual->tipo, atual->valor);
                atual = atual->proximo;
            }
        }
        delete[] tabela;
        tabela = novaTabela;
        numPosicoes = qtdePos;
    }

public:
    // construtor padrao
    tabelaHash(unsigned cap = 100)
    {
        tabela = new lista[cap];
        numPosicoes = cap;
    }
    ~tabelaHash()
    {
        delete[] tabela;
    }
    bool insere(const string &c, const char &t, const int &v)
    {
        if (100 * ocupacaoTab / numPosicoes >= MAXOCUPACAO)
        {
            while (100 * ocupacaoTab / numPosicoes >= MAXOCUPACAO)
            {
                unsigned novoNumListas = obterProximoPrimo(numPosicoes + 1);
                cout << endl
                     << "Eh necessario redimensionar a tabela de: " << numPosicoes << " para " << novoNumListas << endl
                     << endl;
                redimensiona(novoNumListas);
            }
        }

        unsigned pos = posicao(c);
        if (tabela[pos].verificaOcorrencia(c))
            return false;
        else
        {
            tabela[pos].insere(c, t, v);
            ocupacaoTab++;
            return true;
        }
    }
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned pos = posicao(c);
        return tabela[pos].busca(c, tipoBuscado, valorRetorno);
    }
    bool altera(const string &c, const int &v)
    {
        unsigned pos = posicao(c);
        return tabela[pos].alteraValor(c, v);
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

    bool remove(const string &c)
    {
        unsigned pos = posicao(c);
        if (tabela[pos].remove(c))
        {
            ocupacaoTab--;
            return true;
        }
        return false;
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
            case 'i':
                cin >> chave >> tipo >> valor;
                if (not tabela.insere(chave, tipo, valor))
                    cout << "chave ja existente: " << chave << endl;
                break;
            case 'r':
                cin >> chave;
                if (not tabela.remove(chave))
                    cout << "chave nao encontrada: " << chave << endl;
                break;
            case 'l':
                cin >> chave;
                if (not tabela.valor(chave, tipo, valor))
                    cout << "chave nao encontrada: " << chave << endl;
                else
                    cout << chave << " " << tipo << " " << valor << endl;
                break;
            case 'p':
                tabela.imprime();
                break;
            case 'f':
                break;
            default:
                cerr << "comando invalido/n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f');
    tabela.imprime();
    cout << endl;
    return 0;
}