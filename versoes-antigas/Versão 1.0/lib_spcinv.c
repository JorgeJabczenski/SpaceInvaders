#include "lib_spcinv.h"
#include "lib_graficos.h"

void configuracoes_iniciais(){

    srand(time(NULL)); /* Seed Aleatória */

    /*                  Configurações iniciais do ncurses                */
    /*                                                                   */
    initscr();              /* Inicia a tela                             */
    cbreak();               /* Desabilita o buffer de entrada            */
    noecho();               /* Não mostra os caracteres digitados        */
    nodelay(stdscr, TRUE);  /* Faz com que getch não aguarde a digitação */
    keypad (stdscr, TRUE);  /* Permite a leitura das setas               */
    curs_set(FALSE);        /* Não mostra o cursor na tela               */
    start_color();          /* Inicia as cores                           */
    clear();                /* Limpa a tela                              */

    /* Cria novos pares de cores */
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN,COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,COLOR_BLACK);
    init_pair(4, COLOR_BLUE,COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA ,COLOR_BLACK);
    init_pair(6, COLOR_CYAN,COLOR_BLACK);
    init_pair(7, COLOR_WHITE ,COLOR_BLACK);
}

void encerra(t_sprite *jogador){
    endwin();
    jogador->vivo = 0;  /* Mata o jogador */
}

void inicializa_desenho(t_sprite *d, int y, int x, int lin, int col, char c1[], char c2[]){

    int i, tam;

    /* Atribui os argumentos ao sprite passado */
    d->y    = y;
    d->x    = x;
    d->lin  = lin;
    d->col  = col;
    d->vivo = 1;

    /* Inicializa o corpo dos aliens (matriz) a partir de um vetor */
    tam = lin*col;
    for (i = 0; i < tam; i++)
        d->corpo[0][i/col][i%col] = c1[i];         /* Versao 1 */
    
    for (i = 0; i < tam; i++)
        d->corpo[1][i/col][i%col] = c2[i];         /* Versao 2 */

}

void imprime_desenho(t_sprite *d, int versao){
    
    int i,j;

    for (i = 0; i < d->lin; i++)
        for (j = 0; j < d->col; j++)
            mvaddch(i+d->y, j+d->x, d->corpo[versao][i][j]);
        
}

void inicializa_aliens(t_lista *aliens){

    int i, j;
    t_sprite d;

    for (i = 0; i < 11; i++){
        inicializa_desenho(&d, 5, i*7+2, LINALIENS, COLALIENS, ALIEN1A, ALIEN1B);
        insere_fim_lista(d, aliens);
    }
    for (i = 0; i < 2; i++){
        for (j = 0; j < 11; j++){
            inicializa_desenho(&d, 9+4*i ,j*7+2, LINALIENS, COLALIENS, ALIEN2A, ALIEN2B);
            insere_fim_lista(d, aliens);
        }
    }
    for (i = 0; i < 2; i++){
        for (j = 0; j < 11; j++){
            inicializa_desenho(&d, 17+4*i,j*7+2,LINALIENS, COLALIENS, ALIEN3A, ALIEN3B);
            insere_fim_lista(d, aliens);
        }
    }
}

void ajusta_velocidade_aliens(int *counter_aliens, int *delay_aliens, int incremento_aliens){

    *counter_aliens += 1;

    if ((*counter_aliens == incremento_aliens) && (*delay_aliens > 3)){
        *counter_aliens = 0;
        *delay_aliens  -= 1;
    }
}

void move_aliens(t_lista *aliens, int *dir){
    
    int i, tam, borda = 0;

    tamanho_lista(&tam, aliens);

    /* Move todos os aliens na direcao atual e detecta se bateram em alguma borda lateral */
    inicializa_atual_inicio(aliens);
    for (i = 0; i < tam; i++){
        move_item_atual_x(aliens, dir, &borda);
        incrementa_atual(aliens);
    }

    /* Se bateu em alguma borda lateral, muda de direcao e move todos os aliens pra baixo */
    if (borda){
        (*dir) *= -1;
        inicializa_atual_inicio(aliens);
        for (i = 0; i < tam; i++){
            move_item_atual_y(aliens, 1);
            incrementa_atual(aliens);
        }
    }
}

