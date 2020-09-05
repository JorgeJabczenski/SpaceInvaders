#include <ncurses.h>
#include "lib_spcinv.h"

/* Desenha a "casca" do jogo */
void desenha_layout();

/* Imprime a tela inicial do jogo */
void imprime_tela_inicio();

/* Imprime a tela quando o jogador morre */
/* Retorna 1 para reiniciar o jogo e 0 para finaliza-lo */
int imprime_tela_final(int score, int aliens_mortos, int bombas_destruidas, int level);

/* Imprime a pontuação do jogo, a quantidade de aliens mortos, a quantidade de bombas destruidas e a rodada */
void imprimir_score(int score, int aliens_mortos, int bombas_destruidas, int level);

/* A cada ciclo de jogo, imprime todas as listas e chama a função de imprimir o score*/
void imprimir_fim_de_ciclo(t_lista *tiros, t_lista *navemae,t_lista *barreiras,t_lista *bombas,t_lista *aliens,t_lista *jogador,int score, int aliens_mortos, int bombas_destruidas, int level);

/* Sempre que todos os aliens são mortos, apresenta essa tela  */
void imprimir_tela_proximo_level(int score, int aliens_mortos, int bombas_destruidas);