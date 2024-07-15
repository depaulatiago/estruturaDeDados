/*
Utilizando como base o código que você desenvolveu na atividade "Hash com encadeamento - Inventário de itens de jogo", altere as inserções para que a inserção na lista seja ordenada

Exemplo de Entrada e Saída juntas:


*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um noh guarda um par (chave / valor)
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

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;               // primeiro nó da lista
    unsigned short numElementos; // quantidade de valores na lista
public:
    lista() {}                                        // Construtor
    ~lista() {}                                       // Destrutor
    unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
    // Adiciona um novo par (chave, valor) na lista
    // Insere no início, para não precisar de ponteiro para o fim
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novo = new noh(c, t, v, primeiro);
        primeiro = novo;
        ++numElementos;
    }

    // Remove o noh com dada chave da lista.
    // Se a chave não existe, retorna informação.
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
    // Busca um elemento na lista, retorna falso se não encontrado
    // o valor buscado é retornado por passagem por referência
    // na variável valorBuscado
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
    // Verifica se já tem algum dado na lista com
    // uma dada chave
    bool verificaOcorrencia(const string &c)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false;
        return true;
    }
    // Imprime o conteúdo da lista, para fins de depuração
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
    // vetor de ponteiros para lista
    lista *tabela;
    // quantidade de posições na tabela hash
    unsigned numPosicoes;
    // converte uma chave (string) num endereço da tabela
    // - versão simples
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }
    // converte uma chave (string) num endereço da tabela
    // - versão para redimensionamento
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // construtor padrão
    tabelaHash(unsigned cap = 100)
    {
        numPosicoes = cap;
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
    // Insere um nó com dada chave e valor.
    bool insere(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].verificaOcorrencia(c))
            return false;
        tabela[posicao].insere(c, t, v);
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
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
            return false; // Chave já existe, não insere.
        }
        noh *novo = new noh(c, t, v);
        novo->proximo = *ptr; // O próximo do novo é o atual *ptr.
        *ptr = novo;          // Atualiza o ponteiro anterior (ou primeiro) para apontar para o novo.
        cout << "chave '" << c << "' inserida na posicao " << posicao <<  endl;
        return true;
    }
    // Retorna um valor associado a uma dada chave.
    // Se a chave não existe, retorna "NÃO ENCONTRADO!".
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
            return true;
        return false;
    }
    // Retira do hash um nó com dada chave.
    bool remove(const string &c)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c))
            return true;
        return false;
    }
    // Imprime o conteúdo interno do hash (para fins de depuração)
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
            case 'l': // remover
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