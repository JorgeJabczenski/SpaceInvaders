/*      Autor       : Jorge Lucas Vicilli Jabczenski                 */
/*   Last update    : 16/11/2019                                     */
/*     Github       : www.github.com/JorgeJabczenski                 */
/*  Game Repository : www.github.com/JorgeJabczenski/space-invaders  */

#include "lib_spcinv.h"

int main(){

    int delay_aliens      = DELAYALIENS;
    int delay_tiros       = DELAYTIROS;
    int delay_bombas      = DELAYBOMBAS;
    int delay_navemae     = DELAYNAVEMAE;
    int incremento_aliens = INCREMENTOALIENS;
    int maxtiros          = MAXTIROS;
    int maxbombas         = MAXBOMBAS;

    int nlin, ncol, key, direcao = RIGHT, score = 0, rodada = 0;
    int v_jogador = 0, v_aliens = 0, v_tiro = 0, v_bomba = 0, v_navemae = 0, v_barreira = 0;
    int counter_aliens = 0, counter_navemae = APARICAONAVEMAE - 1, counter = 0;
    int aliens_mortos = 0, bombas_destruidas = 0;
    int tam_navemae = 0, qnt_aliens = 0;

    t_lista aliens, tiros, bombas, barreiras, navemae;

    t_sprite jogador;

/*=======================================================================*/
    
    /* Configurações iniciais do ncurses*/
    configuracoes_iniciais();
    
    

    /* Confere o tamanho da tela */
    getmaxyx(stdscr, nlin, ncol);
    if ((nlin < LINHAS) || (ncol < COLUNAS+20)){
        endwin();
        printf("O terminal deve possuir 38 linhas e 120 colunas\n");
        return 1;
    }

    imprime_tela_inicio();  

    inicializa_lista(&aliens);              /*  Inicializa o TAD Lista  */
    inicializa_lista(&tiros);              
    inicializa_lista(&bombas);
    inicializa_lista(&barreiras);
    inicializa_lista(&navemae);

/*=========================================================================*/

    /* Inicializa desenho e posição dos aliens */
    inicializa_aliens(&aliens);

    /* Inicializa desenho e posição do Jogador */
    inicializa_desenho(&jogador, (LINHAS-LINJOGADOR)-1, (COLUNAS/2 - (COLJOGADOR/2+1)), LINJOGADOR, COLJOGADOR, JOGADOR1, JOGADOR2);

    /* Inicializa as barreias */
    inicializa_barreiras(&barreiras);


/*************************************************************************/
    /* Loop principal do jogo */
    while(jogador.vivo){
    
        /* Movimento do Jogador */
        
        key = getch();
        
        if (key == ' '){
            /* Atira */
            atirar(&tiros, &jogador, maxtiros);

        } else if (key == KEY_LEFT){
            move_jogador(&jogador, LEFT, &v_jogador);

        } else if (key == KEY_RIGHT){
             move_jogador(&jogador, RIGHT, &v_jogador);

        } else if (key == 'q'){
            /* Sai do jogo */
            encerra(&jogador);

        } else if (key == 'p'){
            /* Pausa o jogo */
            nodelay(stdscr, FALSE);
            key = 0;
            mvprintw(0,47,"PAUSADO");
            while(key != 'p')
                key = getch();
            nodelay(stdscr, TRUE);
            clear();

        }
        
        tamanho_lista(&qnt_aliens, &aliens);
    
        /* Passa para a proxima fase ao matar os aliens */
        if (qnt_aliens == 0){
            proximo_level(&aliens, &tiros, &bombas, &navemae, &barreiras, &rodada, &delay_aliens, &incremento_aliens, &delay_bombas, &maxtiros, &counter_navemae, &direcao, score, aliens_mortos, bombas_destruidas, &maxbombas);
        }

        /* Movimento dos Aliens */
        if (!(counter % delay_aliens)){
            
            /* Aumenta a velocidade dos aliens ao passar do tempo */
            ajusta_velocidade_aliens(&counter_aliens, &delay_aliens, incremento_aliens);
            
            /* Movimenta os aliens */
            move_aliens(&aliens, &direcao);

            /* Verifica se os aliens baterram nas barreiras ou no jogador ou no chão*/
            checa_posicao_aliens(&aliens, &barreiras, &jogador);
            v_aliens = (v_aliens + 1) % 2; /* Muda o rostinho do alien */

        }

        /* Movimento e detecção das bombas */
        if (!(counter % delay_bombas)){

            /* Aliens atiram as bombas */
            bombardear(&bombas, &aliens, maxbombas);

            /* Cuida da movimentação das bombas */
            move_projeteis(&bombas, DOWN);

            /* Verifica se enconstou nas barreias ou no jogador */
            detecta_bomba(&bombas, &barreiras, &jogador);

            v_bomba = (v_bomba + 1) % 2;

        }

        /* Controles da Nave Mãe */
        if (!(counter % delay_navemae)){
            
            tamanho_lista(&tam_navemae, &navemae);
            counter_navemae++;

            /* Calcula a recorrencia de aparicao da nave mae */
            if (!(counter_navemae % APARICAONAVEMAE)){
                counter_navemae = 0;
                inicializa_navemae(&navemae);
                erase();
            }
            
            /* Caso exista a nave mae, move-la */
            if (tam_navemae){
                move_navemae(&navemae);
                erase();
            }
            
            v_navemae  = (v_navemae + 1) % 2; /* Muda o desenho da nave mae */
        }
       
        /* Movimento e detecção dos tiros */
        if (!(counter % delay_tiros)){

            /* Move os tiros */
            move_projeteis(&tiros, UP);   
            
            /* Verifica se encostou nas barreiras  */
            detecta_tiro(&tiros, &barreiras, &score, PONTUACAOBARREIRA * rodada*2);

            /* Verifica se encontrou alguma bomba  */
            bombas_destruidas += detecta_tiro(&tiros, &bombas, &score, PONTUACAOBOMBA + rodada*rodada);

            /* Verifica se encostou em algum alien */
            aliens_mortos += detecta_tiro(&tiros, &aliens, &score, PONTUACAOALIEN + rodada*rodada);
            
            /* Verifica se encontrou a nave mae    */
            detecta_tiro(&tiros, &navemae, &score, PONTUACAONAVEMAE + rodada*rodada);

            v_tiro = (v_tiro + 1) % 2; /* Muda a desenho do tiro */

        }

         
        /*            Imprimir todos os elementos da tela           */
        /*                                                          */
        erase();
        attron(COLOR_PAIR(7));              
        imprime_lista  (&tiros,         v_tiro);        /*   Tiros   */
        attron(COLOR_PAIR(1)); 
        imprime_desenho(&jogador,    v_jogador);        /*  Jogador  */
        attron(COLOR_PAIR(3));
        imprime_lista  (&bombas,       v_bomba);        /*  Bombas   */
        attron(COLOR_PAIR(2));
        imprime_lista  (&aliens,      v_aliens);        /*  Aliens   */
        imprime_lista  (&barreiras, v_barreira);        /* Barreiras */
        attron(COLOR_PAIR(4));
        imprime_lista  (&navemae,    v_navemae);        /* Nave Mãe  */
        attron(COLOR_PAIR(6));
        imprimir_score(score, aliens_mortos, bombas_destruidas, rodada);
        refresh();
        desenha_layout();               /* Desenha a "casca" do jogo */
        refresh();
        
        /* Controla a variável contadora do jogo */
        if (counter >= 65000)
            counter = 0;
        counter++;

        usleep(DELAY);
    }
/*************************************************************************/
    
    imprime_tela_final(score, aliens_mortos, bombas_destruidas, rodada);

    endwin();                /* Encerra a janela do jogo */
    printf("\033[H\033[J");  /* Limpa o terminal ao terminar o jogo */
    destroi_lista (&aliens);
    destroi_lista  (&tiros);
    destroi_lista (&bombas);
    destroi_lista(&navemae);

    return 0;
}   