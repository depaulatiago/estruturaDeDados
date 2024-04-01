/*
Modifique a sua estrutura heap para que considere a maior prioridade de execução de uma tarefa. No caso considere a tarefa com maior prioridade indicada pelo maior valor e a medida que o valor diminui a prioridade diminui. Implemente o método alteraPrioridade() nessa maxheap. A alteração de prioridade implica que o dado alterado deva ser rearranjado, de forma a manter as propriedades do heap.

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
[MasterBedroom/x/56/70/9] [Bathroom1/n/32/56/7] [tvroom/t/18/28/8] [livingroom/r/35/58/5] [bedroom2/x/33/50/5] [kitchen/c/180/200/1] [bedroom3/v/56/80/8] [bedroom1/x/99/90/2] [Bathroom2/n/44/80/5] [LaundryRoom/h/15/7/1]
a MasterBedroom 5
p
[tvroom/t/18/28/8] [Bathroom1/n/32/56/7] [bedroom3/v/56/80/8] [livingroom/r/35/58/5] [bedroom2/x/33/50/5] [kitchen/c/180/200/1] [MasterBedroom/x/56/70/5] [bedroom1/x/99/90/2] [Bathroom2/n/44/80/5] [LaundryRoom/h/15/7/1]
r
tvroom
p
[bedroom3/v/56/80/8] [Bathroom1/n/32/56/7] [MasterBedroom/x/56/70/5] [livingroom/r/35/58/5] [bedroom2/x/33/50/5] [kitchen/c/180/200/1] [LaundryRoom/h/15/7/1] [bedroom1/x/99/90/2] [Bathroom2/n/44/80/5]
f
*/

/*
Questão 1: Heap - Organização de um robô domestico
Uma empresa desenvolveu um robô de limpeza domestica e precisa que você desenvolva uma um sistema para robô saber qual tarefa ele deve resolver. Você deve considerar como característica: nome da tarefa, tipo da tarefa, a quantidade de energia gasta pela atividade, o tempo estimado para a atividade ser realizada e prioridade.
Com seus conhecimentos de Estrutura de Dados, implemente uma estrutura para definir corretamente qual tarefa ele deve executar. Para este caso, você deve considerar a maior quantidade de energia gasta pela atividade como fator principal para a limpeza do local. Você poderá utilizar o
código fornecido
como base de implementação.
Comandos de utilização do programa:
i: inserir uma nova atividade, seguido de uma string (nome da tarefa), um carácter (tipo da tarefa), três inteiros (a quantidade de energia gasta pela atividade, o tempo estimado para a atividade ser realizada e a prioridade, respectivamente) das tarefas.
r: obter a atividade que deverá ser tratada. Causa a retirada da atividade mais prioritário do sistema e o programa escreve seu nome. Caso não tenha uma atividade para ser realizada, o programa escreve "
Erro ao retirar raiz
".
p: imprime a estrutura.
f: sair do programa.
No início da execução, o programa lê a capacidade máxima de atividades para trabalhar. Caso o usuário tente inserir um elemento além da capacidade máxima informada, informe a seguinte mensagem de erro: "
Erro ao inserir
" .Em seguida começa a processar os comandos acima.
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
p
[kitchen/c/180/200/1] [bedroom1/x/99/90/2] [bedroom3/v/56/80/8] [tvroom/t/18/28/8] [bedroom2/x/33/50/5] [livingroom/r/35/58/5]
r
kitchen
p
[bedroom1/x/99/90/2] [livingroom/r/35/58/5] [bedroom3/v/56/80/8] [tvroom/t/18/28/8] [bedroom2/x/33/50/5]
f
*/

/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2024 by Lucas
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

class MaxHeap
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
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    int getTamanho();
    void alteraPrioridade(string nomeTarefa, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap)
{
    capacidade = cap;
    heap = new dado[cap];
    tamanho = 0;
}

MaxHeap::~MaxHeap()
{
    capacidade = 0;
    delete[] heap;
}

int MaxHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MaxHeap::esquerdo(int i)
{
    return 2 * i + 1;
}

int MaxHeap::direito(int i)
{
    return 2 * i + 2;
}

void MaxHeap::corrigeDescendo(int i)
{
    int maior = i;       // Inicializa o maior como raiz
    int esq = 2 * i + 1; // esq = 2*i + 1
    int dir = 2 * i + 2; // dir = 2*i + 2

    // Se o filho da esquerda é maior que a raiz
    if (esq < tamanho)
    {
        if (heap[esq].prioridade > heap[maior].prioridade)
        {
            maior = esq;
        }
        else if (heap[esq].prioridade == heap[maior].prioridade)
        {
            maior = esq;
        }
    }

    // Se o filho da direita é maior que o maior até agora
    if (dir < tamanho)
    {
        if (heap[dir].prioridade > heap[maior].prioridade)
        {
            maior = dir;
        }
        else if (heap[dir].prioridade == heap[maior].prioridade)
        {
            maior = dir;
        }
    }

    // Se o maior não é a raiz
    if (maior != i)
    {
        swap(heap[i], heap[maior]);

        // Recursivamente corrige o sub-heap afetado
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i)
{
    int p = pai(i);

    if (heap[i].prioridade > heap[p].prioridade)
    {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void MaxHeap::imprime()
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

dado MaxHeap::retiraRaiz()
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

void MaxHeap::insere(dado d)
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

int MaxHeap::getTamanho()
{
    return tamanho;
}

void MaxHeap::alteraPrioridade(string nomeTarefa, int novaPrioridade)
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
    MaxHeap meuHeap(capacidade);

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