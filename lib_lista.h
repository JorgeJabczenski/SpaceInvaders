#include <stdio.h>
#include <stdlib.h>

struct s_sprite
{
  int x;      /* Posição x  */
  int y;      /* Posição Y  */
  int lin;    /* Nr Linhas  */
  int col;    /* Nr Colunas */
  int versao; /* Versao do Sprite */
  int estado;
  int corpo[5][3][8];
};
typedef struct s_sprite t_sprite;

struct s_nodo
{
  t_sprite desenho;
  struct s_nodo *prox;
  struct s_nodo *prev;
};
typedef struct s_nodo t_nodo;

struct s_lista
{
  t_nodo *ini;
  t_nodo *atual;
  t_nodo *fim;
  int tamanho;
};
typedef struct s_lista t_lista;

int inicializa_lista(t_lista *l);

int lista_vazia(t_lista *l);

int tamanho_lista(int *tam, t_lista *l);

int insere_fim_lista(t_sprite item, t_lista *l);

int remove_inicio_lista(t_sprite *item, t_lista *l);

void destroi_lista(t_lista *l);

int inicializa_atual_inicio(t_lista *l);

int incrementa_atual(t_lista *l);

int decrementa_atual(t_lista *l);

int consulta_item_atual(t_sprite *item, t_lista *l);

int move_item_atual(t_lista *l, int diry, int dirx, int *bordax, int *borday);

int remove_item_atual(t_lista *l);

int esvazia_lista(t_lista *l);

int estado_atual(t_lista *l);

int muda_estado_atual(t_lista *l, int estado);

int versao_atual(t_lista *l);

int muda_versao_atual(t_lista *l, int versao);