void checa_posicao_aliens(t_lista *aliens, t_lista *barreiras, t_sprite *jogador){

    int i,j;
    int qnt_aliens, qnt_barreiras;
    t_sprite alien, barreira;

    tamanho_lista(&qnt_aliens   ,    aliens);
    tamanho_lista(&qnt_barreiras, barreiras);

    inicializa_atual_inicio(aliens);
    for (i = 0; i < qnt_aliens; i++){
        consulta_item_atual(&alien, aliens);
        inicializa_atual_inicio(barreiras);

        for (j = 0; j < qnt_barreiras; j++){
            consulta_item_atual(&barreira, barreiras);

            /* Confere se os aliens bateram nas barreiras, se sim, remove as barreiras */
            if ((barreira.x >= alien.x) && (barreira.x < (alien.x + alien.col)) && (barreira.y <= (alien.y + alien.lin) - 1)) {
                remove_item_atual(barreiras);
            } else {
                incrementa_atual(barreiras);
            }
        }

        /* Checa se o alien encostou no jogador ou no fim da tela */
        if ((alien.x <= (jogador->x + jogador->col - 1) && ((alien.x + alien.col - 1) >= jogador->x) &&  ((alien.y + alien.lin - 1) >= jogador->y)) || ((alien.y + alien.lin - 1) >= LINHAS-1)){ 
            jogador->vivo = 0;
        }

        incrementa_atual(aliens);
    }

}

void move_projeteis(t_lista *projeteis, int dir){
    
    int i, tam;
    tamanho_lista(&tam, projeteis);
    t_sprite projetil;

    inicializa_atual_inicio(projeteis);
    for (i = 0; i < tam; i++){
        move_item_atual_y(projeteis, dir);
        consulta_item_atual(&projetil, projeteis);

        /* caso o projetil saia da tela, remove ele da lista */
        if (((dir == UP) && (projetil.y <= 1))  || ((dir == DOWN) && (projetil.y >= LINHAS-1))){
            remove_item_atual(projeteis);
        }
        incrementa_atual(projeteis);
    }

}

void atirar(t_lista *tiros, t_sprite *jogador, int maxtiros){
    
    int qntd_tiros;
    t_sprite tiro;

    tamanho_lista(&qntd_tiros, tiros);

    if (qntd_tiros < maxtiros){
        tiro.col = 1;
        tiro.lin = 1;
        tiro.corpo[0][0][0] = TIRO1;
        tiro.corpo[1][0][0] = TIRO2;
        tiro.x = jogador->x + (jogador->col/2);
        tiro.y = jogador->y;
        insere_fim_lista(tiro, tiros); 
    }
}

int detecta_tiro(t_lista *lista_a, t_lista *lista_b, int *score, int pontos){
    
    int i, j;
    int acertou = 0, contador = 0, tam_a, tam_b;
    t_sprite desenho_a, desenho_b, explosao;
            
    tamanho_lista(&tam_a,  lista_a);   /* Obtem o tamanho das listas */
    tamanho_lista(&tam_b,  lista_b);

    inicializa_atual_inicio(lista_a);

    for (i = 0; i < tam_a; i++){
        consulta_item_atual(&desenho_a, lista_a);
        inicializa_atual_inicio(lista_b);
            
        for (j = 0; j < tam_b; j++){
                acertou = 0;
                consulta_item_atual(&desenho_b, lista_b);
                
                /* Verifica todas as coordenadas para detectar a colisao entre todos os elementos das duas listas */
                if ((desenho_a.x >= desenho_b.x) && (desenho_a.x < (desenho_b.x + desenho_b.col)) && (desenho_a.y <= (desenho_b.y + desenho_b.lin)) && (desenho_a.y >= desenho_b.y)){
                    /* Caso tenha acertado qualquer coisa que nao seja uma barreira, cria uma explosao */
                    if (pontos != PONTUACAOBARREIRA){
                        inicializa_desenho(&explosao,desenho_a.y-3, desenho_a.x-1, LINEXPL, COLEXPL, EXPLOSAO, EXPLOSAO);
                        imprime_desenho(&explosao, 0);
                        refresh();
                        usleep(DELAYEXPLOSAO);
                    }
                    acertou = 1;
                    remove_item_atual(lista_a);
                    remove_item_atual(lista_b);
                    *score += pontos;
                    break;
                }
                incrementa_atual(lista_b); 
        }

        if (!acertou){
            incrementa_atual(lista_a);
        } else {
            clear();
            contador++;
        }
    }
    return contador;
}

