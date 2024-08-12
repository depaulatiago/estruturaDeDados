/*
Implemente uma Árvore Binária de Busca (ABB) com operações para inserir, remover e escrever os elementos de duas formas (em ordem e pré-ordem). A árvore criada deve ser capaz de armazenar um único tipo de informação (chave). As chaves no programa serão números inteiros, porém, quando mais independente for a classe, melhor. A estratégia a respeito de como lidar com chaves repetidas não é importante.

As operações para escrever elementos devem sempre escrever a chave, uma barra e o nível na árvore em que a chave está. Isso vai ajudar a determinar a estrutura da árvore ao testar o programa. Não devem ser colocados espaços antes nem depois da barra.

Caso tentem remover uma chave que não está na árvore, o programa deverá escrever "ERRO" (letras maiúsculas, sem as aspas) na saída padrão. A operação de escrita deve estar na função principal (programa) e não em algum método.

A estratégia de remoção de nó com dois filhos deve ser a de substituir pelo sucessor.

O programa deverá ler comandos identificados por letras minúsculas e seus parâmetros (quando necessário). Os comandos possíveis devem ser:

A letra i, seguida de uma chave para inserir uma chave na árvore.
A letra r, seguida de uma chave para remover uma chave da árvore.
A letra o para escrever os elementos em ordem, no formato descrito acima.
A letra p para escrever os elementos em pré-ordem, no formato descrito acima.
A letra f para finalizar a execução do programa.
Entradas:

Uma sequência de comandos, conforme especificado acima.

Saídas:

Somente os comandos para escrever produzem saída, conforme formato explicado acima.

Exemplo de Entrada:

i 3
i 4
i 2
i 5
i 1
r 3
o
p
f
Exemplo de Saída:

1/2 2/1 4/0 5/1 
4/0 2/1 1/2 5/1
*/
#include <iostream>
using namespace std;

// Classe que representa o objeto armazenado na árvore
class objeto
{
private:
    int numero; // Atributo que armazena a chave (número inteiro)

public:
    // Construtor padrão que inicializa a chave com -1
    objeto()
    {
        numero = -1;
    }

    // Construtor que inicializa a chave com o valor passado
    objeto(int n)
    {
        numero = n;
    }

    // Método que retorna o valor da chave
    int getNumero()
    {
        return numero;
    }
};

// Classe que representa um nó na árvore binária
class noh
{
    friend class ABB; // Permite que a classe ABB acesse os membros privados da classe noh

private:
    objeto elemento;    // Objeto que armazena a chave do nó
    noh *filhoEsquerda; // Ponteiro para o filho à esquerda
    noh *filhoDireita;  // Ponteiro para o filho à direita

public:
    // Construtor que inicializa um nó com um objeto e filhos nulos
    noh(objeto o)
    {
        elemento = o;
        filhoEsquerda = NULL;
        filhoDireita = NULL;
    }
};

// Classe que implementa a Árvore Binária de Busca (ABB)
class ABB
{
private:
    noh *raiz; // Ponteiro para a raiz da árvore

    // Métodos auxiliares privados para manipulação da árvore
    void removerBusca(int n, noh *&atual);
    void deletarNoh(noh *&atual);
    void obterSucessor(objeto &objSucessor, noh *aux);

public:
    // Construtor que inicializa a árvore como vazia
    ABB();

    // Destrutor que libera toda a memória alocada pela árvore
    ~ABB();

    // Método recursivo para deletar todos os nós da árvore
    void deletaTudo(noh *atual);

    // Método que retorna a raiz da árvore
    noh *getRaiz();

    // Método que verifica se a árvore está vazia
    bool vazia();

    // Método para inserir uma nova chave na árvore
    void inserir(int n);

    // Método para remover uma chave da árvore
    void remover(int n);

    // Método para buscar uma chave na árvore e retornar o objeto associado
    bool buscar(int n, objeto &objRetorno);

    // Métodos para imprimir os elementos da árvore em diferentes ordens
    void imprimePreOrdem(noh *atual, int nivel);
    void imprimeEmOrdem(noh *atual, int nivel);
    void imprimePosOrdem(noh *atual, int nivel);
};

