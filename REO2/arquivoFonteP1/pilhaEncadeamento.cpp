/*

Implemente uma função que realize a remoção dos jogos com valores superiores a um valor informado,
denominada remoção especial. Você poderá utilizar somente como estrutura auxiliar outra pilha.
Os demais valores da pilha devem permanecer na posição original. Os valores removidos devem ser
impressos no momento da remoção.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Pilha com encadeamento -
Inventário de itens de jogo" como base.

Entradas:

Com essa finalidade, você deverá adicionar mais um comando, como segue:

    x: seguido de um inteiro: para remover (e imprimir) todos os elementos com valor superior ao
    informado

Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente
falta implementar a chamada para a remoção especial. Ao terminar a execução do programa, todos os
itens da pilha são desempilhados e escritos.

Exemplo de Entrada e Saída juntas:

r
Erro: pilha vazia!
i um a 1
i dois b 2
i dez j 10
i quatro d 4
i sete g 7
i oito h 8
r
Nome: oito Tipo: h Valor: 8
e
Nome: sete Tipo: g Valor: 7
x 4
Nome: sete Tipo: g Valor: 7
Nome: dez Tipo: j Valor: 10
f
Nome: quatro Tipo: d Valor: 4
Nome: dois Tipo: b Valor: 2
Nome: um Tipo: a Valor: 1

*/

#include <iostream>

using namespace std;

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
    Item *topo;
    int tamanho;

public:
    bool vazia(Pilha *pilha)
    {
        if (pilha->topo == NULL)
        {
            return true;
        }
        else
            return false;
    }

    string imprime(string nome, string tipo, int valor)
    {
        return "Nome: " + nome + " Tipo: " + tipo + " Valor: " + to_string(valor);
    }

    void inicializar(Pilha *pilha)
    {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }

    void empilhar(Pilha *pilha, string nome, string tipo, int valor)
    {
        Item *novo = new Item;
        novo->nome = nome;
        novo->tipo = tipo;
        novo->valor = valor;
        novo->prox = pilha->topo;
        pilha->topo = novo;
        pilha->tamanho++;
    }

    void desempilhar(Pilha *pilha)
    {
        if (vazia(pilha))
        {
            cout << "Erro: pilha vazia!" << endl;
        }
        else
        {
            Item *aux = pilha->topo;
            pilha->topo = pilha->topo->prox;
            cout << imprime(aux->nome, aux->tipo, aux->valor);
            cout << endl;
            delete aux;
            pilha->tamanho--;
        }
    }

    void espiar(Pilha *pilha)
    {
        if (vazia(pilha))
        {
            cout << "Erro: pilha vazia!" << endl;
        }
        else
        {
            cout << imprime(pilha->topo->nome, pilha->topo->tipo, pilha->topo->valor);
            cout << endl;
        }
    }
    void removerEspecial(Pilha *pilha, int valor)
    {
        Pilha aux;
        inicializar(&aux);
        while (!vazia(pilha))
        {
            if (pilha->topo->valor > valor)
            {
                Item *removido = pilha->topo;
                pilha->topo = pilha->topo->prox;
                cout << imprime(removido->nome, removido->tipo, removido->valor);
                cout << endl;
                delete removido;
                pilha->tamanho--;
            }
            else
            {
                Item *novo = new Item;
                novo->nome = pilha->topo->nome;
                novo->tipo = pilha->topo->tipo;
                novo->valor = pilha->topo->valor;
                novo->prox = aux.topo;
                aux.topo = novo;
                aux.tamanho++;
                Item *removido = pilha->topo;
                pilha->topo = pilha->topo->prox;
                delete removido;
                pilha->tamanho--;
            }
        }
        while (aux.topo != NULL)
        {
            Item *novo = new Item;
            novo->nome = aux.topo->nome;
            novo->tipo = aux.topo->tipo;
            novo->valor = aux.topo->valor;
            novo->prox = pilha->topo;
            pilha->topo = novo;
            pilha->tamanho++;
            Item *removido = aux.topo;
            aux.topo = aux.topo->prox;
            delete removido;
            aux.tamanho--;
        }
    }
};

int main()
{
    Pilha pilha;
    pilha.inicializar(&pilha);
    char comando;
    string nome, tipo;
    int valor;
    while (cin >> comando)
    {
        switch (comando)
        {
        case 'i':
        {
            cin >> nome >> tipo >> valor;
            pilha.empilhar(&pilha, nome, tipo, valor);
            break;
        }
        case 'r':
        {
            pilha.desempilhar(&pilha);
            break;
        }
        case 'x':
        {
            cin >> valor;
            pilha.removerEspecial(&pilha, valor);
            break;
        }
        case 'e':
        {
            pilha.espiar(&pilha);
            break;
        }
        case 'f':
        {
            while (!pilha.vazia(&pilha))
            {
                pilha.desempilhar(&pilha);
            }
            return 0;
        }
        }
    }
    return 0;
}