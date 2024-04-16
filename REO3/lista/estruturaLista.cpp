#include <iostream>

struct Noh {
    int data;
    Noh* next;
};

class Lista {
private:
    Noh* head;
public:
    Lista() {
        head = nullptr;
    }

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
    Lista lista;
    lista.inserir(1);
    lista.inserir(2);
    lista.inserir(3);
    lista.imprimir();

    return 0;
}