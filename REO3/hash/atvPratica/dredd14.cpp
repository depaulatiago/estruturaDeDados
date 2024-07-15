/*
Utilizando como base o código que você desenvolveu na atividade "Hash com endereçamento aberto -
 Lista de processos em uma repartição pública", faça as alterações necessárias para que a tabela hash seja redimensionada,
  aumentando sua capacidade em 100%, quando a ocupação chegar ou ultrapassar 70%.

Exemplo de Entrada e Saída juntas:

r Joao
Impossível remover de hash vazia.
i processo1 Joao a 2
i processo2 Maria c 5
i processo3 Severino d 9
i processo4 Marcos f 12
p
[0:Severino/9] [1:] [2:Marcos/12] [3:] [4:Joao/2] [5:Maria/5] 
i processo5 Barnabe a 10
p
[0:Severino/9] [1:Barnabe/10] [2:Marcos/12] [3:] [4:] [5:] [6:] [7:] [8:] [9:] [10:Joao/2] [11:Maria/5] 
i processo6 Tiao z 22
i processo7 Marlon a 40
i processo8 Manoel m 88
p
[0:Severino/9] [1:Barnabe/10] [2:Marcos/12] [3:Tiao/22] [4:] [5:Manoel/88] [6:Marlon/40] [7:] [8:] [9:] [10:Joao/2] [11:Maria/5] 
r severino
Chave não encontrada para remoção.
r Severino
f
[0:REMOVIDO] [1:Barnabe/10] [2:Marcos/12] [3:Tiao/22] [4:] [5:Manoel/88] [6:Marlon/40] [7:] [8:] [9:] [10:Joao/2] [11:Maria/5] 
*/
#include <iostream>
#include <exception>

using namespace std;

// Estrutura para armazenar os dados de um processo
struct dado
{
    string assunto;
    string nomeInteressado;
    char tipo;
    int numeroProcesso;
};

// Sobrecarga dos operadores de comparação para a estrutura dado
bool operator==(const dado &d1, const dado &d2)
{
    return (d1.nomeInteressado == d2.nomeInteressado and d1.numeroProcesso == d2.numeroProcesso);
}

bool operator!=(const dado &d1, const dado &d2)
{
    return (d1.nomeInteressado != d2.nomeInteressado or d1.numeroProcesso != d2.numeroProcesso);
}

// Constantes utilizadas na tabela hash
const int UMPRIMO = 13;
const dado INVALIDO = {"", "", '1', -1};  // Dado inválido
const dado REMOVIDO = {"", "", '2', -2};  // Dado removido
const int POSINVALIDA = -1;  // Valor de posição inválido

// Classe para implementação da tabela hash com endereçamento aberto
class hashEA
{
private:
    unsigned posicao(const string &chave);  // Função de hash para calcular posição
    int buscarChave(const string &chave);   // Busca uma chave na tabela hash
    dado *vetDados;  // Vetor de dados (tabela hash)
    unsigned capacidade;  // Capacidade atual da tabela hash
    unsigned tamanho;     // Número de elementos na tabela hash

public:
    hashEA(unsigned cap = 50);  // Construtor (capacidade default: 50)
    ~hashEA();                  // Destrutor
    void imprimir();            // Imprime a tabela hash
    void inserir(const string &assunto, const string &interessado, const char &tipo, const int &valor);  // Insere um elemento na tabela
    void remover(const string &chave);   // Remove um elemento da tabela
    int consultar(const string &chave);  // Consulta um elemento na tabela
    void redimensiona();    // Redimensiona a tabela hash
};

// Implementação dos métodos da classe hashEA

// Construtor: inicializa a tabela com capacidade especificada (default: 50)
hashEA::hashEA(unsigned cap)
{
    capacidade = cap;
    vetDados = new dado[cap];
    for (unsigned i = 0; i < cap; i++)
        vetDados[i] = INVALIDO;  // Inicializa a tabela com dados inválidos
    tamanho = 0;
}

// Destrutor: libera a memória alocada para a tabela
hashEA::~hashEA()
{
    delete[] vetDados;
}

// Função de hash: retorna a posição de armazenamento de uma chave
unsigned hashEA::posicao(const string &chave)
{
    unsigned pos = 1;
    for (unsigned i = 0; i < chave.size(); i++)
        pos = UMPRIMO * pos + chave[i];  // Cálculo da posição usando uma função de hash simples
    return pos % capacidade;  // Retorna a posição ajustada à capacidade da tabela
}

// Busca uma chave na tabela hash
int hashEA::buscarChave(const string &chave)
{
    unsigned pos = posicao(chave);
    unsigned posFinal = pos;
    dado umDado;

    // Busca por sondagem linear
    do
    {
        umDado = vetDados[pos];
        if (umDado == INVALIDO)
            return POSINVALIDA;  // Retorna posição inválida se não encontrar a chave
        if (umDado.nomeInteressado == chave)
            return pos;  // Retorna a posição se encontrar a chave
        pos = (pos + 1) % capacidade;  // Próxima posição na tabela
    } while (pos != posFinal);

    return POSINVALIDA;  // Retorna posição inválida se não encontrar a chave
}

