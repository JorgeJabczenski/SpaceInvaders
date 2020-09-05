#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "lib_lista.h"

/* Clock do Jogo */
#define DELAY 20000

/* Define o tamanho do display */
#define LINHAS   38
#define COLUNAS 100
#define COLMENU  20

/* Direções */
#define UP    -1
#define DOWN   1
#define LEFT  -1
#define RIGHT  1
#define STAY   0

/* ESTADOS */
#define VIVO  1
#define MORTO 0
#define ESTADOMORTO 4


/*====================ALIENS=======================*/

/* Sprites */
#define ALIEN1A "/^-o\\\\Xxx/ \\x/ "
#define ALIEN1B "/o-o\\\\xxx/ \\+/ "
#define ALIEN1C "/o-^\\\\xxX/ \\x/ "
#define ALIEN1D "/^-^\\\\XXX/ \\+/ "
#define ALIEN2D "\\+=+/ |T| /   \\"
#define ALIEN2A "\\-=-  |t|\\/   \\"
#define ALIEN2B " -=- /|t|\\/   \\"
#define ALIEN2C " +=+//|T| /   \\ "
#define ALIEN3A "  _/\\\\/ ^|\\_v_/"
#define ALIEN3B "/\\_/\\|^ ^|\\_v_/"
#define ALIEN3C "/\\_  |o \\/\\_^_/"
#define ALIEN3D "  _  \\/ \\/\\_^_/"

/* Velocidade de movimento dos aliens */
#define DELAYALIENS 15
/* Velocidade maxima dos aliens */
#define LIMITEALIENS 3

#define QNTDALIENS 55
#define LINALIENS 3
#define COLALIENS 5
#define TAMANHOALIEN 15

/*===================BOMBAS========================*/

/* Sprites */
#define BOMBA1 "o"
#define BOMBA2 "O"
#define BOMBA3 "0"
#define BOMBA4 "O"
#define BOMBA5 "*"

/* Quantidade maxima de bombas que podem existir simultaneamente   */
#define MAXBOMBAS  5
/* Velocidade inicial de movimento das bombas */
#define DELAYBOMBAS 15
/* Velocidade máxima de movimento das bombas */
#define LIMITEBOMBAS 3
/* Delay do lançamento das bombas */
#define DELAYBOMBARDEAR 50 

/*===================JOGADOR========================*/

/* Sprites */
#define JOGADOR1 "|=|=| ~~~ "
#define JOGADOR2 "|-|-' ^~~ "
#define JOGADOR3 "'-|-' ~^~ "
#define JOGADOR4 "'=|=| ~~^ "
#define JOGADOR5 "          "

/* Tempo de mudar o sprite */
#define DELAYJOGADOR 5 

#define LINJOGADOR 2
#define COLJOGADOR 5
#define TAMANHOJOGADOR 10

/*===================TIROS========================*/

/* Sprites */
#define TIRO1 "v"
#define TIRO2 "|"
#define TIRO3 "^"
#define TIRO4 "|"

/* Quantidade Máxima de tiros que podem existir simultaneamente */
#define MAXTIROS 5
/* Quantidade Mínima de tiros que podem existir simultaneamente */
#define MINTIROS 3
/* Velocidade de movimento dos tiros */
#define DELAYTIROS 3

/*====================EXPLOSAO=======================*/

/* Sprite */
#define EXPLOSAO      " \\|/  -x-  /|\\ "

#define LINEXPL 3
#define COLEXPL 3

/*=====================NAVE MAE======================*/

/* Sprites */
#define NAVEMAE1 "W  MW  MMWMWMWMW MW  MW "
#define NAVEMAE2 "  MW  MWWMWMWMWMMW  MW  "
#define NAVEMAE3 " MW  MW MWMWMWMWW  MW  M"
#define NAVEMAE4 "MW  MW  WMWMWMWM  MW  MW"
#define EXPLOSAONAVEMAE "   \\||/   --  --   /||\\  "

/* Velocidade de movimento da nave mãe */
#define DELAYNAVEMAE 5
/* De quanto em quanto tempo a nave mae aparece */
#define APARICAONAVEMAE 700

#define LINMAE 3
#define COLMAE 8
#define TAMANHONAVEMAE 24

/*====================BARREIRA=======================*/