void bombardear(t_lista *bombas, t_lista *aliens, int maxbombas){
    
    int i;
    int qnt_bombas, qnt_aliens, alien_atirador;
    t_sprite alien, bomba;
    
    tamanho_lista(&qnt_aliens, aliens);
    tamanho_lista(&qnt_bombas, bombas);

    /* Escolhe um alien aleatorio na lista para atirar a bomba */
    if ((qnt_bombas < maxbombas) && (qnt_aliens > 0)){
        alien_atirador = rand() % qnt_aliens;
        inicializa_atual_inicio(aliens);
        for (i = 0; i < alien_atirador; i++)
            incrementa_atual(aliens);
    
        /* Cria e Insere a bomba na lista */
        consulta_item_atual(&alien, aliens);
        bomba.col = 1;
        bomba.lin = 1;
        bomba.vivo = 1;
        bomba.x = alien.x + alien.col;
        bomba.y = alien.y + alien.lin;
        bomba.corpo[0][0][0] = BOMBA1;
        bomba.corpo[1][0][0] = BOMBA2;
        insere_fim_lista(bomba, bombas);
    }
}

void detecta_bomba(t_lista *bombas, t_lista *barreiras, t_sprite *jogador){

    int i, j;
    int qnt_bombas, qnt_barreiras, acertou; 
    t_sprite bomba, barreira;

    tamanho_lista(&qnt_bombas, bombas);
    inicializa_atual_inicio(bombas);
    for (i = 0; i < qnt_bombas; i++){
        acertou = 0;
        consulta_item_atual(&bomba, bombas);

        /* Verifica se a bomba atingiu o jogador */
        if ((bomba.x >= jogador->x) && (bomba.x < (jogador->x + jogador->col)) && (bomba.y >= jogador->y)){   
            jogador->vivo = 0;

        /* Verifica se atingiu as barreiras */
        } else {
            tamanho_lista(&qnt_barreiras, barreiras);
            inicializa_atual_inicio(barreiras);

            for (j = 0; j < qnt_barreiras; j++){
                consulta_item_atual(&barreira, barreiras);
                if ((barreira.x == bomba.x) && (barreira.y == bomba.y)){
                    remove_item_atual(barreiras);
                    remove_item_atual(bombas);
                    acertou = 1;
                } else {
                    incrementa_atual(barreiras);
                }
            }
        }
        if(!acertou)
            incrementa_atual(bombas);
    }

}

void inicializa_barreiras(t_lista *barreiras){

    int i,j,k;
    t_sprite peca;

    for (i = 16; i < 100; i += 21){
        for (j = 0; j < LINHASBARREIRA; j++){
            for (k = 0; k < COLUNASBARREIRA; k++){
                peca.lin  = 1;
                peca.col  = 1;
                peca.vivo = 1;
                peca.x = i  + k;
                peca.y = 31 + j;
                peca.corpo [0][0][0] = BARREIRA1;
                peca.corpo [1][0][0] = BARREIRA2;
                insere_fim_lista(peca, barreiras);
            }
        }
    }
}

void inicializa_navemae(t_lista *navemae){
    
    t_sprite navemae_sprite;

    inicializa_desenho(&navemae_sprite,1, 2, LINMAE, COLMAE, NAVEMAE1, NAVEMAE2);
    insere_fim_lista(navemae_sprite, navemae);
}

void move_navemae(t_lista *navemae){

    int borda = 0, dir = RIGHT;
    t_sprite nave;

    inicializa_atual_inicio(navemae);
    move_item_atual_x(navemae, &dir, &borda);
    consulta_item_atual(&nave, navemae);

    if (borda)
        remove_item_atual(navemae);

}

