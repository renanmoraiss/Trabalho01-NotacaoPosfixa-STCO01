#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1000

typedef struct Elemento { 
    char caractere;
    struct Elemento *proximo;
}elemento; //struct de um elemento da pilha (contém um caractere e um ponteiro para o próx. elemnto na pilha)

typedef struct Pilha {
    elemento *topo;
}*pilha; //struct com ponteiro que vai apontar para o topo da pilha

pilha criarPilha(); //protótipo da função para criar pilha de forma dinamica na heap
void empilhar(pilha P, char c); //protótipo da função para inserir um novo elemento no topo da pilha
char desempilhar(pilha P); //protótipo da função para remover o elemento do tipo da pilha e depois retornar o respectivo caractere
int pilhaVazia(pilha P); //protótipo da função para verificar se a pilha tá vazia
char *infixaParaPosFixa(char *expInfixa); //protótipo da função para converter notação infixa para notação posfixa
int verificarEstruturaInfixa(char *expInfixa); //protótipo da função para verificar se a notação infixa tem ( ) e [ ] corretos
void liberarElementos(elemento *elem); //protótipo da função para liberar todos os elementos da pilha
void liberarPilha(pilha P); //protótipo da função para liberar a pilha da heap

int main() {
    char expInfixa[TAM_MAX];
    char *expPosFixa;
    scanf("%[^\n]", expInfixa);
    if (verificarEstruturaInfixa(expInfixa)) { //estrutura condicional para verificar se a notação infixa está na estrutura correta
        expPosFixa = infixaParaPosFixa(expInfixa);
        printf("%s\n", expPosFixa);
        free(expPosFixa);
    }
    return 0;
}

pilha criarPilha() {
    pilha P = malloc(sizeof(*P));
    if (P == NULL) { //verifica se a alocação dinamica da pilha na heap deu certo
        return NULL;
    }
    P->topo = NULL;
    return P;
}

void empilhar(pilha P, char c) {
    elemento *elem;
    elem = malloc(sizeof(elemento));
    if (elem == NULL) { //verifica se a alocação dinamica do elemento na heap deu certo
        return;
    }
    elem->proximo = P->topo;
    P->topo = elem; //insere o novo elemento alocado no topo da pilha
    elem->caractere = c;
    return;
}

char desempilhar(pilha P) {
    if (P == 0 || P->topo == 0) { //P == 0 -> verificar se a pilha não existe; P->topo == 0 -> verificar se a pilha existe e não tem elemento nela
        return '\0';
    }
    char c_auxiliar;
    elemento* auxiliar;
    auxiliar = P->topo;
    P->topo = P->topo->proximo;
    c_auxiliar = auxiliar->caractere; //guardar o valor do caractere que será retornado
    free(auxiliar); //libera a memória do elemento removido anteriormente
    return c_auxiliar;
}

char *infixaParaPosFixa(char *expInfixa) {
    char *expPosFixa;
    char caractere;
    int tamanho = strlen(expInfixa);
    expPosFixa = malloc(sizeof(char) * (tamanho+1));
    if (expPosFixa == NULL) {
        return NULL;
    }
    pilha P = criarPilha();
    if (P == NULL) {
        free(expPosFixa);
        return NULL;
    }

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
            while (!pilhaVazia(P) && P->topo->caractere != '(' && (P->topo->caractere == '+' || P->topo->caractere == '-' || P->topo->caractere == '/' || P->topo->caractere == '*')) { 
                expPosFixa[j++] = desempilhar(P);
            } empilhar(P, expInfixa[i]);
            break;

            case '*':
            case '/':
            while (!pilhaVazia(P) && P->topo->caractere != '(' && (P->topo->caractere == '/' || P->topo->caractere == '*')) {
                expPosFixa[j++] = desempilhar(P);
            } empilhar(P, expInfixa[i]);
            break;

            case '^':
            while (!pilhaVazia(P) && P->topo->caractere == '^') {
                expPosFixa[j++] = desempilhar(P);
            } empilhar(P, expInfixa[i]);
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

int verificarEstruturaInfixa(char *expInfixa) {
    char caractere;
    pilha P = criarPilha();

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
                liberarPilha(P);
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
                liberarPilha(P);
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

int pilhaVazia(pilha P){
    if(P == NULL || P->topo == NULL){
        return 1;
    }
    else {
        return 0;
    }
}