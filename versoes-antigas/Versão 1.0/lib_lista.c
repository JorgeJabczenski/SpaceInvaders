#include "lib_lista.h"

int inicializa_lista(t_lista *l){
    
    t_nodo *first, *last;
    
    first = (t_nodo *) malloc (sizeof(t_nodo));
    if (first == NULL)
        return 0;

    last = (t_nodo *) malloc (sizeof(t_nodo));
    if (last == NULL){
        free(first);
        return 0;
    }
    
    l->ini = first;
    first->prox = last;
    first->prev = NULL;

    l->fim = last;
    last->prox = NULL;
    last->prev = first;
    
    l->atual = NULL;
    
    l->tamanho = 0;

    return 1;
}

int lista_vazia(t_lista *l){
    return ((l->tamanho) ? 0 : 1 );
}

int tamanho_lista(int *tam, t_lista *l){
    *tam = l->tamanho;
    return 1;
}

int insere_fim_lista(t_sprite item, t_lista *l){

    t_nodo *new;
    new = (t_nodo *) malloc (sizeof(t_nodo));
    if (new == NULL)
        return 0;

    new->desenho = item;

    new->prox = l->fim;
    new->prev = l->fim->prev;
    l->fim->prev->prox = new;
    l->fim->prev = new;

    l->tamanho++;

    return 1;
}

int remove_inicio_lista(t_sprite *item, t_lista *l){
    
    if (lista_vazia(l)){
        return 0;
    }

    *item = l->ini->prox->desenho;

    l->ini->prox = l->ini->prox->prox;
    free(l->ini->prox->prev);
    l->ini->prox->prev = l->ini;

    l->tamanho--;

    return 1;
}

void destroi_lista(t_lista *l){
    
    int i, tam;
    t_sprite lixo;

    tam = l->tamanho;

    for (i = 0; i < tam; i++)
        remove_inicio_lista(&lixo, l);


    free(l->fim);
    free(l->ini);

}

int inicializa_atual_inicio(t_lista *l){
    
    if (lista_vazia(l))
        return 0;
    
    l->atual = l->ini->prox;

    return 1;
}

int inicializa_atual_fim(t_lista *l){
    
    if (lista_vazia(l))
        return 0;
    
    l->atual = l->fim->prev;

    return 1;
}

int incrementa_atual(t_lista *l){
    
    if (lista_vazia(l) || (l->atual == l->fim->prev))
        return 0;
    
    l->atual = l->atual->prox;

    return 1;
}

int decrementa_atual(t_lista *l){
   
    if (lista_vazia(l) || l->atual == l->ini->prox)
        return 0;
    
    l->atual = l->atual->prev;

    return 1;
}

int consulta_item_atual(t_sprite *item, t_lista *l){
    if (lista_vazia(l)){
        return 0;
    } 

    *item = l->atual->desenho;

    return 1;
}

int move_item_atual_x(t_lista *l, int *dir, int *borda){

    l->atual->desenho.x += (*dir);

    if ((*borda != 1) && ((l->atual->desenho.x <= 1) || (l->atual->desenho.x + l->atual->desenho.col >= 99))){
        *borda = 1;
    }
    return 1;
}

int move_item_atual_y(t_lista *l, int dir){
    l->atual->desenho.y += dir;
    return 1;
}

int remove_item_atual(t_lista *l){
    
    if (lista_vazia(l)){
        return 0;
    } 

    t_nodo *p;

    p = l->atual;

    l->atual->prev->prox = l->atual->prox;
    l->atual->prox->prev = l->atual->prev;


    if (l->atual->prox == l->fim){
        l->atual = l->atual->prev;
    } else {
        l->atual = l->atual->prox;
    }

    free(p);
    l->tamanho--;
    return 1;
}