// Implementação do construtor da ABB, que define a raiz como nula
ABB::ABB()
{
    raiz = NULL;
}

// Implementação do destrutor da ABB, que deleta todos os nós
ABB::~ABB()
{
    deletaTudo(raiz);
}

// Método recursivo que deleta todos os nós da árvore
void ABB::deletaTudo(noh *atual)
{
    if (atual != NULL)
    {
        deletaTudo(atual->filhoEsquerda); // Deleta subárvore esquerda
        deletaTudo(atual->filhoDireita);  // Deleta subárvore direita
        delete atual;                     // Deleta o nó atual
    }
}

// Método que retorna o ponteiro para a raiz da árvore
noh *ABB::getRaiz()
{
    return raiz;
}

// Método que verifica se a árvore está vazia
bool ABB::vazia()
{
    return raiz == NULL;
}

// Método para inserir uma nova chave na árvore
void ABB::inserir(int n)
{
    noh *novo = new noh(objeto(n)); // Cria um novo nó com a chave n
    if (vazia())
    {
        raiz = novo; // Se a árvore estiver vazia, a raiz passa a ser o novo nó
    }
    else
    {
        noh *aux = raiz; // Ponteiro auxiliar para percorrer a árvore
        while (aux != NULL)
        {
            if (n < aux->elemento.getNumero()) // Se a chave é menor, vai para a esquerda
            {
                if (aux->filhoEsquerda == NULL)
                {
                    aux->filhoEsquerda = novo; // Insere o novo nó como filho à esquerda
                    aux = NULL;
                }
                else
                {
                    aux = aux->filhoEsquerda; // Continua a busca na subárvore esquerda
                }
            }
            else
            {
                if (aux->filhoDireita == NULL)
                {
                    aux->filhoDireita = novo; // Insere o novo nó como filho à direita
                    aux = NULL;
                }
                else
                {
                    aux = aux->filhoDireita; // Continua a busca na subárvore direita
                }
            }
        }
    }
}

// Método público para remover uma chave da árvore
void ABB::remover(int n)
{
    removerBusca(n, raiz); // Inicia a busca para remoção a partir da raiz
}

// Método recursivo para buscar e remover uma chave
void ABB::removerBusca(int n, noh *&atual)
{
    if (n == atual->elemento.getNumero()) // Se a chave for encontrada
    {
        deletarNoh(atual); // Deleta o nó atual
    }
    else if (n < atual->elemento.getNumero()) // Se a chave é menor, busca à esquerda
    {
        removerBusca(n, atual->filhoEsquerda);
    }
    else // Se a chave é maior, busca à direita
    {
        removerBusca(n, atual->filhoDireita);
    }
}

// Método para deletar um nó específico
void ABB::deletarNoh(noh *&atual)
{
    noh *aux = atual; // Nó auxiliar para manipulação
    if (atual->filhoEsquerda == NULL)
    {
        atual = atual->filhoDireita; // Substitui pelo filho direito se não houver filho esquerdo
        delete aux;                  // Deleta o nó
    }
    else if (atual->filhoDireita == NULL)
    {
        atual = atual->filhoEsquerda; // Substitui pelo filho esquerdo se não houver filho direito
        delete aux;                   // Deleta o nó
    }
    else
    {
        objeto objSucessor;                                         // Objeto para armazenar o sucessor
        obterSucessor(objSucessor, atual);                          // Obtém o sucessor do nó atual
        atual->elemento = objSucessor;                              // Substitui o elemento do nó pelo sucessor
        removerBusca(objSucessor.getNumero(), atual->filhoDireita); // Remove o sucessor
    }
}

// Método para obter o sucessor de um nó
void ABB::obterSucessor(objeto &objSucessor, noh *aux)
{
    aux = aux->filhoDireita; // Começa pela subárvore direita
    while (aux->filhoEsquerda != NULL)
    {
        aux = aux->filhoEsquerda; // Vai para a esquerda até encontrar o menor elemento
    }
    objSucessor = aux->elemento; // O menor elemento é o sucessor
}

