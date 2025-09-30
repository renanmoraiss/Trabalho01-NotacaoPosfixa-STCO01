struct Elemento {
    char caractere;
    struct Elemento *proximo;
};
typedef struct Elemento elemento;

struct Pilha {
    elemento *topo;
};
typedef struct Pilha *pilha;

pilha criarPilha(); //criar pilha.
void empilhar(pilha P, char c); //colocar elemento na pilha.
char desempilhar(pilha P); //retirar elemento da pilha.
int pilhaVazia(pilha P); //verificar se a pilha está vazia.
char *infixaParaPosFixa(char *expInfixa); //converter expressão infixa para posfixa.
int bemFormada(char *expInfixa); //verificar se a expressão possui a estrutura adequada.
void liberarElementos(elemento *elem); //limpar elementos da pilha.
void liberarPilha(pilha P); //limpar topo da pilha.