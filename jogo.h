#ifndef JOGO_H
#define JOGO_H

#include "dados.h"

int menu(void);
int posmenu(Palavra *lista, int quantidade, int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas);
int newPartida(Palavra *lista, int quantidade, int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas);
void boneco(int erros);

#endif