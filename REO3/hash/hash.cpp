#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;
const int MAXOCUPACAO = 70;
//taxa de redimensionamento da lista 
const int TXREDIM = 1.05f;

bool primo(int n) {
    if (n==1 or n==2) return true;
    int divisor = 2;
    while ((divisor <= sqrt(n)) and (n % divisor != 0)) 
        divisor++;
    return (n % divisor != 0);
}

int obterProximoPrimo(int n){
    bool achouProximo = false;
    int i = n;
    while (not achouProximo and not primo(i)) i++;
    return i;
}

class noh{
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char tipo;
        int valor;
        noh* proximo;
        noh(const string& c= "", const char& t = 'a', const int& v = 0, noh* prox=NULL):
            chave(c), tipo(t), valor(v), proximo(prox){};
};

class lista{
    friend class tabelaHash;
    private:
        noh* primeiro;//primeiro noh da lista
        unsigned short numElementos;//quantidade de valores na lista
    public:
        lista() : primeiro(NULL), numElementos(0){}; //construtor
        ~lista(){ //destrutor
         noh* atual = primeiro;
         while(atual != NULL){
            noh* aux = atual;
            atual = atual->proximo;
            delete aux;
         }
        }
        unsigned short tamanho() {return numElementos;}//consulta do tamanho

        //adiciona um novo par de valores e insere no início da lista
        void insere(const string& c, const char& t, const int& v){
            noh* novonoh = new noh(c, t, v, primeiro);
            primeiro = novonoh;
            numElementos++;
        }
        //altera o primeiro elemento da lista
        bool alteraValor(const string&c, const int& v){
            noh* atual = primeiro;
            while((atual != NULL) and (atual->chave != c)){
                atual = atual->proximo;
            if(atual == NULL)
                return false;
            else{
                atual->valor = v;
                return true;
            }
        }
        //remove o noh, se nao existir retorna informacoes
        bool remove(const string& c){
            noh* atual = primeiro;
            noh* anterior = NULL;
            while ((atual != NULL) and (atual->chave != c)){
                anterior = atual;
                atual = atual->proximo;
            }
            if (atual!=NULL){
                if (anterior == NULL){
                    primeiro = atual->proximo;
                }else{
                    anterior->proximo = atual->proximo;
                }
                delete atual;
                numElementos--;
                return true;
            }
            else 
            return false;
        }
};
