/*
A agência bancária decidiu contratar uma pessoa para fazer o programa que gerencia as senhas de atendimento nos caixas expressos. Você será responsável por essa implementação e as instruções passadas a você são: existem dois tipos de senha, as prioritárias e as normais; as senhas são chamadas de modo a serem chamadas 3 prioritárias para então uma normal. Não havendo prioridades, as pessoas com senha normal podem ser atendidas normalmente. Sempre que um atendimento normal for realizado, os próximos três devem ser prioritários, se possível. Se estiver na hora de realizar um atendimento de cliente normal mas não houver nenhum cliente normal, deve ser chamado um nome do atendimento preferencial, se houver. Você deverá usar uma estrutura de dados do tipo fila e poderá usar código fornecido.

O programa deve ler comandos representados por palavras e seus respectivos argumentos assim:

O comando "normal" seguido de um nome (sem espaços) representa retirada de uma senha normal, ou seja, uma pessoa entrou na fila "normal".
O comando "prioridade" seguido de um nome (sem espaços) representa retirada de uma senha prioritária, ou seja, uma pessoa entrou na fila "prioridade".
O comando "atender" representa uma senha sendo chamada.
O comando "fim" solicita o fim da execução do programa.
Para cada comando de atendimento, o programa deverá escrever o nome da pessoa que deve ser atendida, de acordo com as regras de atendimento vistas. Caso não haja cliente a ser chamado, o programa deve escrever "AGUARDE" (letras maiúsculas). A cada atendimento normal, a contagem para prioritários deve ser reiniciada.

Entradas:

Sequência de comandos, seguindo as instruções acima.
Saídas:

Somente o comando "atender" gera saída, conforme instruções acima.
Exemplo de Entrada:

normal Abner
prioridade Ackson
normal Adilson
normal Adriana
normal Adriano
normal Adriel
prioridade Adrielle
atender
atender
atender
atender
prioridade Adriene
prioridade Adson
prioridade Afonso
prioridade Agatha
atender
atender
atender
atender
atender
fim
Exemplo de Saída:

Ackson
Adrielle
Abner
Adilson
Adriene
Adson
Afonso
Adriana
Agatha
*/
/* Código base para estrutura de dados Fila
 *
 * by Juliana Galvani Greghi
 *                                nov/2018
 */

#include <iostream>
using namespace std;

class noh
{
  friend class fila;

private:
  string mnome;
  noh *nProximo;

public:
  noh(string nome);
};

noh::noh(string nome)
{
  mnome = nome;
  nProximo = NULL;
}

class fila
{
private:
  noh *mInicio;
  noh *mFim;
  int mTamanho;

public:
  fila();
  ~fila();
  int tamanho();
  void enfileira(string nome);
  string desenfileira();
  void limpaFila();
  bool vazia();
};

fila::fila()
{
  mInicio = NULL;
  mFim = NULL;
  mTamanho = 0;
}

fila::~fila()
{
  limpaFila();
}

void fila::limpaFila()
{
  while (!vazia())
  {
    desenfileira();
  };
}

int fila::tamanho()
{
  return mTamanho;
}

bool fila::vazia()
{
  return (mTamanho == 0);
}

void fila::enfileira(string nome)
{
  noh *novo = new noh(nome);
  if (mTamanho == 0)
  {
    mInicio = novo;
  }
  else
  {
    mFim->nProximo = novo;
  }
  mFim = novo;
  mTamanho++;
}

string fila::desenfileira()
{
  string nome = mInicio->mnome;
  noh *temp = mInicio;
  mInicio = mInicio->nProximo;
  delete temp;
  mTamanho--;
  if (mTamanho == 0)
  {
    mFim = NULL;
  }
  return nome;
}
 
int main()
{
    fila filaNormal;   
    fila filaPrioritaria;
    string nome;
    string comando;
    int contador = 0;
    while (comando != "fim")
    {
        cin >> comando;
        if (comando == "normal")
        {
            cin >> nome;
            filaNormal.enfileira(nome);
        }
        else if (comando == "prioridade")
        {
            cin >> nome;
            filaPrioritaria.enfileira(nome);
        }
        else if (comando == "atender")
        {
            if (!filaPrioritaria.vazia())
            {
                cout << filaPrioritaria.desenfileira() << endl;
                contador++;
                if (contador == 3)
                {
                    contador = 0;
                    if (!filaNormal.vazia())
                    {
                        cout << filaNormal.desenfileira() << endl;
                    }
                    else
                    {
                        cout << "AGUARDE" << endl;
                    }
                }
            }
            else
            {
                if (!filaNormal.vazia())
                {
                    cout << filaNormal.desenfileira() << endl;
                }
                else
                {
                    cout << "AGUARDE" << endl;
                }
            }
        }
    }
  

  return 0;
}