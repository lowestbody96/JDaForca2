JOGO DA FORCA

Descricao:
Este projeto implementa um jogo da forca em linguagem C, com menu principal,
selecao de tema, palavras carregadas de um arquivo, contabilizacao de vitorias,
derrotas, empates, dicas usadas e partidas jogadas, alem de um ranking .

Objetivo:
Adivinhar a palavra secreta antes de completar o desenho da forca.

Regras:
- O jogador pode escolher um tema disponivel.
- A palavra é sorteada entre as palavras daquele tema.
- Cada rodada permite chutar letras.
- Se o jogador digitar '$', usa uma dica, mas perde 1 vida.
- A dica nao pode ser usada quando o jogador ja possui 5 erros.
- O jogo termina quando a palavra e descoberta ou quando o numero de erros atinge o limite.
- O ranking salva nome do jogador e estatisticas relevantes.

Arquivos do projeto:
- main.c: ponto de entrada do programa.
- dados.h / dados.c: leitura, validacao e filtragem de palavras.
- jogo.h / jogo.c: menu, partidas, mecânica do jogo e desenho da forca.
- ranking.h / ranking.c: persistencia e exibicao do ranking.
- palavras.txt: arquivo contendo palavras e temas no formato:
  tema;palavra;tamanho

Exemplo de entrada em palavras.txt:
ASTROLOGIA;GEMEOS;6
QUIMICA;OXIGENIO;8
GEOGRAFIA;BRASIL;6
HISTORIA;REVOLUCAO;9
...


Compilar:
No terminal, dentro da pasta do projeto, execute:

gcc -Wall -Wextra -Wpedantic dados.c jogo.c ranking.c main.c -o tr

Executar:
./tr

Observacoes importantes:
- O programa utiliza arquivos em disco para armazenar o ranking em ranking.bin.
- O arquivo de palavras deve seguir o formato indicado para funcionar corretamente.
- O ranking e ordenado manualmente por quantidade de vitorias, menor uso de dicas, menor numero de derrotas e nome.

Menu principal:
1. Jogar
2. Ver Ranking
3. Como Jogar
4. Sair

Estrutura de dados:
Palavra:
- tema
- texto
- tamanho

JogadorRanking:
- nome
- vitorias
- derrotas
- empates
- dicas_usadas
- partidas_jogadas

Dica:
A dica revela uma letra da palavra, mas o jogador perde 1 vida de erro ao usá-la.

Autor:
lowestbody96
