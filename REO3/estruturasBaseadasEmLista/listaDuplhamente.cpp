#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class noh{
     friend class listadup;
     private:
          const Dado dado;
          noh* proximo;
          noh* anterior;

     public:
          noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d){
     proximo = NULL;
     anterior = NULL;
}

class listadup{
     private:
          noh* primeiro;
          noh* ultimo;
          int tamanho;
          void removeTodos();
          void imprimeReversoAux(noh* umNoh);
     public:
          listadup();
          listadup(const listadup& umalistadup);
          ~listadup();
          listadup& operator=(const listadup& umalistadup);
          inline void insere(Dado dado);
          void insereNoInicio(Dado dado);
          void insereNaPosicao(int posicao, Dado dado);
          void insereNoFim(Dado dado);
          int procura(Dado valor);
          void imprime();
          void imprimeReverso();
          inline bool vazia();
          void removeNoFim();
          void removeNoInicio();
          void removeValor(Dado valor);
          
};
 
listadup::listadup(){
     tamanho = 0;
     primeiro = NULL;
     ultimo = NULL;
}
//construtor de copia
listadup::listadup(const listadup& umalistadup){
     tamanho = 0;
     primeiro = NULL;
     ultimo = NULL;
     
     noh* aux = umalistadup.primeiro;

     while(aux != NULL){
          insereNoFim(aux->dado);
          aux = aux->proximo;
     }
}
//destrutor
listadup::~listadup(){
     removeTodos();
}

void listadup::removeTodos(){
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

listadup& listadup::operator=(const listadup& umalistadup){
     //limpa a listadup atual
     removeTodos();

     //precorre a listadup recebida como parametro, copiando os dados
     noh*  aux = umalistadup.primeiro;

     while(aux != NULL){
          insereNoFim(aux->dado);
          aux = aux ->proximo;
     }

     return *this;
}

void listadup::insere(Dado dado){
     insereNoFim(dado);
}

void listadup::insereNoFim(Dado dado){
     noh* novo = new noh(dado);

     if(vazia()){
          primeiro = novo;
          ultimo = novo;
     }
     else{
          ultimo->proximo = novo;
          novo->anterior = ultimo;
          ultimo = novo;
     }   
     tamanho++;
}

void listadup::insereNoInicio(Dado dado){
     noh* novo = new noh(dado);

     if(vazia()){
          primeiro = novo;
          ultimo = novo;
     } else{
          novo->proximo = primeiro;
          primeiro->anterior = novo;
          primeiro = novo;
     }
     tamanho++;
}

void listadup::insereNaPosicao(int posicao, Dado dado){
     noh* novo = new noh(dado);

     if(posicao <= tamanho && posicao >=0){
          if(vazia()){
               primeiro = novo;
               ultimo = novo;
          }else if(posicao == 0){
               novo->proximo = primeiro;
               primeiro->anterior = novo;
               primeiro = novo;
          }else if(posicao == tamanho){
               ultimo->proximo = novo;
               novo->anterior = ultimo;
               ultimo = novo;
          }else{
               noh* aux = primeiro;
               int posAux = 0;
               while (posAux < (posicao-1)){
                    aux = aux->proximo;
                    posAux++;
               }
               novo->proximo = aux->proximo;
               aux->proximo->anterior = novo;
               aux->proximo = novo;
               tamanho++;
          }
     }else{
          cerr << "Posicao inexistente!" << endl;
          exit(EXIT_FAILURE);
     }
}

int listadup::procura(Dado valor){
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


void listadup::imprime(){
     noh* aux = primeiro;

     while(aux != NULL){
          cout << aux->dado << " ";
          aux = aux->proximo;
     }
     cout << endl;

     //imprime reverso
     aux = ultimo;
     while(aux != NULL){
          cout << aux->dado << " ";
          aux = aux->anterior;
     }
     cout << endl;
}



inline bool listadup::vazia(){
     return (tamanho == 0);
}

void listadup::removeNoInicio(){
      if(vazia()){
          cerr << "Remocao em listadup vazia!" << endl;
          exit(EXIT_FAILURE);
     }

     noh* removido = primeiro;
     primeiro = primeiro->proximo;
     if(primeiro != NULL) primeiro->anterior = NULL;
     delete removido;

     tamanho--;
     if (vazia()) primeiro = NULL;
}

void listadup::removeNoFim(){
      if(vazia()){
          cerr << "Remocao em listadup vazia!" << endl;
          exit(EXIT_FAILURE);
     }

     noh* removido = ultimo;
     ultimo = ultimo->anterior;
     if(ultimo != NULL) ultimo->proximo = NULL;
     delete removido;
     tamanho--;
     if (vazia()) primeiro = NULL;
}

void listadup::removeValor(Dado dado){
     noh* aux = primeiro;
     
     while(aux != NULL && aux->dado != dado){
          aux = aux->proximo;
     }
     if(aux == NULL){
          cerr << "Erro: remocao de valor não encontrado" << endl;
          exit(EXIT_FAILURE);
     }
     else{
          noh* anterior = aux->anterior;
          noh* proximo = aux->proximo;
          if(anterior != NULL) 
               anterior->proximo = proximo;
          else
               primeiro = aux->proximo;
          if(proximo != NULL) 
               proximo->anterior = anterior;
          else
               ultimo = aux->anterior;
          delete aux;
     }
     tamanho--;
     if(vazia()){
          ultimo = NULL;
          primeiro = NULL;
     }
}




int main(){
     listadup minhaLista;
     cout << "**Teste da listadup**" << endl;

     minhaLista.insere(5);
     minhaLista.insere(3);
     minhaLista.insere(1);
     minhaLista.insere(0);
     minhaLista.insere(6);
     minhaLista.insereNoInicio(18);
     minhaLista.insereNaPosicao(3,25);
     minhaLista.imprime();
     
     cout << minhaLista.procura(3) << endl;
     cout << minhaLista.procura(50)<< endl;
     cout << minhaLista.procura(6)<< endl;

     //contrutor de copia
     cout << "Sobrecarga do construtor de copia" << endl;
     listadup outraLista(minhaLista);
     outraLista.insereNoInicio(99);
     outraLista.insereNoFim(10);

     //sobrecarga do operador de atribuicao
     cout << "Sobrecarga do operador de atribuicao" << endl;
     listadup maisUmaLista;
     maisUmaLista = outraLista;

     maisUmaLista.insereNoInicio(31);
     maisUmaLista.insereNoFim(13);

     cout << endl;
     

     minhaLista.imprime();
     outraLista.imprime();
     maisUmaLista.imprime();

     minhaLista.removeNoFim();
     minhaLista.removeNoInicio();
     minhaLista.removeNoFim();
     minhaLista.removeNoInicio();
     minhaLista.removeNoFim();
     minhaLista.removeNoInicio();
     minhaLista.removeValor(25);
     minhaLista.imprime();

     outraLista.removeValor(10);
     outraLista.imprime();

     maisUmaLista.removeValor(31);
     maisUmaLista.removeValor(25);
     maisUmaLista.imprime();

     minhaLista.insere(0);
     minhaLista.imprime();
     minhaLista.insereNoInicio(12);
     minhaLista.imprime();




     return 0;
}