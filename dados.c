#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

int present(FILE *ff, Palavra **lista, int *quantidade) {
    if (ff == NULL) {
        printf("\nO arquivo nao existe (ou nao foi possivel abri-lo).\n");
        *lista = NULL;
        *quantidade = 0;
        return 0;
    }

    printf("\nIniciando JOGO DA FORCA...");
    printf("\nArquivo de palavras aberto com sucesso...\n");

    int total = lecture(ff, lista, quantidade);
    fclose(ff);
    return total;
}

int lecture(FILE *ff, Palavra **lista, int *quantidade) {
    Palavra *temporario = NULL;
    int capacidade = 0;
    char linha[256];

    *lista = NULL;
    *quantidade = 0;

    while (fgets(linha, sizeof(linha), ff) != NULL) {
        char tema[30];
        char texto[50];
        int tamanho = 0;

        if (sscanf(linha, "%29[^;];%49[^;];%d", tema, texto, &tamanho) != 3) {
            continue;
        }

        if (strlen(tema) == 0 || strlen(texto) == 0) {
            continue;
        }

        if (tamanho != (int)strlen(texto)) {
            continue;
        }

        if (*quantidade == capacidade) {
            capacidade = (capacidade == 0) ? 10 : capacidade * 2;
            temporario = (Palavra *)realloc(*lista, capacidade * sizeof(Palavra));
            if (temporario == NULL) {
                free(*lista);
                *lista = NULL;
                *quantidade = 0;
                return 0;
            }
            *lista = temporario;
        }

        strcpy((*lista)[*quantidade].tema, tema);
        strcpy((*lista)[*quantidade].texto, texto);
        (*lista)[*quantidade].tamanho = tamanho;
        (*quantidade)++;
    }

    return *quantidade;
}

int picktheme(const Palavra *lista, int quantidade, char *temaEscolhido) {
    char temas[50][30];
    int totalTemas = 0;

    if (lista == NULL || quantidade <= 0) {
        return -1;
    }

    for (int i = 0; i < quantidade; i++) {
        int jaExiste = 0;
        for (int j = 0; j < totalTemas; j++) {
            if (strcmp(lista[i].tema, temas[j]) == 0) {
                jaExiste = 1;
                break;
            }
        }

        if (!jaExiste) {
            strcpy(temas[totalTemas], lista[i].tema);
            totalTemas++;
        }
    }

    printf("\nEscolha um dos temas:\n");
    for (int i = 0; i < totalTemas; i++) {
        printf("[%d] %s\n", i + 1, temas[i]);
    }

    int opcao = 0;
    do {
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
    } while (opcao < 1 || opcao > totalTemas);

    strcpy(temaEscolhido, temas[opcao - 1]);
    return opcao - 1;
}

Palavra *filtrarTema(const Palavra *lista, int quantidade, const char *tema, int *nFiltradas) {
    Palavra *filtradas = NULL;
    int total = 0;

    if (lista == NULL || quantidade <= 0 || tema == NULL) {
        if (nFiltradas != NULL) {
            *nFiltradas = 0;
        }
        return NULL;
    }

    filtradas = (Palavra *)malloc(quantidade * sizeof(Palavra));
    if (filtradas == NULL) {
        if (nFiltradas != NULL) {
            *nFiltradas = 0;
        }
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {
        if (strcmp(lista[i].tema, tema) == 0) {
            filtradas[total++] = lista[i];
        }
    }

    if (nFiltradas != NULL) {
        *nFiltradas = total;
    }

    if (total == 0) {
        free(filtradas);
        return NULL;
    }

    return filtradas;
}