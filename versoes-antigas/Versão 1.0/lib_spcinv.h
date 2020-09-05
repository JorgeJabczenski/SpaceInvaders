#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "lib_lista.h"
#include "lib_graficos.h"

/* Clock do Jogo */
#define DELAY 20000

/* Define o tamanho do display */
#define LINHAS   38
#define COLUNAS 100

/* Direções */
#define UP    -1
#define DOWN   1
#define LEFT  -1
#define RIGHT  1
#define STAY   0

/*====================ALIENS=======================*/

#define ALIEN1A "/^-^\\\\xxx/ \\x/ "
#define ALIEN1B "/o-o\\\\XXX/ \\X/ "
#define ALIEN2A "\\+=+\\ |T| /   \\ "
#define ALIEN2B "/-=-/ |t| /   \\"
#define ALIEN3A "/\\_/\\|o o|\\_v_/"
#define ALIEN3B "/\\_/\\|x x|\\_^_/"
#define LINALIENS 3
#define COLALIENS 5
#define TAMANHOALIEN 15
/* Velocidade de movimento dos aliens */
#define DELAYALIENS 15
/* Velocidade maxima dos aliens */
#define LIMITEALIENS 5
/* Incremento de velocidade */
#define INCREMENTOALIENS 25
/* Taxa maxima de aumento de velocidade */
#define LIMITEINCREMENTOALIENS 10
/* Quantidade maxima de bombas que podem existir simultaneamente   */
#define MAXBOMBAS  5
/* Velocidade de movimento das bombas */
#define DELAYBOMBAS 20
/* Desenho das bombas */
#define BOMBA1 '|'
#define BOMBA2 'v'

/*===================JOGADOR========================*/

#define JOGADOR1 "!=|=!^~^~^"
#define JOGADOR2 "[-|-]~^~^~"
#define LINJOGADOR 2
#define COLJOGADOR 5
#define TAMANHOJOGADOR 10
/* Quantidade Máxima de tiros que podem existir simultaneamente   */
#define MAXTIROS 5
/* Velocidade de movimento dos tiros */
#define DELAYTIROS 2
#define TIRO1 '^'
#define TIRO2 '|'

/*=====================NAVE MAE======================*/

/* Velocidade de movimento da nave mãe */
#define DELAYNAVEMAE 5
/* De quanto em quanto tempo a nave mae aparece */
#define APARICAONAVEMAE 200
#define NAVEMAE1 "/.*.*.*\\<o o o >\\.*.*.*/"
#define NAVEMAE2 "/*.*.*.\\< o o o>\\*.*.*./"
#define LINMAE 3
#define COLMAE 8
#define TAMANHONAVEMAE 24

/*====================EXPLOSAO=======================*/

/* 2x2 */
#define MINIEXPLOSAO  "\\//\\"
#define LINMINEXPL 2
#define COLMINEXPL 2
/* 3x3 */
#define EXPLOSAO      "\\|/- -/|\\"
#define LINEXPL 3
#define COLEXPL 3
/* Tempo que a explosao fica na tela */
#define DELAYEXPLOSAO 20000

/*====================BARREIRA=======================*/

/* 3x8 */
#define BARREIRA1 ACS_CKBOARD
#define BARREIRA2 ACS_DIAMOND
/* Quantidade inicial de linhas e colunas das barreiras */
#define LINHASBARREIRA      3
#define COLUNASBARREIRA     8
#define QUANTIDADEBARREIRAS 4

/*====================PONTUACAO=======================*/

#define PONTUACAOALIEN   10
#define PONTUACAONAVEMAE 30
#define PONTUACAOBOMBA    2
#define PONTUACAOBARREIRA 0

/*====================FUNCOES=======================*/

void configuracoes_iniciais();
void encerra(t_sprite *jogador);
void desenha_layout();
void imprimir_score(int score, int aliens_mortos, int bombas_destruidas, int rodada);
void proximo_level(t_lista *aliens, t_lista *tiros, t_lista *bombas, t_lista *navemae, t_lista *barreiras, int *rodada, int *delay_aliens, int *incremento_aliens, int *delay_bombas, int *maxtiros, int *counter_navemae, int *dir, int score, int aliens_mortos, int bombas_destruidas, int *maxbombas);
void imprime_tela_inicio();
void imprime_tela_final(int score, int aliens_mortos, int bombas_destruidas, int rodada);

void inicializa_desenho(t_sprite *d, int y, int x, int lin, int col, char c1[], char c2[]);
void imprime_desenho(t_sprite *d, int versao);

void move_jogador(t_sprite *jogador, int dir, int *v_jogador);

void move_aliens(t_lista *aliens, int *dir);
void inicializa_aliens(t_lista *aliens);
void ajusta_velocidade_aliens(int *counter_aliens, int *delay_aliens, int incremento_aliens);
void checa_posicao_aliens(t_lista *aliens, t_lista *barreiras, t_sprite *jogador);

void move_projeteis(t_lista *projeteis, int dir);
void atirar(t_lista *tiros, t_sprite *jogador, int maxtiros);
int  detecta_tiro(t_lista *lista_a, t_lista *lista_b, int *score, int pontos);
void bombardear(t_lista *bombas, t_lista *aliens, int maxbombas);
void detecta_bomba(t_lista *bombas, t_lista *barreiras, t_sprite *jogador);

void inicializa_barreiras(t_lista *barreiras);

void inicializa_navemae(t_lista *navemae);
void move_navemae(t_lista *navemae);

