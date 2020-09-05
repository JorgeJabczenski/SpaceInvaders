#include <stdio.h>
#include <stdlib.h>

struct peca_barreira_s{
    int cord_x;
    int cord_y;
    int vivo;
    char c;
};
typedef struct peca_barreira_s peca_barreira_t;

struct barreira_s{
    int vivo;
    int cord_x;
    int cord_y;
    int lin;
    int col;
    peca_barreira_t corpo[3][8];
};
typedef struct barreira_s barreira_t;

void inicializa_barreira(barreira_t bar[]){

    int i, j, k;

    for (i = 0; i < 4; i++){
        bar[i].cord_x = 7 + (bar[i].col * i); /* Coordenada X Da Barreira */
        bar[i].cord_y = 31;                   /* Coordenada Y Da Barreira */
        bar[i].lin = 3;
        bar[i].col = 8;
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


barreira_t b[4];

int main(){

    inicializa_barreira(&b[1]);
    printf("%d\n", b[3].corpo[0][0].cord_x);

    return 0;

}