void proximo_level(t_lista *aliens, t_lista *tiros, t_lista *bombas, t_lista *navemae, t_lista *barreiras, int *rodada, int *delay_aliens, int *incremento_aliens, int *delay_bombas, int *maxtiros, int *counter_navemae, int *dir, int score, int aliens_mortos, int bombas_destruidas, int *maxbombas){
    
    int key = 0;

    *rodada += 1;  /* Aumenta a rodada */
    *dir = RIGHT;  /* Reseta a direção */
            
    if (*delay_aliens > LIMITEALIENS)  /* Ajusta a velocidade dos aliens */
        *delay_aliens -= 1;
    
    if (*incremento_aliens > LIMITEINCREMENTOALIENS)
        *incremento_aliens -= 2 ;
    
    if (*delay_bombas > 5)  /* Ajusta a velocidade e quantidade das bombas */
        *delay_bombas -= 1;
    *maxbombas += 1;
            
    if (*maxtiros > 3)      /* Diminui a quantidade de tiros */
        *maxtiros -= 1;

    *counter_navemae = APARICAONAVEMAE - 1; /* Ajusta o contador de aparicao da nave mae */

    destroi_lista     (tiros);  /* Reseta a lista de tiros */
    inicializa_lista  (tiros);

    destroi_lista    (bombas);  /* Reseta a lista de bombas */
    inicializa_lista (bombas);

    destroi_lista    (navemae); /* Reseta a nave mae */
    inicializa_lista (navemae);

    destroi_lista    (barreiras);     /* Reseta as barreiras */
    inicializa_lista (barreiras);
    inicializa_barreiras (barreiras);

    inicializa_aliens (aliens);       /* Inicia os aliens  */

    clear();
    mvprintw(5, (COLUNAS+20)/2 - 8, "Pontucao Atual %d", score);
    mvprintw(15,(COLUNAS+20)/2 - 9, "LEVEl %d Concluido!", *rodada);
    mvprintw(25,(COLUNAS+20)/2 - 8 ,"Aliens Mortos: %d", aliens_mortos);
    mvprintw(27,(COLUNAS+20)/2 - 10,"Bombas Destruidas: %d", bombas_destruidas);
    mvprintw(30,(COLUNAS+20)/2 - 12,"Aperte 'a' para continuar");
    refresh();

    nodelay(stdscr, FALSE);
    while(key != 'a')
        key = getch();
    nodelay(stdscr, TRUE);
    clear();

}

void imprimir_score(int score, int aliens_mortos, int bombas_destruidas, int rodada){
    mvprintw(2,104,"Score : %d", score);            /* Pontuação         */
    mvprintw(5, 104, "Aliens Mortos");              /* Alies Mortos      */ 
    mvprintw(6, 110, "%d", aliens_mortos);          /* Alies Mortos      */ 
    mvprintw(8, 107, "Bombas");                     /* Bombas Destruidas */
    mvprintw(9, 105, "Destruidas");                 /* Bombas Destruidas */
    mvprintw(10, 110, "%d", bombas_destruidas);     /* Bombas Destruidas */
    mvprintw(20, 107, "LEVEL %d", rodada + 1);      /* Level             */
    mvprintw(34,104,"p para pausar");               /* Instrucoes        */
    mvprintw(36,105,"q para sair");                 /* Instrucoes        */
}

void move_jogador(t_sprite *jogador, int dir, int *v_jogador){
    
    if ((dir == RIGHT) && ((jogador->x + jogador->col-1) < COLUNAS-1))
        jogador->x += 1;
    else if ((dir == LEFT) && (jogador->x > 1))
        jogador->x -= 1;

    *v_jogador = (*v_jogador + 1) % 2;

}

void imprime_lista(t_lista *l, int versao){
    
    int i, tamanho;
    t_sprite item;

    tamanho_lista(&tamanho, l);
    
    if (lista_vazia(l))
        return;

    inicializa_atual_inicio(l);

    for(i = 0; i < tamanho; i++){
        consulta_item_atual(&item,l);
        imprime_desenho(&item, versao);
        incrementa_atual(l);
    } 
    
    printf("\n");
}