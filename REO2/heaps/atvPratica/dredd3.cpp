/*
Modifique a sua estrutura heap para que considere a maior prioridade de execução de uma tarefa. No caso considere a tarefa com maior prioridade indicada pelo valor 1 e a medida que o valor aumenta a prioridade diminui. Implemente o método alteraPrioridade() nessa minheap. A alteração de prioridade implica que o dado alterado deva ser rearranjado, de forma a manter as propriedades do heap.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Heap - Organização de um robô domestico" como base.

Com essa finalidade, você deverá adicionar mais um comando, como segue:

a seguindo de uma string e um inteiro: altera a prioridade da atividade com o nome informado com o novo valor.
Exemplo de Entrada e Saída juntas:

10
r
Erro ao retirar raiz
p
Heap vazia!
i livingroom r 35 58 5
i tvroom t 18 28 8
i kitchen c 180 200 1
i bedroom1 x 99 90 2
i bedroom2 x 33 50 5
i bedroom3 v 56 80 8
i MasterBedroom x 56 70 9
i Bathroom1 n 32 56 7
i Bathroom2 n 44 80 5
i LaundryRoom h 15 7 1
i entrace a 10 5 2
Erro ao inserir
p
[kitchen/c/180/200/1] [LaundryRoom/h/15/7/1] [livingroom/r/35/58/5] [Bathroom2/n/44/80/5] [bedroom1/x/99/90/2] [bedroom3/v/56/80/8] [MasterBedroom/x/56/70/9] [tvroom/t/18/28/8] [Bathroom1/n/32/56/7]
[bedroom2/x/33/50/5]
a kitchen 5
p
[LaundryRoom/h/15/7/1] [bedroom1/x/99/90/2] [livingroom/r/35/58/5] [Bathroom2/n/44/80/5] [kitchen/c/180/200/5] [bedroom3/v/56/80/8] [MasterBedroom/x/56/70/9] [tvroom/t/18/28/8] [Bathroom1/n/32/56/7]
[bedroom2/x/33/50/5]
r
LaundryRoom
p
[bedroom1/x/99/90/2] [bedroom2/x/33/50/5] [livingroom/r/35/58/5] [Bathroom2/n/44/80/5] [kitchen/c/180/200/5] [bedroom3/v/56/80/8] [MasterBedroom/x/56/70/9] [tvroom/t/18/28/8] [Bathroom1/n/32/56/7]
f
*/

#include <iostream>
#include <utility>   // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado
{
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2)
{
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2)
{
    return d1.prioridade < d2.prioridade;
}

ostream &operator<<(ostream &output, const dado &d)
{
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade << "]";
    return output;
}

class MinHeap
{
private:
    dado *heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);

public:
    MinHeap(int cap);
    ~MinHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    int getTamanho();
    void alteraPrioridade(string nomeTarefa, int novaPrioridade);
};

MinHeap::MinHeap(int cap)
{
    capacidade = cap;
    heap = new dado[cap];
    tamanho = 0;
}

MinHeap::~MinHeap()
{
    capacidade = 0;
    delete[] heap;
}

int MinHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MinHeap::esquerdo(int i)
{
    return 2 * i + 1;
}

int MinHeap::direito(int i)
{
    return 2 * i + 2;
}

void MinHeap::corrigeDescendo(int i)
{
    int menor = i;       // Inicializa o menor como raiz
    int esq = 2 * i + 1; // esq = 2*i + 1
    int dir = 2 * i + 2; // dir = 2*i + 2

    // Se o filho da esquerda é menor que a raiz
    if (esq < tamanho)
    {
        if (heap[esq].prioridade < heap[menor].prioridade)
        {
            menor = esq;
        }
        else if (heap[esq].prioridade == heap[menor].prioridade)
        {
            menor = esq;
        }
    }

    // Se o filho da direita é menor que o menor até agora
    if (dir < tamanho)
    {
        if (heap[dir].prioridade < heap[menor].prioridade)
        {
            menor = dir;
        }
        else if (heap[dir].prioridade == heap[menor].prioridade)
        {
            menor = dir;
        }
    }

    // Se o menor não é a raiz
    if (menor != i)
    {
        swap(heap[i], heap[menor]);

        // Recursivamente corrige o sub-heap afetado
        corrigeDescendo(menor);
    }
}

void MinHeap::corrigeSubindo(int i)
{
    int p = pai(i);

    if (heap[i].prioridade < heap[p].prioridade)
    {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void MinHeap::imprime()
{
    if (tamanho > 0)
    {
        for (int i = 0; i < tamanho; i++)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Heap vazia!" << endl;
    }
}

dado MinHeap::retiraRaiz()
{
    if (tamanho <= 0)
        throw std::out_of_range("Heap vazio");

    if (tamanho == 1)
    {
        tamanho--;
        return heap[0];
    }

    // Armazena a raiz e a remove
    dado raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    corrigeDescendo(0);

    return raiz;
}

void MinHeap::insere(dado d)
{
    if (tamanho == capacidade)
    {
        cout << "Erro ao inserir" << endl;
    }
    else
    {
        heap[tamanho] = d;
        corrigeSubindo(tamanho);
        tamanho++;
    }
}

int MinHeap::getTamanho()
{
    return tamanho;
}

void MinHeap::alteraPrioridade(string nomeTarefa, int novaPrioridade)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (heap[i].nomeTarefa == nomeTarefa)
        {
            heap[i].prioridade = novaPrioridade;
            corrigeSubindo(i);
            corrigeDescendo(i);
        }
    }
}

int main()
{
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MinHeap meuHeap(capacidade);

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                meuHeap.insere(info);
                break;
            case 'r': // remover
                if (meuHeap.getTamanho() > 0)
                {
                    cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                }
                else
                {
                    cout << "Erro ao retirar raiz" << endl;
                }
                break;
            case 'p': // limpar tudo
                meuHeap.imprime();
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            case 'a': // alterar prioridade
                cin >> info.nomeTarefa;
                int novaPrioridade;
                cin >> novaPrioridade;
                meuHeap.alteraPrioridade(info.nomeTarefa, novaPrioridade);
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
    cout << endl;
    return 0;
}