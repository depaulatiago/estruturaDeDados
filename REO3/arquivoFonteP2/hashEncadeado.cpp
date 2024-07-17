/*
Implemente uma função que realize a modificação dos dados de um elemento da Hash. Será possível alterar qualquer campo do elemento e após a modificação, a posição do elemento na tabela hash deve ser recalculada.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Hash com encadeamento - Inventário de itens de jogo" como base.

Entradas:

Com essa finalidade, você deverá adicionar mais um comando, como segue:

m seguido de duas strings, um char e um inteiro: para alterar um elemento com uma determinada chave, sua nova chave, o novo tipo e o novo valor.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a modificação. Ao terminar a execução do programa, todos os itens da hash são escritos.

Exemplo de Entrada e Saída juntas:

6
r dez
Erro na remoção: chave não encontrada!
i um a 1
chave 'um' inserida na posicao 4
i dois b 2
chave 'dois' inserida na posicao 5
i quatro d 4
chave 'quatro' inserida na posicao 2
i sete g 7
chave 'sete' inserida na posicao 1
i oito h 8
chave 'oito' inserida na posicao 5
i dez j 10
chave 'dez' inserida na posicao 5
i tres c 3
chave 'tres' inserida na posicao 2
p
0: 
1: [sete/7]
2: [tres/3][quatro/4]
3: 
4: [um/1]
5: [dez/10][oito/8][dois/2]
m oito oitocentos w 800
p
0: 
1: [sete/7]
2: [tres/3][quatro/4]
3: [oitocentos/800]
4: [um/1]
5: [dez/10][dois/2]
l dez
Tipo: j Valor: 10
f
0: 
1: [sete/7]
2: [tres/3][quatro/4]
3: [oitocentos/800]
4: [um/1]
5: [dez/10][dois/2]
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7; // Constante para a função de hash

// Classe que representa um nó na lista encadeada
class noh
{
    friend class lista;      // A classe 'lista' pode acessar membros privados de 'noh'
    friend class tabelaHash; // A classe 'tabelaHash' pode acessar membros privados de 'noh'

private:
    string chave; // Chave do nó
    char tipo;    // Tipo do elemento
    int valor;    // Valor do elemento
    noh *proximo; // Ponteiro para o próximo nó na lista encadeada
    // Construtor da classe 'noh'
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

// Classe que representa uma lista encadeada de nós
class lista
{
    friend class tabelaHash; // A classe 'tabelaHash' pode acessar membros privados de 'lista'

private:
    noh *primeiro;               // Ponteiro para o primeiro nó da lista
    unsigned short numElementos; // Quantidade de nós na lista
public:
    // Construtor
    lista() : primeiro(NULL), numElementos(0) {}
    // Destrutor
    ~lista() {}
    // Consulta o tamanho da lista
    unsigned short tamanho() { return numElementos; }

    // Adiciona um novo nó (chave, tipo, valor) no início da lista
    void insere(const string &c, const char &t, const int &v)
    {
        noh *novo = new noh(c, t, v, primeiro);
        primeiro = novo;
        ++numElementos;
    }

    // Remove o nó com uma determinada chave da lista
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
            return false; // Chave não encontrada
        if (anterior == NULL)
            primeiro = atual->proximo;
        else
            anterior->proximo = atual->proximo;
        delete atual;
        --numElementos;
        return true;
    }

    // Busca um nó na lista por sua chave, retornando seu tipo e valor por referência
    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false; // Chave não encontrada
        tipoBuscado = atual->tipo;
        valorBuscado = atual->valor;
        return true;
    }

    // Verifica se já existe um nó na lista com uma determinada chave
    bool verificaOcorrencia(const string &c)
    {
        noh *atual = primeiro;
        while ((atual != NULL) and (atual->chave != c))
            atual = atual->proximo;
        if (atual == NULL)
            return false; // Chave não encontrada
        return true;
    }

    // Imprime o conteúdo da lista
    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "[" << atual->chave << "/" << atual->valor << "]";
            atual = atual->proximo;
        }
    }
};

// Classe que representa a tabela hash com encadeamento
class tabelaHash
{
private:
    lista *tabela;        // Vetor de ponteiros para lista
    unsigned numPosicoes; // Quantidade de posições na tabela hash

    // Função de hash para converter uma chave em um endereço na tabela
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }

    // Função de hash (versão para redimensionamento)
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // Construtor padrão
    tabelaHash(unsigned cap = 100)
    {
        numPosicoes = cap;
        tabela = new lista[numPosicoes];
    }

    // Destrutor
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

    // Insere um nó com uma determinada chave e valor na tabela hash
    bool insere(const string &c, char &t, const int &v)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].verificaOcorrencia(c))
            return false; // Chave já existente
        tabela[posicao].insere(c, t, v);
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
        return true;
    }

    // Insere um nó de forma ordenada na tabela hash
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
        cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
        return true;
    }

    // Retorna um valor associado a uma dada chave
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].busca(c, tipoBuscado, valorRetorno))
            return true;
        return false;
    }

    // Remove um nó com uma determinada chave da tabela hash
    noh *remove(const string &c)
    {
        unsigned posicao = funcaoHash(c);
        if (tabela[posicao].remove(c))
            return tabela[posicao].primeiro;
        return nullptr;
    }

    // Imprime o conteúdo interno da tabela hash
    void imprime()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }

    // Função para modificar um elemento
    void modificar(const string &chave, const string &novaChave, char novoTipo, int novoValor)
    {
        // Passo 1 & 2: Remover o elemento com a chave original
        noh *elementoModificado = remove(chave);

        if (elementoModificado != nullptr)
        {
            // Passo 3: Modificar os dados do elemento
            elementoModificado->chave = novaChave;
            elementoModificado->tipo = novoTipo;
            elementoModificado->valor = novoValor;

            // Passo 4 & 5: Inserir o elemento modificado na nova posição
            insere(novaChave, novoTipo, novoValor);

            // Libera o nó removido
            delete elementoModificado;
        }
        else
        {
            cout << "Elemento com a chave " << chave << " não encontrado." << endl;
        }
    }
};

int main()
{
    int tamanhoTH;
    cin >> tamanhoTH;             // Lê o tamanho da tabela hash
    tabelaHash tabela(tamanhoTH); // Cria uma tabela hash com o tamanho lido
    char comando;
    string chave;
    string novaChave;
    char tipo = 'a';
    int valor = -1;

    // Loop para processar os comandos
    do
    {
        try
        {
            cin >> comando; // Lê o comando
            switch (comando)
            {
            case 'i': // Inserir
                cin >> chave >> tipo >> valor;
                if (not tabela.insereOrdenado(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // Remover
                cin >> chave;
                if (not tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // Buscar
                cin >> chave;
                if (not tabela.valor(chave, tipo, valor))
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
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // Loop continua até o comando 'f'

    tabela.imprime(); // Imprime a tabela hash final
    cout << endl;
    return 0;
}
