/*
Implemente uma função que realize a remoção dos dados da estrutura pilha de um determinado tipo utilizando somente como estrutura auxiliar outra pilha.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Pilha com armazenamento em vetor - Lista de tarefas para robô doméstico" como base.

Entradas:

Com essa finalidade, você deverá adicionar mais um comando, como segue:

x seguido de um caracter: para remover os dados que possuem o determinado tipo.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: pilha vazia!
i sala s 150
i quarto1 q 45
i quarto2 q 60
i quarto3 q 45
i cozinha c 130
r
Nome: cozinha Tipo: c Valor: 130
i cozinha c 143
e
Nome: cozinha Tipo: c Valor: 143
i varanda v 111
i banheiro b 33
Erro: pilha cheia!
x q
f
Nome: varanda Tipo: v Valor: 111
Nome: cozinha Tipo: c Valor: 143
Nome: sala Tipo: s Valor: 150
*/

#include <iostream>

using namespace std;

typedef int Item;

const int max_itens = 100;

struct Item
{
     string nome;
     string tipo;
     int valor;
     Item *prox;
};

class Pilha
{
private:
     int tamanho;
     Item **estrutura; // Use a stack of pointers to Item objects

public:
     Pilha();
     ~Pilha();
     bool estaCheia();
     bool estaVazia();
     void inserir(Item *item); // Update the parameter type to Item*
     Item* remover(); // Update the return type to Item*
     void imprimir();
     Item limpar();
};

Pilha::Pilha()
{
     tamanho = 0;
     estrutura = new Item*[max_itens]; // Allocate memory for pointers to Item objects
}

Pilha::~Pilha()
{
     delete[] estrutura;
}

bool Pilha::estaCheia()
{
     return (tamanho == max_itens);
}

bool Pilha::estaVazia()
{
     return (tamanho == 0);
}

void Pilha::inserir(Item *item) // Update the parameter type to Item*
{
     if (estaCheia())
     {
          cout << "A pilha está cheia!\n";
     }
     else
     {
          estrutura[tamanho] = item;
          tamanho++;
     }
}

Item* Pilha::remover() // Update the return type to Item*
{
     if (estaVazia())
     {
          cout << "A pilha está vazia!\n";
          return nullptr;
     }
     else
     {
          tamanho--;
          return estrutura[tamanho];
     }
}

void Pilha::imprimir()
{
     if (!estaVazia())
     {
          for (int i = 0; i < tamanho; i++)
          {
               cout << " [ " << estrutura[i]->valor << " ] "; // Access the value of the Item object using the pointer
          }
     }
}

Item Pilha::limpar()
{
     while(!estaVazia())
     {
          remover();
     }
}

int main()
{
     Pilha p1;
     char opc;

     do
     {
          cin >> opc;
          switch (opc)
          {
          case 'i':
               Item* valorInserir = new Item(); // Create a new Item object
               cout << "Digite um valor para inserir: ";
               cin >> valorInserir->valor; // Read the value into valorInserir
               p1.inserir(valorInserir); // Pass the address of valorInserir to the inserir function
               break;
          case 'r':
               p1.remover();
               break;
          case 'f':
               p1.limpar();
          }

     } while (opc != 0);

     return 0;
}