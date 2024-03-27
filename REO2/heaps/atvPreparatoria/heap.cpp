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
    return d1.energiaGasta > d2.energiaGasta;
}

bool operator<(dado d1, dado d2)
{
    return d1.energiaGasta < d2.energiaGasta;
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
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    if (esq < tamanho && heap[esq] > heap[maior])
    {
        maior = esq;
    }

    if (dir < tamanho && heap[dir] > heap[maior])
    {
        maior = dir;
    }

    if (maior != i)
    {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i)
{
    int p = pai(i);

    if (heap[i] > heap[p])
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
    dado aux = heap[0];
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
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