#include "spcinv.h"

void imprime_desenho(desenho_t *d, int ver){
    
    int i,j;
    if (d->vivo){
        for (i = 0; i < d->linhas; i++){
            for (j = 0; j < d->colunas; j++){
                move(i+d->cord_y, j+d->cord_x);
                addch(d->corpo[ver][i][j]);
            }
        }
    }
}

void move_aliens(desenho_t alien[5][11], int *direcao){

    int i, j;
    int bateu_na_borda;

    bateu_na_borda = 0;

    for (i = 10; i >=0; i--){
        for (j = 0; j < 5; j++){
            if ( (alien[j][i].vivo) && (*direcao == 1) && (((alien[j][i].cord_x) + (alien[j][i].colunas )) >= COLUNAS)){
                bateu_na_borda = 1;
                break;
            }
            if ( (alien[j][i].vivo) && (*direcao == -1) && ((alien[j][i].cord_x) <= 0) ){
                bateu_na_borda = 1;
                break;
            }
        }
    }
           
    if (bateu_na_borda){
        *direcao *= -1;
        for (i = 0; i < 11; i++){
            for (j = 0; j < 5; j++){
                  alien[j][i].cord_y += 1;
            }
        }
    }

    for (i = 0; i < 11; i++){
        for (j = 0; j < 5; j++){
            alien[j][i].cord_x += *direcao;
        }
    }
}

void imprime_aliens(desenho_t alien[5][11], int ver){
    
    int i, j;
    
    for (i = 0; i < 5; i++){
        for (j = 0; j < 11; j++){
            if (alien[i][j].vivo)
                imprime_desenho(&alien[i][j],ver);
        }
    }
}

void inicializa_desenho(desenho_t *d, int lin, int col, char corpo1[], char corpo2[], int y, int x, int vivo){
    
    int i, tam;
    tam = lin*col;

    d->tamanho = tam;
    d->linhas = lin;
    d->colunas = col;
    d->cord_x = x;
    d->cord_y = y;
    d->vivo = 1;

    for (i = 0; i < tam; i++)
        d->corpo[0][i / col][i % col] = corpo1[i];
    for (i = 0; i < tam; i++)
        d->corpo[1][i / col][i % col] = corpo2[i]; 
}

void imprime_projetil(tiro_t projetil[], int tamanho ,char p){

    int i;

    for(i = 0; i < tamanho; i++){
        move(projetil[i].cord_y, projetil[i].cord_x);
        addch(p);
    }

}

void inicializa_barreira(barreira_t bar[], int linbar, int colbar){

    int i, j, k;

    for (i = 0; i < QUANTIDADEBARREIRAS; i++){
        bar[i].lin = linbar;
        bar[i].col = colbar;
        bar[i].cord_x = 7 + (bar[i].col * i*3); /* Coordenada X Da Barreira */
        bar[i].cord_y = 31;                     /* Coordenada Y Da Barreira */
        for (j = 0; j < bar[i].lin; j++){
            for (k = 0; k < bar[i].col; k++){
                bar[i].corpo[j][k].vivo = 1;
                bar[i].corpo[j][k].cord_x = bar[i].cord_x + k;
                bar[i].corpo[j][k].cord_y = bar[i].cord_y + j;
                bar[i].corpo[j][k].c = 'Y';
            }
        }      
    }
}

void imprime_barreira(barreira_t barreira[4]){

    int i, j, k;

    for (i = 0; i < 4; i++){
        for (j = 0; j < barreira[i].lin; j++){
            for (k = 0; k < barreira[i].col; k++){
                if (barreira[i].corpo[j][k].vivo){
                    move(barreira[i].corpo[j][k].cord_y, barreira[i].corpo[j][k].cord_x);
                    addch(barreira[i].corpo[j][k].c);
                }
            }
        }      
    }
}