// Método para buscar uma chave na árvore
bool ABB::buscar(int n, objeto &objRetorno)
{
    if (vazia())
    {
        return false; // Se a árvore está vazia, retorna falso
    }
    else
    {
        noh *aux = raiz; // Ponteiro auxiliar para percorrer a árvore
        while (aux != NULL)
        {
            if (n == aux->elemento.getNumero()) // Se a chave for encontrada
            {
                objRetorno = aux->elemento; // Retorna o objeto associado
                return true;
            }
            else if (n < aux->elemento.getNumero()) // Se a chave é menor, busca à esquerda
            {
                aux = aux->filhoEsquerda;
            }
            else // Se a chave é maior, busca à direita
            {
                aux = aux->filhoDireita;
            }
        }
        return false; // Retorna falso se a chave não for encontrada
    }
}

// Método para imprimir os elementos da árvore em pré-ordem
void ABB::imprimePreOrdem(noh *atual, int nivel)
{
    if (atual != NULL)
    {
        cout << atual->elemento.getNumero() << "/" << nivel << " "; // Imprime o elemento e o nível
        imprimePreOrdem(atual->filhoEsquerda, nivel + 1);           // Imprime a subárvore esquerda
        imprimePreOrdem(atual->filhoDireita, nivel + 1);            // Imprime a subárvore direita
    }
}

// Método para imprimir os elementos da árvore em ordem
void ABB::imprimeEmOrdem(noh *atual, int nivel)
{
    if (atual != NULL)
    {
        imprimeEmOrdem(atual->filhoEsquerda, nivel + 1);            // Imprime a subárvore esquerda
        cout << atual->elemento.getNumero() << "/" << nivel << " "; // Imprime o elemento e o nível
        imprimeEmOrdem(atual->filhoDireita, nivel + 1);             // Imprime a subárvore direita
    }
}

// Método para imprimir os elementos da árvore em pós-ordem
void ABB::imprimePosOrdem(noh *atual, int nivel)
{
    if (atual != NULL)
    {
        imprimePosOrdem(atual->filhoEsquerda, nivel + 1);           // Imprime a subárvore esquerda
        imprimePosOrdem(atual->filhoDireita, nivel + 1);            // Imprime a subárvore direita
        cout << atual->elemento.getNumero() << "/" << nivel << " "; // Imprime o elemento e o nível
    }
}

// Função principal que lê comandos e manipula a árvore
int main()
{
    ABB abb;        // Cria uma instância da árvore binária
    objeto objAux;  // Objeto auxiliar para operações de busca
    char comando;   // Variável para armazenar o comando lido
    int valor = -1; // Variável para armazenar o valor lido

    do
    {
        try
        {
            cin >> comando; // Lê o comando do usuário
            switch (comando)
            {
            case 'i': // Comando para inserir uma chave na árvore
                cin >> valor;
                abb.inserir(valor);
                break;
            case 'r': // Comando para remover uma chave da árvore
                cin >> valor;
                if (abb.buscar(valor, objAux)) // Verifica se a chave existe antes de remover
                {
                    abb.remover(valor);
                }
                else
                {
                    cout << "ERRO" << endl; // Se a chave não existe, imprime "ERRO"
                }
                break;
            case 'o': // Comando para imprimir a árvore em ordem
                abb.imprimeEmOrdem(abb.getRaiz(), 0);
                break;
            case 'p': // Comando para imprimir a árvore em pré-ordem
                abb.imprimePreOrdem(abb.getRaiz(), 0);
                break;
            case 'z': // Comando para imprimir a árvore em pós-ordem
                abb.imprimePosOrdem(abb.getRaiz(), 0);
                break;
            case 'b': // Comando para buscar uma chave na árvore
                cin >> valor;
                if (abb.buscar(valor, objAux))
                {
                    cout << objAux.getNumero() << endl; // Se encontrada, imprime a chave
                }
                else
                {
                    cout << "Objeto não encontrado!" << endl; // Se não encontrada, imprime mensagem de erro
                }
                break;
            case 'f': // Comando para finalizar a execução do programa
                // A execução termina no do-while
                break;
            default:
                cerr << "comando inválido\n"; // Mensagem de erro para comandos inválidos
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl; // Captura e imprime exceções de tempo de execução
        }
    } while (comando != 'f'); // Continua até que o comando 'f' seja lido para finalizar
    return 0; // Finaliza o programa
}