/* Sprites */
#define BARREIRA1 '~'
#define BARREIRA2 '^'
#define BARREIRA3 's'

#define QUANTIDADEBARREIRAS 4
#define LINHASBARREIRA      3
#define COLUNASBARREIRA     8
#define DELAYBARREIRA      10

/*====================PONTUACAO=======================*/

#define PONTUACAONAVEMAE 30
#define PONTUACAOALIEN   10
#define PONTUACAOBOMBA    3
#define PONTUACAOBARREIRA 1

/*====================FUNCOES=======================*/


/* Executa todas as funções do Ncurses para iniciar o jogo */
void configuracoes_iniciais();

/* Muda o sprite de todos os elementos de uma lista, os sprites vao de 0-4, sendo o 4 o sprite de explosão */
void atualiza_versao(t_lista *l);


/* Inicializa objeto (chamado de desenho) com todas as informações necessárias feitos para desenhos de qualquer tamanho > 1x1 */
void inicializa_desenho(t_sprite *d, int y, int x, int lin, int col, char c1[], char c2[], char c3[], char c4[], char c5[]);

/* Imprime qualquer desenho da tela */
void imprime_desenho(t_sprite *d, int versao);

/* Imprime uma lista inteira de desenhos */
void imprime_lista(t_lista *l);

/* Retira todos os desenhos com o estado == MORTO de uma lista */
void retira_mortos_lista(t_lista *l);

/* Faz todas as operações necessárias para aumentar a dificuldade do jogo conforme a passagem dos niveis */
void proximo_level(t_lista *aliens, t_lista *tiros, t_lista *bombas, t_lista *navemae, t_lista *jogador, t_lista *barreiras, int *level, int *delay_aliens, int *delay_bombas, int *maxtiros, int *dir, int *maxbombas);

/* Pausa o jogo */
void pausar();

/* Le do teclado as possibilidades de movimentação e comando */
void le_teclado(t_lista *jogador, t_lista *tiros, int maxtiros);

/* Confere apenas as coordenadas x e y, feito para comparar colisoes entre dois sprites 1x1 */
/* Retorna 1 caso haja uma colisao */
int detecta_colisao_simples(t_sprite a, t_sprite b);

/* Confere todas as coordendas de 2 sprites e detecta uma colisao, feito para comparar colisoes entre dois sprites de qualquer tamanho */
/* Retorna 1 caso haja uma colisao */
int detecta_colisao_completa(t_sprite a, t_sprite b);


/* Inicializa a lista jogador */
void inicializa_jogador(t_lista *jogador);

/* Move todos os elementos da lista jogador (apenas 1) para a direção desejada (LEFT ou RIGHT)*/
void move_jogador(t_lista *jogador, int dir);

/* Muda o estado do jogador para MORTO */
void mata_jogador(t_lista *jogador);


/* Inicializa os 55 aliens com sua posição, tamanho e corpo */
void inicializa_aliens(t_lista *aliens);

/* Move todos os aliens vivos para a direção desejada (LEFT ou RIGHT) */
/* Retorna 1 caso tenha encostado em uma borda vertical */
int move_aliens(t_lista *aliens, int *dir);

/* Confere a posição de todos os aliens com a posição das barreiras, do jogador e do chão para verificar colisões */
/* Retorna 0 caso tenha enconstado no jogador ou no fim da tela */
int checa_posicao_aliens(t_lista *aliens, t_lista *barreiras, t_lista *jogador);


/* Criar um tiro da posição do jogador e insere na lista de tiros */
void atirar(t_lista *tiros, t_lista *jogador, int maxtiros);

/* Cria uma bomba da posição de um alien aleatório e insere na lista de bombas */
void bombardear(t_lista *bombas, t_lista *aliens, int maxbombas);

/* Move para direção desejada (UP ou DOWN) uma bomba ou um tiro */
void move_projeteis(t_lista *projeteis, int dir);

/* Detecta a colisão entre uma lista de projeteis e uma lista de personagens */
/* Retorna a quantidade de colisões */
int detecta_projetil(t_lista *lista_a, t_lista *lista_b, int *score, int pontos);


/* Inicializa as barreiras nas posições corretas */
void inicializa_barreiras(t_lista *barreiras);

/* Inicializa a nave mãe no canto superior esquerdo da tela */
void inicializa_navemae(t_lista *navemae);