// Insere um elemento na tabela hash
void hashEA::inserir(const string &assunto, const string &interessado, const char &tipo, const int &valor)
{
    // Verificações antes da inserção
    if (interessado.empty())
        throw invalid_argument("Chave inválida.");  // Chave vazia não é permitida
    if (tamanho == capacidade)
        throw runtime_error("Tabela hash cheia.");  // Tabela cheia, não é possível inserir

    // Verifica se a chave já existe na tabela
    if (buscarChave(interessado) != POSINVALIDA)
        throw runtime_error("Inserção de chave que já existe.");

    unsigned pos = posicao(interessado);  // Calcula a posição para inserção
    while ((vetDados[pos] != INVALIDO) and (vetDados[pos] != REMOVIDO))
        pos = (pos + 1) % capacidade;  // Trata colisões por sondagem linear

    // Insere o novo elemento na posição encontrada
    vetDados[pos].assunto = assunto;
    vetDados[pos].nomeInteressado = interessado;
    vetDados[pos].tipo = tipo;
    vetDados[pos].numeroProcesso = valor;
    tamanho++;

    // Verifica se é necessário redimensionar a tabela
    if (tamanho >= 0.7 * capacidade)
        redimensiona();  // Redimensiona quando a ocupação atinge 70%
}

// Redimensiona a tabela hash
void hashEA::redimensiona()
{
    unsigned capAux = capacidade;  // Armazena a capacidade atual da tabela
    capacidade *= 2;                // Aumenta a capacidade da tabela em 100%
    dado *aux = new dado[capacidade];  // Cria um novo vetor de dados com a nova capacidade
    for (unsigned i = 0; i < capacidade; i++)
        aux[i] = INVALIDO;  // Inicializa o novo vetor com dados inválidos

    // Transfere os dados válidos da tabela antiga para a nova
    for (unsigned i = 0; i < capAux; i++)
    {
        if (vetDados[i] != INVALIDO and vetDados[i] != REMOVIDO)
        {
            unsigned pos = posicao(vetDados[i].nomeInteressado);  // Calcula a posição na nova tabela
            while ((aux[pos] != INVALIDO))
                pos = (pos + 1) % capacidade;  // Trata colisões por sondagem linear
            aux[pos] = vetDados[i];  // Insere o dado na nova tabela
        }
    }
    delete[] vetDados;  // Libera a memória ocupada pela tabela antiga
    vetDados = aux;     // Atualiza o ponteiro da tabela para apontar para a nova tabela
}

// Imprime a tabela hash
void hashEA::imprimir()
{
    for (unsigned i = 0; i < capacidade; ++i)
    {
        cout << '[' << i << ":";
        if (vetDados[i] != INVALIDO)
        {
            if (vetDados[i] == REMOVIDO)
                cout << "REMOVIDO";  // Indica que o elemento foi removido
            else
                cout << vetDados[i].nomeInteressado << '/' << vetDados[i].numeroProcesso;  // Imprime o elemento
        }
        cout << "] ";
    }
}

// Remove um elemento da tabela hash
void hashEA::remover(const string &chave)
{
    if (tamanho == 0)
        throw runtime_error("Impossível remover de hash vazia.");  // Não é possível remover de uma tabela vazia

    int pos = buscarChave(chave);  // Busca a posição da chave na tabela
    if (pos == POSINVALIDA)
        throw runtime_error("Chave não encontrada para remoção.");  // Chave não encontrada, não é possível remover

    vetDados[pos] = REMOVIDO;  // Marca o elemento como REMOVIDO
    tamanho--;  // Decrementa o tamanho da tabela
}

// Consulta um elemento na tabela hash
int hashEA::consultar(const std::string &chave)
{
    int pos = buscarChave(chave);  // Busca a posição da chave na tabela
    if (pos == POSINVALIDA)
        throw runtime_error("Chave não encontrada para consulta.");  // Chave não encontrada, não é possível consultar

    return vetDados[pos].numeroProcesso;  // Retorna o número do processo associado à chave
}

// Função principal
int main()
{
    hashEA tabela(6);  // Cria uma tabela hash com capacidade inicial de 6 posições
    char operacao;

    string assunto, interessado;
    char tipo;
    int valor;
    do
    {
        try
        {
            cin >> operacao;  // Lê a operação desejada
            switch (operacao)
            {
            case 'i':  // Inserir um elemento na tabela
                cin >> assunto >> interessado >> tipo >> valor;
                tabela.inserir(assunto, interessado, tipo, valor);
                break;
            case 'r':  // Remover um elemento da tabela
                cin >> interessado;
                tabela.remover(interessado);
                break;
            case 'l':  // Consultar um elemento na tabela
                cin >> interessado;
                valor = tabela.consultar(interessado);
                cout << valor << endl;
                break;
            case 'p':  // Imprimir a estrutura da tabela (debug)
                tabela.imprimir();
                cout << endl;
                break;
            case 'f':  // Finalizar o programa
                // Operação de finalização
                break;
            default:
                cerr << "operação inválida" << endl;  // Trata operações inválidas
            }
        }
        catch (exception &e)
        {
            cout << e.what() << endl;  // Captura e exibe exceções lançadas
        }
    } while (operacao != 'f');  // Loop continua até receber o comando de finalização

    tabela.imprimir();  // Imprime a tabela final antes de encerrar o programa
    return 0;  // Retorna 0 indicando sucesso
}
