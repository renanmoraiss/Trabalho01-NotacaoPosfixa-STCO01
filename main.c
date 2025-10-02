#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1000

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

int main() {
    char expInfixa[TAM_MAX];
    char *expPosFixa;
    scanf("%[^\n]", expInfixa);
    if (bemFormada(expInfixa)) {
        expPosFixa = infixaParaPosFixa(expInfixa);
        printf("%s\n", expPosFixa);
        free(expPosFixa);
    }
    return 0;
}

//função para alocar dinamicamente uma pilha.
pilha criarPilha() {
    pilha P = malloc(sizeof(*P));
    P->topo = NULL;
    return P;
}

//função para adicionar elementos na pilha.
void empilhar(pilha P, char c) {
    elemento *elem;
    elem = malloc(sizeof(elemento));
    if (elem == NULL) {
        return;
    }
    elem->proximo = P->topo;
    P->topo = elem;
    elem->caractere = c;
    return;
}

//função para remover elementos da pilha.
char desempilhar(pilha P) {
    char c_auxiliar;
    elemento* auxiliar;
    auxiliar = P->topo;
    P->topo = P->topo->proximo;
    c_auxiliar = auxiliar->caractere;
    free(auxiliar);
    return c_auxiliar;
}

//função para converter uma expressão infixa em posfixa.
char *infixaParaPosFixa(char *expInfixa) {
    char *expPosFixa;
    char caractere;
    int tamanho = strlen(expInfixa);
    expPosFixa = malloc(sizeof(char) * (tamanho+1));
    pilha P = criarPilha();

    int j = 0;
    for (int i = 0; expInfixa[i] != '\0'; i++) {
        switch(expInfixa[i]) {
            case '(':
                empilhar(P, expInfixa[i]);
                break;

            case ')':
                caractere = desempilhar(P);
                while (caractere != '(') {
                    expPosFixa[j++] = caractere;
                    caractere = desempilhar(P);
                }
                break;

            case '+':
            case '-':
                while (!pilhaVazia(P) && P->topo->caractere != '(' &&
                       (P->topo->caractere == '+' || P->topo->caractere == '-' ||
                        P->topo->caractere == '*' || P->topo->caractere == '/' ||
                        P->topo->caractere == '^')) {
                    expPosFixa[j++] = desempilhar(P);
                }
                empilhar(P, expInfixa[i]);
                break;

            case '*':
            case '/':
                
                while (!pilhaVazia(P) && P->topo->caractere != '(' &&
                       (P->topo->caractere == '*' || P->topo->caractere == '/' ||
                        P->topo->caractere == '^')) {
                    expPosFixa[j++] = desempilhar(P);
                }
                empilhar(P, expInfixa[i]);
                break;

            case '^':
                
                empilhar(P, expInfixa[i]);
                break;

            default:
                expPosFixa[j++] = expInfixa[i];
        }
    }
    while (!pilhaVazia(P)) {
        expPosFixa[j++] = desempilhar(P);
    }
    expPosFixa[j] = '\0';
    liberarPilha(P);
    return expPosFixa;
}

//função para verificar se a string possui a estrutura correta para converter expressão infixa para posfixa.
int bemFormada(char *expInfixa) {
    char caractere;
    pilha P = criarPilha();
    //
    for (int i = 0; expInfixa[i] != '\0'; i++) {
        switch (expInfixa[i]) {
            case '[':
            case '(':
            empilhar(P, expInfixa[i]);
            break;

            case ')':
            if (pilhaVazia(P)) {
                liberarPilha(P);
                return 0;
            }
            caractere = desempilhar(P);
            if (caractere != '(') {
                return 0;
            }
            break;

            case ']':
            if (pilhaVazia(P)) {
                liberarPilha(P);
                return 0;
            }
            caractere = desempilhar(P);
            if (caractere != '[') {
                return 0;
            }
            break;

            default:
            break;
        }
    } if (pilhaVazia(P)) {
        liberarPilha(P);
        return 1;
    } else {
        liberarPilha(P);
        return 0;
    }
}

//função para liberar os elementos da pilha.
void liberarElementos(elemento *elem) {
    if (elem == NULL) {
        return;
    } else {
        liberarElementos(elem->proximo);
        free(elem);
    }
}

//função para liberar o topo da pilha.
void liberarPilha(pilha P) {
    liberarElementos(P->topo);
    free(P);
    return;
}

//função para verificar se a pilha está vazia.
int pilhaVazia(pilha P){
    if(P == NULL || P->topo == NULL){
        return 1;
    }
    else {
        return 0;
    }
}