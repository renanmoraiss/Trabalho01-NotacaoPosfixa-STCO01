#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1000

typedef struct Elemento { 
    char caractere;
    struct Elemento *proximo;
}elemento; //elemento da pilha (contém um caractere e um ponteiro para o próx. elemento na pilha)

typedef struct Pilha {
    elemento *topo;
}*pilha; //ponteiro que vai apontar para o topo da pilha

pilha criarPilha(); //criar pilha de forma dinamica na heap
void empilhar(pilha P, char c); //inserir um novo elemento no topo da pilha
char desempilhar(pilha P); //remover o elemento do tipo da pilha e depois retornar o respectivo caractere
int verificarPilhaVazia(pilha P); //verificar se a pilha tá vazia
char *notacaoInfixaParaPosfixa(char *notacaoInfixa); //converter notação infixa para notação posfixa
int verificarEstruturaInfixa(char *notacaoInfixa); //verificar se a notação infixa tem ( ) e [ ] corretos
void liberarElementos(elemento *elem); //liberar todos os elementos da pilha
void liberarPilha(pilha P); //liberar a pilha da heap

int main() {
    char notacaoInfixa[TAM_MAX];
    char *notacaoPosfixa;
    scanf("%[^\n]", notacaoInfixa);
    if (verificarEstruturaInfixa(notacaoInfixa)) { //verificar se a notação infixa está na estrutura correta
        notacaoPosfixa = notacaoInfixaParaPosfixa(notacaoInfixa);
        printf("%s\n", notacaoPosfixa);
        free(notacaoPosfixa);
    }
    return 0;
}

pilha criarPilha() {
    pilha P = malloc(sizeof(*P));
    if (P == NULL) { //verificar se a alocação dinamica da pilha na heap deu certo
        return NULL;
    }
    P->topo = NULL;
    return P;
}

void empilhar(pilha P, char c) {
    elemento *elem;
    elem = malloc(sizeof(elemento));
    if (elem == NULL) { //verificar se a alocação dinamica da memoria para o elemento na heap deu certo
        return;
    }
    elem->proximo = P->topo;
    P->topo = elem; //inserir o novo elemento alocado no topo da pilha
    elem->caractere = c;
    return;
}

char desempilhar(pilha P) {
    if (P == 0 || P->topo == 0) { //verificar se a pilha não existe e verificar se a pilha existe e não tem elemento nela
        return '\0';
    }
    char c_auxiliar;
    elemento* auxiliar;
    auxiliar = P->topo;
    P->topo = P->topo->proximo;
    c_auxiliar = auxiliar->caractere; //guardar o valor do caractere que será retornado
    free(auxiliar); //liberar a memória do elemento removido anteriormente
    return c_auxiliar;
}

char *notacaoInfixaParaPosfixa(char *notacaoInfixa) {
    char *notacaoPosfixa;
    char caractere;
    int tamanho = strlen(notacaoInfixa);
    notacaoPosfixa = malloc(sizeof(char) * (tamanho+1)); //alocar memória na heap (tamanho+1 por causa do \0 no final)
    if (notacaoPosfixa == NULL) { //verificar se a alocação dinamica da memoria na heap deu certo
        return NULL;
    }
    pilha P = criarPilha(); //chamar a funcao para criar pilha para guardar os operadoes (+ - * / ^)
    if (P == NULL) {
        free(notacaoPosfixa);
        return NULL;
    }

    int j = 0;
    for (int i = 0; notacaoInfixa[i] != '\0'; i++) {
        switch(notacaoInfixa[i]) {
            case '(': 
            empilhar(P, notacaoInfixa[i]);
            break;

            case ')':
            caractere = desempilhar(P);
            while (caractere != '(') {
                notacaoPosfixa[j++] = caractere;
                caractere = desempilhar(P);
            }
            break;

            case '+':
            case '-':
            while (!verificarPilhaVazia(P) && P->topo->caractere != '(' && (P->topo->caractere == '+' || P->topo->caractere == '-' || P->topo->caractere == '/' || P->topo->caractere == '*')) { 
                notacaoPosfixa[j++] = desempilhar(P);
            } empilhar(P, notacaoInfixa[i]);
            break;

            case '*':
            case '/':
            while (!verificarPilhaVazia(P) && P->topo->caractere != '(' && (P->topo->caractere == '/' || P->topo->caractere == '*')) {
                notacaoPosfixa[j++] = desempilhar(P);
            } empilhar(P, notacaoInfixa[i]);
            break;

            case '^':
            while (!verificarPilhaVazia(P) && P->topo->caractere == '^') {
                notacaoPosfixa[j++] = desempilhar(P);
            } empilhar(P, notacaoInfixa[i]);
            break;

            default:
            notacaoPosfixa[j++] = notacaoInfixa[i];
        }
    } 
    
    while (!verificarPilhaVazia(P)) {
        notacaoPosfixa[j++] = desempilhar(P);
    }

    notacaoPosfixa[j] = '\0';
    liberarPilha(P);
    return notacaoPosfixa;
}

int verificarEstruturaInfixa(char *notacaoInfixa) {
    char caractere;
    pilha P = criarPilha();

    for (int i = 0; notacaoInfixa[i] != '\0'; i++) {
        switch (notacaoInfixa[i]) {
            case '[':
            case '(':
            empilhar(P, notacaoInfixa[i]);
            break;

            case ')':
            if (verificarPilhaVazia(P)) {
                liberarPilha(P);
                return 0;
            }
            caractere = desempilhar(P);
            if (caractere != '(') {
                liberarPilha(P);
                return 0;
            }
            break;

            case ']':
            if (verificarPilhaVazia(P)) {
                liberarPilha(P);
                return 0;
            }
            caractere = desempilhar(P);
            if (caractere != '[') {
                liberarPilha(P);
                return 0;
            }
            break;

            default:
            break;
        }
    } if (verificarPilhaVazia(P)) {
        liberarPilha(P);
        return 1;
    } else {
        liberarPilha(P);
        return 0;
    }
}

void liberarElementos(elemento *elem) {
    if (elem == NULL) {
        return;
    } else {
        liberarElementos(elem->proximo);
        free(elem);
    }
}

void liberarPilha(pilha P) {
    liberarElementos(P->topo);
    free(P);
    return;
}

int verificarPilhaVazia(pilha P){
    if(P == NULL || P->topo == NULL){
        return 1;
    }
    else {
        return 0;
    }
}