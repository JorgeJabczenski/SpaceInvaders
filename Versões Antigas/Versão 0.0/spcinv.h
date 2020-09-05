#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

/* 3x5 */
#define ALIEN1A "/^-^\\\\xxx/ \\x/ "
#define ALIEN1B "/o-o\\\\XXX/ \\X/ "
#define ALIEN2A "\\+=+\\ |T| /   \\ "
#define ALIEN2B "/-=-/ |t| /   \\"
#define ALIEN3A "/\\_/\\|o o|\\_v_/"
#define ALIEN3B "/\\_/\\|x x|\\_^_/"
#define TAMANHOALIEN 15

/* 2x5 */
#define NAVINHA " /^\\ @$$$@"
#define TAMANHONAVINHA 10

/* 3x8*/
#define NAVEMAE1 "/.*.*.*\\<o o o >\\.*.*.*/"
#define NAVEMAE2 "/*.*.*.\\< o o o>\\*.*.*./"
#define TAMANHONAVEMAE 24

/* 3x5 */
#define EXPLOSAO "\\ | / - * -/ | \\"

/* 3x8 */
#define BARREIRA "/AAAAAA\\MMMMMMMMWWWWWWWW"

/* Quantidade Máxima de tiros que podem existir simultaneamente   */
#define MAXTIROS 10

/* Quantidade Máxima de tiros que podem existir simultaneamente   */
#define MAXBOMBAS  3

/* Velocidade de movimento dos aliens */
#define DELAYALIENS 10

/* Velocidade de movimento dos tiros */
#define DELAYTIROS 5

/* Velocidade de movimento das bombas */
#define DELAYBOMBAS 15

/* Define o tamanho do ecrã */
#define LINHAS 38
#define COLUNAS 100

/* Quantidade inicial de linhas e colunas das barreiras */
#define LINHASBARREIRA 3
#define COLUNASBARREIRA 8;
#define QUANTIDADEBARREIRAS 4

struct desenho_s
{
    int tamanho;
    int linhas;
    int colunas;
    char corpo[2][3][8];
    int cord_x;
    int cord_y;
    int vivo;
};
typedef struct desenho_s desenho_t;

struct tiro_s
{
    int cord_x;
    int cord_y;
};
typedef struct tiro_s tiro_t;

struct peca_barreira_s{
    int cord_x;
    int cord_y;
    int vivo;
    char c;
};
typedef struct peca_barreira_s peca_barreira_t;

struct barreira_s{
    int cord_x;
    int cord_y;
    int lin;
    int col;
    peca_barreira_t corpo[3][8];
};
typedef struct barreira_s barreira_t;


void inicializa_desenho(desenho_t *d, int lin, int col, char corpo1[], char corpo2[], int y, int x, int vivo);
void inicializa_barreira(barreira_t bar[], int linbar, int colbar);

void imprime_desenho(desenho_t *d, int ver);
void imprime_aliens(desenho_t aliens[5][11], int ver);
void imprime_projetil(tiro_t projetil[], int tamanho ,char p);
void imprime_barreira(barreira_t barreira[4]);

int tamanho_da_tela(int *nlin, int *ncol);

void move_aliens(desenho_t alien[5][11], int *direcao);