#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class noh{
     friend class lista;
     private:
          const Dado dado;
          noh* proximo;
     public:
          noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d){
     proximo = NULL;
}

class lista{
     private:
          noh* primeiro;
          noh* ultimo;
          int tamanho;
          void removeTodos();
          void imprimeReversoAux(noh* umNoh);
     public:
          lista();
          lista(const lista& umaLista);
          ~lista();
          lista& operator=(const lista& umaLista);
          inline void insere(Dado dado);
          void insereNoInicio(Dado dado);
          void insereNaPosicao(int posicao, Dado dado);
          void insereNoFim(Dado dado);
          int procura(Dado valor);
          void imprime();
          void imprimeReverso();
          inline bool vazia();

          void removeNoInicio();
          void removeNoFim();
};
 
lista::lista(){
     tamanho = 0;
     primeiro = NULL;
     ultimo = NULL;
}
//construtor de copia
lista::lista(const lista& umaLista){
     tamanho = 0;
     primeiro = NULL;
     ultimo = NULL;
     
     noh* aux = umaLista.primeiro;

     while(aux != NULL){
          insereNoFim(aux->dado);
          aux = aux->proximo;
     }
}
//destrutor
lista::~lista(){
     removeTodos();
}

void lista::removeTodos(){
     noh* aux = primeiro;
     noh* temp;

     while(aux != NULL){
          temp = aux;
          aux = aux->proximo;
          delete temp;
     }
     tamanho = 0;
     primeiro = NULL;
     ultimo = NULL;    
}

lista& lista::operator=(const lista& umaLista){
     //limpa a lista atual
     removeTodos();

     //precorre a lista recebida como parametro, copiando os dados
     noh*  aux = umaLista.primeiro;

     while(aux != NULL){
          insereNoFim(aux->dado);
          aux = aux ->proximo;
     }

     return *this;
}

void lista::insere(Dado dado){
     insereNoFim(dado);
}

void lista::insereNoFim(Dado dado){
     noh* novo = new noh(dado);

     if(vazia()){
          primeiro = novo;
          ultimo = novo;
     }
     else{
          ultimo->proximo = novo;
          ultimo = novo;
     }   
     tamanho++;
}

void lista::insereNoInicio(Dado dado){
     noh* novo = new noh(dado);

     if(vazia()){
          primeiro = novo;
          ultimo = novo;
     } else{
          novo->proximo = primeiro;
          primeiro = novo;
     }
     tamanho++;
}

void lista::insereNaPosicao(int posicao, Dado dado){
     noh* novo = new noh(dado);

     if(posicao <= tamanho && posicao >=0){
          if(vazia()){
               primeiro = novo;
               ultimo = novo;
          }else if(posicao == 0){
               novo->proximo = primeiro;
               primeiro = novo;
          }else if(posicao == tamanho){
               ultimo->proximo = novo;
               ultimo = novo;
          }else{
               noh* aux = primeiro;
               int posAux = 0;
               while (posAux < (posicao-1)){
                    aux = aux->proximo;
                    posAux++;
               }
               novo->proximo = aux->proximo;
               aux->proximo = novo;
               tamanho++;
          }
     }else{
          cerr << "Posicao inexistente!" << endl;
          exit(EXIT_FAILURE);
     }
}

int lista::procura(Dado valor){
     noh* aux = primeiro;
     int posAux = 0;
     while(aux != NULL && aux->dado != valor){
          posAux++;
          aux = aux->proximo;
     }
     if(aux == NULL){
          posAux = -1;
     }

     return posAux;
}

void lista::imprimeReverso(){
     imprimeReversoAux(primeiro);
     cout << endl;
}

void lista::imprimeReversoAux(noh* umNoh){
     if(umNoh != NULL){
          imprimeReversoAux(umNoh->proximo);
          cout << umNoh->dado << " ";
     }
}

inline bool lista::vazia(){
     return (primeiro == NULL);
}

void lista::imprime(){
     noh* aux = primeiro;

     while(aux != NULL){
          cout << aux->dado << " ";
          aux = aux->proximo;
     }
     cout << endl;
}



void lista::removeNoFim(){
     if(vazia()){
          cerr << "Remocao em lista vazia!" << endl;
          exit(EXIT_FAILURE);
     }

     noh* aux = primeiro;
     noh* anterior;
     while(aux->proximo != NULL){
          anterior = aux;
          aux = aux->proximo;
     }

     delete ultimo;
     anterior->proximo = NULL;
     ultimo = anterior;
     tamanho--;
     if(vazia()) primeiro = NULL;
}

void lista::removeNoInicio(){
      if(vazia()){
          cerr << "Remoção em lista vazia!" << endl;
          exit(EXIT_FAILURE);
     }

     noh* removido = primeiro;
     primeiro = primeiro->proximo;
     delete removido;
     tamanho--;
     if (tamanho == 0) primeiro = NULL;
}

int main(){
     lista minhaLista;
     cout << "**Teste da lista**" << endl;
     cout << "Quantidade de valores a inserir: " << endl;

     int valor;
     int num;
     cin >> num;
     for(int i=0; i < num; i++){
          cin >> valor;
          minhaLista.insere(valor);
     }
     minhaLista.imprime();

     minhaLista.insereNoInicio(18);
     minhaLista.insereNaPosicao(3,25);
     minhaLista.imprime();
     minhaLista.imprimeReverso();
     
     cout << minhaLista.procura(0) << endl;
     cout << minhaLista.procura(50)<< endl;
     cout << minhaLista.procura(12)<< endl;

     //contrutor de copia
     cout << "Sobrecarga do construtor de copia" << endl;
     lista outraLista(minhaLista);
     outraLista.imprime();
     outraLista.imprimeReverso();

     //sobrecarga do operador de atribuicao
     cout << "Sobrecarga do operador de atribuicao" << endl;
     lista maisUmaLista;
     maisUmaLista = outraLista;

     maisUmaLista.imprime();
     maisUmaLista.imprimeReverso();


     maisUmaLista.removeNoFim();
     maisUmaLista.removeNoFim();

     maisUmaLista.imprime();
     maisUmaLista.imprimeReverso();


     maisUmaLista.removeNoInicio();
     maisUmaLista.removeNoInicio();

     maisUmaLista.imprime();
     maisUmaLista.imprimeReverso();

     return 0;
}