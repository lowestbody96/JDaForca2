
#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[50];
    int vitorias;
    int derrotas;
    int empates;
    int dicas_usadas;
    int partidas_jogadas;
} JogadorRanking;

void rank(int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas);
void mostrarRanking(void);
void organize(JogadorRanking *lista, int quantidade);

#endif
