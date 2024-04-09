/*Implemente uma estrutura de dados pilha, utilizando armazenamento em vetor, para implementar uma lista de tarefas para um robô 
doméstico. A estrutura deve possibilitar, pelo menos, as seguintes ações: empilhamento e desempilhamento de itens, verificação do 
item no topo da pilha e limpeza da lista de afazeres (remoção de todos os elementos da pilha). O desempilhamento deve escrever
mensagem de erro na saída ("Erro: pilha vazia!"), quando a pilha já estiver vazia. O empilhamento também deve gerar mensagem de erro 
("Erro: pilha cheia!"), quanto todas as posições do vetor estiverem ocupadas. Os itens da lista de tarefas possuem os seguintes
atributos: nome (uma string sem espaços), tipo (um único caracter) e tempo de execução em minutos (um inteiro). Além disso, 
sabe-se que esse robô tem capacidade de memória limitada para no máximo seis tarefas.

Entradas:

O programa deve aceitar os seguintes comandos:

i seguido de uma string, um caracter e um inteiro: para inserir um item na lista de tarefas
r: para retirar um item da lista de tarefas
l: para limpar (remover todos) os itens da lista de tarefas
e: para espiar o topo da lista de tarefas (escreve o topo sem removê-lo)
f: para finalizar a execução do programa
Antes dos comandos, o programa recebe a capacidade de armazenamento da pilha.*/

/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1; //Inicializa o topo como -1 (Pilha Vazia)
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer. 
void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado* mPilha; //Vetor para armazenar os elementos
        int posTopo;

    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        Dado Desempilhar(); 
        // Insere um elemento na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
};

Pilha::Pilha(){
    mPilha = new Dado[TAMANHOPILHA];
    posTopo = PILHAVAZIA;
}

Pilha::~Pilha() {
    delete[] mPilha;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Dado valor = mPilha[posTopo];
    posTopo--;
    return valor;
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: pilha cheia!");
    posTopo++;
    mPilha[posTopo] = d;
}

void Pilha::LimparTudo() {
    posTopo = PILHAVAZIA;
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    cout << "Nome: " << mPilha[posTopo].nome << " Tipo: " << mPilha[posTopo].tipo << " Valor: " << mPilha[posTopo].valor << endl;
}

bool Pilha::Vazia() {
    return posTopo == PILHAVAZIA;
}

bool Pilha::Cheia() {
    return posTopo == TAMANHOPILHA -1;
}
int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!pilha.Vazia())               
                        pilha.Topo();
                    else
                        cout << " Pilha vazia!"<< endl;
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}