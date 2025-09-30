#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

#define TAM_MAX 100

int main() {
    char expInfixa[TAM_MAX];
    char *expPosFixa;
    printf("String de entrada: ");
    scanf("%s", expInfixa);
    if (bemFormada(expInfixa)) {
        expPosFixa = infixaParaPosFixa(expInfixa);
        printf("%s\n", expPosFixa);
        free(expPosFixa);
    }
    return 0;
}