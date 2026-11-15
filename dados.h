#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>

typedef struct {
    char tema[30];
    char texto[50];
    int tamanho;
} Palavra;

int present(FILE *ff, Palavra **lista, int *quantidade);
int lecture(FILE *ff, Palavra **lista, int *quantidade);
int picktheme(const Palavra *lista, int quantidade, char *temaEscolhido);
Palavra *filtrarTema(const Palavra *lista, int quantidade, const char *tema, int *nFiltradas);

#endif