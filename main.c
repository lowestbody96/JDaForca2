#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"
#include "jogo.h"

int main() {
    Palavra *todasPalavras = NULL;
    int totalPalavras = 0;
    int dicas = 0;
    int vitorias = 0;
    int derrotas = 0;
    int empates = 0;
    int partidas = 0;
    int sair = 0;

    srand(time(NULL));

    FILE *ff = fopen("palavras.txt", "r");
    totalPalavras = present(ff, &todasPalavras, &totalPalavras);

    if (todasPalavras == NULL || totalPalavras == 0) {
        printf("\nNao foi possivel carregar as palavras do jogo.\n");
        return 1;
    }

    printf("\nTudo pronto pra iniciar...\n");

    while (!sair) {
        sair = posmenu(todasPalavras, totalPalavras, &dicas, &vitorias, &derrotas, &empates, &partidas);
    }

    free(todasPalavras);
    return 0;
}