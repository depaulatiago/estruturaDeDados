/*
Implemente uma tabela hash, utilizando tratamento de colisão por encadeamento de nós, para implementar um inventário de itens em um jogo digital. A estrutura deve possibilitar, pelo menos, as seguintes ações: inserção e remoção de itens, localizar um item na estrutura hash. A remoção e busca devem escrever mensagem de erro na saída ("Erro: hash vazia!"), quando a hash estiver vazia. Na remoção ou na busca, caso a hash contenha elementos mas o item da busca não se encontra na tabela, o usuário deve ser informado da seguinte forma: ("Elemento inexistente!") . Os itens do inventários possuem os seguintes atributos: nome (uma string sem espaços), tipo (um único caracter) e valor (um inteiro).

Para essa atividade você pode utilizar as seguintes opções de código fonte base: código fornecido 1 ou código fornecido2.

No início da execução, o programa lê o tamanho da tabela hash.

Entradas:

O programa deve aceitar os seguintes comandos:

i: seguido de uma string, um caracter e um inteiro: para inserir um item no inventário. Caso exista colisão, a inserção na lista deve ser no ínicio.
r seguido de um string: para retirar um item do inventário
l seguido de um string: para localizar o determinado item no inventário
p: imprimir toda a tabela hash
f: para finalizar a execução do programa
Saídas:

Todas as saídas de comandos já estão implementadas na função principal dos códigos fontes informados anteriormente. Ao terminar a execução do programa, todos os itens da hash são escritos.

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
l quatro
Tipo: d Valor: 4
r dez
f
0:
1: [sete/7]
2: [tres/3][quatro/4]
3:
4: [um/1]
5: [oito/8][dois/2]
*/

/*
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
 */

/*
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
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
    }
    // Remove o noh com dada chave da lista.
    // Se a chave não existe, retorna informação.
    bool remove(const string &c)
    {
    }
    // Busca um elemento na lista, retorna falso se não encontrado
    // o valor buscado é retornado por passagem por referência
    // na variável valorBuscado
    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {
    }
    // Verifica se já tem algum dado na lista com
    // uma dada chave
    bool verificaOcorrencia(const string &c)
    {
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
    tabelaHash(unsigned cap = 100) {}
    ~tabelaHash() {}
    // Insere um nó com dada chave e valor.
    bool insere(const string &c, char &t, const int &v) {
        
    }
    // Retorna um valor associado a uma dada chave.
    // Se a chave não existe, retorna "NÃO ENCONTRADO!".
    bool valor(const string &c, char &tipoBuscado, int &valorRetorno) {}
    // Retira do hash um nó com dada chave.
    bool remove(const string &c) {}
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
                if (not tabela.insere(chave, tipo, valor))
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