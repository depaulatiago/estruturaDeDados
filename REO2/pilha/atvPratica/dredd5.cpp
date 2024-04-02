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

typedef int TipoItem;

const int max_itens = 100;

class Pilha
{
private:
     int tamanho;
     int *estrutura;

public:
     Pilha();
     ~Pilha();
     bool estaCheia();
     bool estaVazia();
     void inserir(TipoItem item);
     TipoItem remover();
     void imprimir();
};

Pilha::Pilha()
{
     tamanho = 0;
     estrutura = new TipoItem[max_itens];
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

void Pilha::inserir(TipoItem item)
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

TipoItem Pilha::remover()
{
     if (estaVazia())
     {
          cout << "A pilha está vazia!\n";
          return 0;
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
               cout << " [ " << estrutura[i] << " ] ";
          }
     }
}

int main()
{
     Pilha p1;
     int opc;

     do
     {
          cout << "0 - Sair\n";
          cout << "1 - Inserir\n";
          cout << "2 - Remover\n";
          cout << "3 - Imprimir\n";
          cin >> opc;
          switch (opc)
          {
          case 1:
               TipoItem valorInserir;
               cout << "Digite um valor para inserir: ";
               cin >> valorInserir;
               p1.inserir(valorInserir);
               break;
          case 2:
               p1.remover();
               break;
          case 3:
               p1.imprimir();
               break;
          default:
               opc = 0;
               break;
          }

     } while (opc != 0);

     return 0;
}