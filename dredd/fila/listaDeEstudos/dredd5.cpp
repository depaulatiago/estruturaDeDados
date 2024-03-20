/*
Implemente uma estrutura do tipo fila com as operações básicas de inserção e remoção. Com a estrutura implementada, 
faça um programa que utilize a fila para gerar números binários de 1 a N.
 O trecho a seguir dá uma dica de como resolver o problema:

inicio = "1"
enfileira (inicio) // fila = (1)
laço
	enfileira(inicio + “0”) // fila = (1, 10)
	enfileira(inicio + “1”) // fila(1, 10, 11)
	elemento = desenfileira() 
fim  do laço
Note que como cada passo do laço enfileira por padrão dois elementos, você precisará inserir um controle
 adicional no laço ou na impressão para evitar enfileirar um elemento a mais, dependendo da entrada.

Entradas:

Número inteiro positivo representando N
Saídas:

Números binários gerados de 1 a N
Exemplo de Entrada:

6
Exemplo de Saída:

1 10 11 100 101 110
*/
#include <iostream>
using namespace std;

class noh {
	friend class fila;
	private:
		int dado;
		noh* prox;
};

class fila {
	private:
		noh* inicio;
		noh* fim;
		int tamanho;
	public:
		fila();
		~fila();
		void enfileira(int d);
		int desenfileira();
		bool vazia();
		void imprime();
};

fila::fila() {
	inicio = NULL;
	fim = NULL;
	tamanho = 0;
}

fila::~fila() {
	while (inicio != NULL) {
		desenfileira();
	}
}

void fila::enfileira(int d) {
	noh* temp = new noh;
	temp->dado = d;
	temp->prox = NULL;
	if (fim != NULL) {
		fim->prox = temp;
	}
	fim = temp;
	if (inicio == NULL) {
		inicio = temp;
	}
	tamanho++;
}

int fila::desenfileira() {
	int removido;
	noh* temp;
	removido = inicio->dado;
	temp = inicio;
	inicio = inicio->prox;
	if (inicio == NULL) {
		fim = NULL;
	}
	delete temp;
	tamanho--;
	return removido;
}

bool fila::vazia() {
	return (inicio == NULL);
}

void fila::imprime() {
	noh* temp = inicio;
	while (temp != NULL) {
		cout << temp->dado << " ";
		temp = temp->prox;
	}
	cout << endl;
}

int main() {
	fila f;
	int n;
	cin >> n;
	f.enfileira(1);
	for (int i = 0; i < n; i++) {
		int temp = f.desenfileira();
		cout << temp << " ";
		f.enfileira(temp * 10);
		f.enfileira(temp * 10 + 1);
	}
	cout << endl;
	return 0;
}
