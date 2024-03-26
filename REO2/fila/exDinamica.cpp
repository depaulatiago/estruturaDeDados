#include <iostream>
using namespace std;

class noh
{
  friend class fila;

private:
  int nValor;
  noh *nProximo;

public:
  noh(int valor);
};

noh::noh(int valor)
{
  nValor = valor;
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
  int tamanho(); // usa para dar somente positivos
  void enfileira(int valor);
  int desenfileira();
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

void fila::enfileira(int valor)
{
  noh *novo = new noh(valor);
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

int fila::desenfileira()
{
  int valor = mInicio->nValor;
  noh *temp = mInicio;
  mInicio = mInicio->nProximo;
  delete temp;
  mTamanho--;
  if (mTamanho == 0)
  {
    mFim = NULL;
  }
  return valor;
}
 
int main()
{
  fila f1;
  int num;

  cin >> num;

  while (num >= 0)
  {
    f1.enfileira(num);
    cin >> num;
  }

  cout << "Tamanho: " << f1.tamanho() << endl;

  cout << "Elementos:" << endl;

  while (!f1.vazia())
  {
    cout << f1.desenfileira() << " ";
  }

  cout << endl;

  return 0;
}