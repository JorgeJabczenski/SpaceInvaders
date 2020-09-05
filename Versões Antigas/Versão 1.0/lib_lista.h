#include <stdio.h>
#include <stdlib.h>

struct t_sprite{
  int x;
  int y;
  int lin;
  int col;
  int vivo;
  int corpo[2][3][8];
};
typedef struct t_sprite t_sprite;

struct t_nodo {
    t_sprite desenho;
    struct t_nodo *prox;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;


int inicializa_lista (t_lista *l);
int lista_vazia (t_lista *l);
int tamanho_lista (int *tam, t_lista *l);
int insere_fim_lista (t_sprite  item, t_lista *l);
int remove_inicio_lista (t_sprite *item, t_lista *l);
void destroi_lista (t_lista *l);

int inicializa_atual_inicio (t_lista *l);
int inicializa_atual_fim (t_lista *l);
int incrementa_atual (t_lista *l);
int decrementa_atual (t_lista *l);
int consulta_item_atual (t_sprite *item, t_lista *l);
int move_item_atual_x (t_lista *l, int *dir, int *borda);
int move_item_atual_y (t_lista *l, int dir);
int remove_item_atual (t_lista *l);
int apaga_item_atual (t_lista *l);

void imprime_lista (t_lista *l, int versao);