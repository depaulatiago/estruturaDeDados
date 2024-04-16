/*
Utilizando listas encadeadas, faça um programa que representa o processo de soma de dígitos. Por exemplo, quando você soma 347 com 594, o 4 soma com o 7, dando 11. Fica 1 na última posição, indo 1 para somar com 9 e 4, dando 14. Fica 4 na segunda posição, e vai 1 para somar com 3 e 5, totalizando 8. E então, você tem como resultado 841.

Computacionalmente, esse processo é realizado de uma maneira mais fácil se você usar uma lista e considerar que os números estão invertidos. Assim, crie um programa que dada duas listas em que cada nó possui um único dígito, crie uma terceira que seja a soma das duas. As listas são dinâmicas e simplesmente encadeadas. As listas de entrada possuem pelo menos um elemento.
Entradas:

elementos da lista 1 (-1 indica término da lista)
elementos da lista 2 (-1 indica término da lista)
Saídas:

Lista 3
Exemplo de Entrada:

1 2 3 4 5 -1
6 7 8 9 -1
Exemplo de Saída:

7 9 1 4 6
*/

#include <iostream>
using namespace std;

struct Noh {
    int data;
    Noh* next;
};

class Lista {
public:
    Lista() {
        head = nullptr;
    }
    Noh* head;

    void inserir(int valor) {
        Noh* novoNoh = new Noh;
        novoNoh->data = valor;
        novoNoh->next = nullptr;

        if (head == nullptr) {
            head = novoNoh;
        } else {
            Noh* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = novoNoh;
        }
    }

    void imprimir() {
        Noh* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    Lista lista1;
    Lista lista2;
    Lista lista3;

    int valor;
    cin >> valor;
    while (valor != -1) {
        lista1.inserir(valor);
        cin >> valor;
    }

    cin >> valor;

    while (valor != -1) {
        lista2.inserir(valor);
        cin >> valor;
    }

    Noh* temp1 = lista1.head;
    Noh* temp2 = lista2.head;
    int carry = 0;
    while (temp1 != nullptr || temp2 != nullptr) {
        int soma = carry;
        if (temp1 != nullptr) {
            soma += temp1->data;
            temp1 = temp1->next;
        }
        if (temp2 != nullptr) {
            soma += temp2->data;
            temp2 = temp2->next;
        }
        carry = soma / 10;
        soma = soma % 10;
        lista3.inserir(soma);
    }
    if (carry > 0) {
        lista3.inserir(carry);
    }

    lista3.imprimir();

    return 0;
}