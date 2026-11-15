#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

int compararRanking(void *a, void *b) {
    JogadorRanking *j1 = (JogadorRanking *)a;
    JogadorRanking *j2 = (JogadorRanking *)b;

    if (j1->vitorias != j2->vitorias) {
        return j2->vitorias - j1->vitorias;
    }
    if (j1->dicas_usadas != j2->dicas_usadas) {
        return j1->dicas_usadas - j2->dicas_usadas;
    }
    if (j1->derrotas != j2->derrotas) {
        return j1->derrotas - j2->derrotas;
    }
    return strcmp(j1->nome, j2->nome);
}

void rank(int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas) {
    JogadorRanking jogador;
    JogadorRanking *lista = NULL;
    FILE *arquivo;
    int quantidade = 0;
    int encontrado = 0;

    printf("\nRegistro de ranking");
    printf("\nInsira o nome do jogador:\n");
    printf("\nNome: ");
    scanf(" %49[^\n]", jogador.nome);
    getchar();

    jogador.vitorias = *vitorias;
    jogador.derrotas = *derrotas;
    jogador.empates = *empates;
    jogador.dicas_usadas = *dicas;
    jogador.partidas_jogadas = *partidas;

    arquivo = fopen("ranking.bin", "rb");
    if (arquivo != NULL) {
        JogadorRanking atual;
        while (fread(&atual, sizeof(JogadorRanking), 1, arquivo) == 1) {
            lista = (JogadorRanking *)realloc(lista, (quantidade + 1) * sizeof(JogadorRanking));
            if (lista == NULL) {
                fclose(arquivo);
                printf("\nErro ao ler ranking.\n");
                return;
            }
            lista[quantidade++] = atual;
            if (strcmp(atual.nome, jogador.nome) == 0) {
                encontrado = 1;
                lista[quantidade - 1].vitorias += jogador.vitorias;
                lista[quantidade - 1].derrotas += jogador.derrotas;
                lista[quantidade - 1].empates += jogador.empates;
                lista[quantidade - 1].dicas_usadas += jogador.dicas_usadas;
                lista[quantidade - 1].partidas_jogadas += jogador.partidas_jogadas;
            }
        }
        fclose(arquivo);
    }

    if (!encontrado) {
        lista = (JogadorRanking *)realloc(lista, (quantidade + 1) * sizeof(JogadorRanking));
        if (lista == NULL) {
            printf("\nErro ao salvar ranking.\n");
            return;
        }
        lista[quantidade++] = jogador;
    }

    organize(lista, quantidade);

    arquivo = fopen("ranking.bin", "wb");
    if (arquivo == NULL) {
        free(lista);
        printf("\nNao foi possivel abrir o arquivo de ranking.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fwrite(&lista[i], sizeof(JogadorRanking), 1, arquivo);
    }

    fclose(arquivo);
    free(lista);
    printf("\nJogador salvo no ranking!\n");
}

void mostrarRanking(void) {
    FILE *arquivo = fopen("ranking.bin", "rb");
    JogadorRanking jogador;
    int i = 1;

    if (arquivo == NULL) {
        printf("\nRanking vazio.\n");
        return;
    }

    printf("\n== RANKING ==\n");
    printf("%2s %-20s %-10s %-10s %-10s %-12s %-10s\n", "#", "Nome", "Vitorias", "Derrotas", "Empates", "Dicas", "Partidas");

    while (fread(&jogador, sizeof(JogadorRanking), 1, arquivo) == 1) {
        printf("%2d %-20s %-10d %-10d %-10d %-12d %-10d\n",
               i,
               jogador.nome,
               jogador.vitorias,
               jogador.derrotas,
               jogador.empates,
               jogador.dicas_usadas,
               jogador.partidas_jogadas);
        i++;
    }

    fclose(arquivo);
}

void organize(JogadorRanking *lista, int quantidade) {
    if (lista == NULL || quantidade <= 1) {
        return;
    }

    for (int i = 1; i < quantidade; i++) {
        JogadorRanking atual = lista[i];
        int j = i - 1;

        while (j >= 0 && compararRanking(&lista[j], &atual) > 0) {
            lista[j + 1] = lista[j];
            j--;
        }

        lista[j + 1] = atual;
    }
}