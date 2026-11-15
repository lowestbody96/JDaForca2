#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "ranking.h"

int menu(void) {
    int alpha = 0;
    do {
        printf("\n[1] Jogar | [2] Ver Ranking | [3] Como Jogar | [4] Sair\n");
        scanf("%d", &alpha);
        getchar();
    } while (alpha != 1 && alpha != 2 && alpha != 3 && alpha != 4);
    return alpha;
}

int posmenu(Palavra *lista, int quantidade, int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas) {
    int alpha = menu();

    printf("\nVitórias = %d", *vitorias);

    switch(alpha) {
        case 1: {
            char tema[30];
            int indiceTema = picktheme(lista, quantidade, tema);
            if (indiceTema < 0) {
                printf("\nNenhum tema disponivel.\n");
                return 0;
            }

            int qtdTema = 0;
            Palavra *temaLista = filtrarTema(lista, quantidade, tema, &qtdTema);
            if (temaLista == NULL || qtdTema == 0) {
                printf("\nNenhuma palavra encontrada para esse tema.\n");
                return 0;
            }

            printf("\n==JOGO DA FORCA==\n");
            int venceu = newPartida(temaLista, qtdTema, dicas, vitorias, derrotas, empates, partidas);
            if (venceu) {
                printf("\nDeseja salvar sua pontuação no ranking? [s/n]: ");
                char resposta;
                scanf(" %c", &resposta);
                getchar();
                if (resposta == 's' || resposta == 'S') {
                    rank(dicas, vitorias, derrotas, empates, partidas);
                }
            }
            free(temaLista);
            return 0;
        }

        case 2:
            printf("\n==VER RANKING==\n");
            mostrarRanking();
            return 0;

        case 3:
            printf("\n==COMO JOGAR==\n");
            printf("\nSe você chegou até aqui, está tudo pronto pra jogar");
            printf("\nSerá escolhida aleatoriamente uma palavra do tema selecionado");
            printf("\nVocê tem 6 tentativas para acertar a palavra");
            printf("\nVocê pode gastar 1 vida pedindo uma dica com '$'");
            printf("\nSempre que vencer, pode adicionar sua nova pontuação ao ranking");
            printf("\nIsso é tudo! Bom jogo");
            return 0;

        case 4:
            printf("\n==SAINDO DO JOGO==\n");
            return 1;

        default:
            printf("\nentrada invalida...");
            return 0;
    }
}

int newPartida(Palavra *lista, int quantidade, int *dicas, int *vitorias, int *derrotas, int *empates, int *partidas) {
    (void)empates;
    int erros = 0;
    int rodada = 1;
    int ganhou = 0;
    int sorteio = rand() % quantidade;
    int omega = lista[sorteio].tamanho;
    char palavra[50];
    char desc[50];
    char chute;
    int match;
    char chuteserrados[7] = {0};
    char letrasUsadas[26] = {0};

    (*partidas)++;
    strcpy(palavra, lista[sorteio].texto);
    for (int i = 0; i < omega; i++) {
        desc[i] = '-';
    }
    desc[omega] = '\0';

    while (erros < 6) {
        if (strcmp(desc, palavra) == 0) {
            printf("\nVocê venceu!");
            printf("\nA palavra correta era mesmo %s!\n", desc);
            (*vitorias)++;
            ganhou = 1;
            break;
        }

        boneco(erros);
        printf("\nRodada nº%d\n", rodada);
        printf("\n%s", desc);
        printf("\nSeus erros: %s\n", chuteserrados);
        printf("\nSeu chute: ");
        scanf(" %c", &chute);
        getchar();

        if (chute >= 'a' && chute <= 'z') {
            chute -= 32;
        }

        if (chute == '$') {
            if (erros >= 5) {
                printf("\nVoce nao pode usar dica com 5 erros ou mais.\n");
                continue;
            }
            (*dicas)++;
            erros++;
            printf("\nDica usada! Voce perdeu 1 vida.\n");
            for (int i = 0; i < omega; i++) {
                if (desc[i] == '-') {
                    desc[i] = palavra[i];
                    break;
                }
            }
            rodada++;
            continue;
        }

        if (chute < 'A' || chute > 'Z') {
            printf("\nDigite uma letra valida.\n");
            continue;
        }

        if (letrasUsadas[chute - 'A']) {
            printf("\nEssa letra ja foi usada.\n");
            continue;
        }

        letrasUsadas[chute - 'A'] = 1;
        match = 0;

        for (int j = 0; j < omega; j++) {
            if (palavra[j] == chute) {
                match++;
                desc[j] = chute;
            }
        }

        if (match == 0) {
            printf("\nVocê errou!\n");
            chuteserrados[erros] = chute;
            erros++;
        }

        rodada++;
    }

    if (!ganhou) {
        printf("\nVocê perdeu!\n");
        printf("\nA palavra correta era %s\n", palavra);
        (*derrotas)++;
    }

    return ganhou;
}

void boneco(int erros) {
    printf("\n----------------+\n");
    printf("Erros:%d", erros);
    printf("\t\t|\n");
    printf("\t\t|\n");

    switch (erros) {
        case 1:
            printf("\t\tO\n");
            break;
        case 2:
            printf("\t\tO\n");
            printf("\t\t=\n");
            printf("\t\t|\n");
            break;
        case 3:
            printf("\t\tO\n");
            printf("\t\t=\n");
            printf("\t\t/|\n");
            break;
        case 4:
            printf("\t\tO\n");
            printf("\t\t=\n");
            printf("\t\t/|\\\n");
            break;
        case 5:
            printf("\t\tO\n");
            printf("\t\t=\n");
            printf("\t\t/|\\\n");
            printf("\t\t/\n");
            break;
        case 6:
            printf("\t\tO\n");
            printf("\t\t=\n");
            printf("\t\t/|\\\n");
            printf("\t\t/ \\\n");
            break;
        default:
            break;
    }
    printf("\n==========\n");
}
