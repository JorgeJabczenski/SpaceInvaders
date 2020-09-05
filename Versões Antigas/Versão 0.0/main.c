#include "spcinv.h"
#include <stdio.h>

desenho_t alien[5][11], navinha, nave_mae;

tiro_t tiros[MAXTIROS];
int quantidade_tiros = 0;

tiro_t bombas[MAXBOMBAS];
int quantidade_bombas = 0;

barreira_t barreira[4];

int nlin, ncol, direcao = 1;

int main(){


    int i, j, k, l, m;   /* Variaveis de controle para os loops*/
    int versao = 0;      /* Variavel da versao dos aliens*/
    unsigned long long int counter = 0;
    unsigned long long int counter_aliens = 0;
    int delay_aliens = DELAYALIENS;
    int delay_tiros  = DELAYTIROS;
    int delay_bombas = DELAYBOMBAS;
    int linhas_barreira = LINHASBARREIRA;
    int colunas_barreira = COLUNASBARREIRA;
    int key;

    srand(time(NULL)); /* Seed Aleatória */

    /* Configurações iniciais do ncurses */
    initscr();              /* inicia a tela                             */
    cbreak();               /* desabilita o buffer de entrada            */
    noecho();               /* não mostra os caracteres digitados        */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad (stdscr, TRUE);  /* permite a leitura das setas               */
    curs_set(FALSE);        /* não mostra o cursor na tela               */
    clear();

    /* Confere o tamanho da tela */
    getmaxyx(stdscr, nlin, ncol);
    if ((nlin < LINHAS) || (ncol < COLUNAS)){
        endwin();
        printf("O terminal deve possuir 38 linhas e 100 colunas\n");
        return 1;
    }


    /* Inicializa os valores de todos os aliens */
    for (i = 0; i < 11; i++){
        inicializa_desenho(&alien[0][i],3,5,ALIEN1A,ALIEN1B,4 ,i*7,1);
        inicializa_desenho(&alien[1][i],3,5,ALIEN2A,ALIEN2B,8 ,i*7,1);
        inicializa_desenho(&alien[2][i],3,5,ALIEN2A,ALIEN2B,12,i*7,1);
        inicializa_desenho(&alien[3][i],3,5,ALIEN3A,ALIEN3B,16,i*7,1);
        inicializa_desenho(&alien[4][i],3,5,ALIEN3A,ALIEN3B,20,i*7,1);
    }

    /* Inicializa a nave mãe */
    inicializa_desenho(&nave_mae,3,8,NAVEMAE1,NAVEMAE2, 1, 0, 1);

    /* Inicializa a nave do jogador */
    inicializa_desenho(&navinha, 2, 5, NAVINHA, NAVINHA,36, 48, 1);

    /* Inicializa as barreiras */
    inicializa_barreira(barreira, linhas_barreira, colunas_barreira);

    
    /* Loop Principal do Jogo */
    while(navinha.vivo){

        /* Checa os movimentos do jogador */
        key = getch();

        if (key == ' '){
            /* Atira */
            if(quantidade_tiros < MAXTIROS){
                tiros[quantidade_tiros].cord_x = navinha.cord_x+2;
                tiros[quantidade_tiros].cord_y = navinha.cord_y-1;
                quantidade_tiros++;
            }
        } else if (key == KEY_LEFT){
            if (navinha.cord_x > 0)
                navinha.cord_x--;
        } else if (key == KEY_RIGHT){
            if ((navinha.cord_x + navinha.colunas) < 100)
                navinha.cord_x++;
        } else if (key == 'q'){
            endwin();
            exit(0);
        }

        /* Controla o Movimento dos Tiros */
        if (!(counter % delay_tiros)){
            for (i = 0; i < quantidade_tiros; i++){
                tiros[i].cord_y--;
                if (tiros[i].cord_y <= 0){ /* Caso o tiro tenha chegado na borda superior, deleta ele e "shfita" o resto do vetor*/
                    for (j = 0; j < quantidade_tiros-1; j++){
                        tiros[j] = tiros[j+1];
                    }
                    quantidade_tiros--;
                }
            }

            /* Checa pra ver se os tiros acertaram os aliens ou a nave mãe */
            for (i = 0; i < quantidade_tiros; i++){
                for (j = 4; j >= 0; j--){
                    for (k = 0; k < 11; k++){
                        if ((alien[j][k].vivo) && (tiros[i].cord_y <= alien[j][k].cord_y + 2) && (tiros[i].cord_y >= alien[j][k].cord_y) && (tiros[i].cord_x >= alien[j][k].cord_x) && (tiros[i].cord_x <= (alien[j][k].cord_x + 4))){
                            alien[j][k].vivo = 0;
                            for (l = i; l < quantidade_tiros-1; l++){
                                tiros[i] = tiros[i+1];
                            }
                            quantidade_tiros--;
                        }
                    }
                }
                if ((nave_mae.vivo) && (tiros[i].cord_y <= nave_mae.cord_y + nave_mae.linhas) && (tiros[i].cord_x >= nave_mae.cord_x) && (tiros[i].cord_x <= nave_mae.cord_x + nave_mae.colunas)){
                    nave_mae.vivo = 0;
                }
            }

        }    

        /* Controla o tempo de mexer os aliens */
        if (!(counter % delay_aliens)){
            counter_aliens++;
            if (counter_aliens == 100 && delay_aliens > 5){ /* Controla o quão rápido os aliens vao se mexer */
                counter_aliens = 0;
                delay_aliens--;
            }
            move_aliens(alien, &direcao);
            versao = (versao+1) % 2; /* muda a carinha do alien */

            /* Controle de BOMBAS */
            if ((quantidade_bombas < MAXBOMBAS)){
                int randA = rand() % 5 ;
                int randB = rand() % 11;
                if (alien[randA][randB].vivo){
                    bombas[quantidade_bombas].cord_x = alien[randA][randB].cord_x + 2;
                    bombas[quantidade_bombas].cord_y = alien[randA][randB].cord_y + 3;
                    quantidade_bombas++;
                }
                
            }
        }
       
        /* Move as Bombas */
        if (!(counter % delay_bombas)){
            for (i = 0; i < quantidade_bombas; i++){
                bombas[i].cord_y++;
                if (bombas[i].cord_y > LINHAS){
                    for (j = i; j < quantidade_bombas-1; j++){
                        bombas[j] = bombas[j+1];
                    }
                    quantidade_bombas--;
                }
            }

            /* Checa pra ver se as bombas atingiram a barreira */
            for (i = 0; i < quantidade_bombas; i++){
                for (j = 0; j < QUANTIDADEBARREIRAS; j++){
                    if (bombas[i].cord_y >= barreira[j].cord_y){
                        for (k = 0; k < 3; k++){
                            for (l = 0; l < 8; l++){
                                if ((barreira[j].corpo[k][l].vivo) && (bombas[i].cord_y >= barreira[j].corpo[k][l].cord_y) && (bombas[i].cord_x == barreira[j].corpo[k][l].cord_x)){
                                    barreira[j].corpo[k][l].vivo = 0;
                                    for (m = i; m < quantidade_bombas-1; m++){
                                        bombas[m] = bombas[m+1];
                                        quantidade_bombas--;
                                    }
                                }
                            }
                        }
                    }
                }
            }   

            /* Checa pra ver se as bombas atingiram o jogador */
            for (i = 0; i < quantidade_bombas; i++){
                if ((bombas[i].cord_y == navinha.cord_y) && (bombas[i].cord_x >= navinha.cord_x) && (bombas[i].cord_x <= navinha.cord_x + navinha.colunas)){
                    navinha.vivo = 0;
                }
                
            }
                            
        }
        
        /* Checa pra ver se os aliens encostaram no jogador ou no chão*/
        for (k = 0; k < 5; k++){
            for (i = 0; i < 11; i++){
                if(alien[k][i].vivo){
                    if (((alien[k][i].cord_y + alien[k][i].linhas == navinha.cord_y) && 
                    (alien[k][i].cord_x >= navinha.cord_x) && 
                    ((alien[k][i].cord_x + alien[k][i].colunas) <= (navinha.cord_x + navinha.colunas))) || 
                    ((alien[k][i].cord_y + alien[k][i].linhas) >= LINHAS)){
                        navinha.vivo = 0;
                    }  
                }
            }
        }

        /* Controla o tempo de mexer a nave mãe */
        
        /* Imprime Aliens */
        imprime_aliens(alien, versao);

        /* Imprime Nave Mãe */
        imprime_desenho(&nave_mae, versao);  

        /* Imprime Jogador */
        imprime_desenho(&navinha, 0);

        /* Imprime Tiros */
        imprime_projetil(tiros, quantidade_tiros, '|');

        /* Imprime Bombas */
        imprime_projetil(bombas, quantidade_bombas, '$');

        /* Imprime Barreiras */
        imprime_barreira(barreira);

        /* Controla a variavel de contador do jogo */
        if (counter >= 4294967290) {
            counter = 0;
        }
        counter++;

        refresh();
        usleep(10000); /* Delay do jogo */
        clear();       /* Limpa a Tela  */
    }

    endwin();
    printf("Você Morreu!\n");
    return 0;

}
