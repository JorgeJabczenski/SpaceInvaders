#include "lib_spcinv.h"

void configuracoes_iniciais()
{
    srand(time(NULL)); /* Seed Aleatória */

    /*                  Configurações iniciais do ncurses                */
    /*                                                                   */
    initscr();             /* Inicia a tela                             */
    cbreak();              /* Desabilita o buffer de entrada            */
    noecho();              /* Não mostra os caracteres digitados        */
    nodelay(stdscr, TRUE); /* Faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);  /* Permite a leitura das setas               */
    curs_set(FALSE);       /* Não mostra o cursor na tela               */
    start_color();         /* Inicia as cores                           */
    clear();               /* Limpa a tela                              */

    /* Cria novos pares de cores */
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_GREEN, 0,720,240);
    init_color(COLOR_MAGENTA,1000, 204, 612);
    init_color(COLOR_WHITE,1000, 1000, 1000);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void atualiza_versao(t_lista *l)
{
    int i, tam;

    tamanho_lista(&tam, l);
    inicializa_atual_inicio(l);

    for (i = 0; i < tam; i++)
    {
        l->atual->desenho.versao = (l->atual->desenho.versao + 1) % 4;
        incrementa_atual(l);
    }
}

void inicializa_desenho(t_sprite *d, int y, int x, int lin, int col, char c1[], char c2[], char c3[], char c4[], char c5[])
{
    int i, tam;

    /* Atribui os argumentos ao sprite passado */
    d->y = y;
    d->x = x;
    d->lin = lin;
    d->col = col;
    d->estado = VIVO;
    d->versao = 0;

    /* Inicializa o corpo dos aliens (matriz) a partir de um vetor */
    tam = lin * col;
    for (i = 0; i < tam; i++)
        d->corpo[0][i / col][i % col] = c1[i]; /* Versao 1 */

    for (i = 0; i < tam; i++)
        d->corpo[1][i / col][i % col] = c2[i]; /* Versao 2 */

    for (i = 0; i < tam; i++)
        d->corpo[2][i / col][i % col] = c3[i]; /* Versao 3 */

    for (i = 0; i < tam; i++)
        d->corpo[3][i / col][i % col] = c4[i]; /* Versao 4 */

    for (i = 0; i < tam; i++)
        d->corpo[4][i / col][i % col] = c5[i]; /* Versao 5 (MORTA) */
}

void imprime_desenho(t_sprite *d, int versao)
{
    int i, j;

    for (i = 0; i < d->lin; i++)
        for (j = 0; j < d->col; j++)
            mvaddch(i + d->y, j + d->x, d->corpo[versao][i][j]);
}

void imprime_lista(t_lista *l)
{
    int i, tamanho;
    t_sprite item;

    if (lista_vazia(l))
        return;

    tamanho_lista(&tamanho, l);
    inicializa_atual_inicio(l);

    for (i = 0; i < tamanho; i++)
    {
        consulta_item_atual(&item, l);
        imprime_desenho(&item, versao_atual(l)); /* Imprime a versao atual  */
        incrementa_atual(l);
    }
}

void retira_mortos_lista(t_lista *l)
{
    int tam, i;

    tamanho_lista(&tam, l);
    inicializa_atual_inicio(l);

    for(i = 0; i < tam; i++){
        if (estado_atual(l) == MORTO)
            remove_item_atual(l);
        else 
            incrementa_atual(l);
    }
}

void proximo_level(t_lista *aliens, t_lista *tiros, t_lista *bombas, t_lista *navemae, t_lista *jogador, t_lista *barreiras, int *level, int *delay_aliens, int *delay_bombas, int *maxtiros, int *dir, int *maxbombas)
{
    *level += 1;  /* Aumenta a rodada */
    *dir = RIGHT; /* Reseta a direção */

    /* Aumenta a velocidade inicial dos aliens a cada fase que passa até chegar no limite */
    if(*level < DELAYALIENS - LIMITEALIENS)
    	*delay_aliens = DELAYALIENS - *level;
    else 
    	*delay_aliens = LIMITEALIENS;


    if (*delay_bombas > LIMITEBOMBAS) /* Ajusta a velocidade e quantidade das bombas */
        *delay_bombas -= 1;
    *maxbombas += 1;

    if (*maxtiros > MINTIROS) /* Diminui a quantidade de tiros */
        *maxtiros -= 1;

    /* Esvazia as listas e as inicia para prepará-las para uma nova fase */
    esvazia_lista(tiros);
    esvazia_lista(bombas);
    esvazia_lista(navemae);
    esvazia_lista(jogador);
    inicializa_jogador(jogador);
    esvazia_lista(barreiras);
    inicializa_barreiras(barreiras);
    inicializa_aliens(aliens); /* Inicia os aliens  */
}

void pausar()
{
    int key = 0;
    nodelay(stdscr, FALSE);
    mvprintw(0, 47, "PAUSADO");
    while (key != 'p')
        key = getch();
    nodelay(stdscr, TRUE);
    clear();
}

void le_teclado(t_lista *jogador, t_lista *tiros, int maxtiros)
{
    int key;

    key = getch();
    if ((key == KEY_RIGHT) || (key == 'd') || (key == 'l')){
        move_jogador(jogador, RIGHT);

    } else if ((key == KEY_LEFT)||(key == 'a')|| (key == 'k')){
        move_jogador(jogador, LEFT);

    } else if ((key == KEY_UP)||(key == 'w') || (key == ' ')|| (key == 'z')){
        atirar(tiros, jogador, maxtiros);

    } else if (key == 'p'){
        pausar();

    } else if (key == 'q'){
        mata_jogador(jogador);
    }
}

int detecta_colisao_simples(t_sprite a, t_sprite b)
{
    return ((a.x == b.x) && (a.y <= b.y));
}

int detecta_colisao_completa(t_sprite a, t_sprite b)
{
    return ((a.x < b.x + b.col) && (a.x + a.col > b.x) && (a.y + a.lin > b.y) && (a.y < b.y + b.lin));
}

/*&&&&&&&&&&&&&&&&&& JOGADOR &&&&&&&&&&&&&&&&&&*/

void inicializa_jogador(t_lista *jogador)
{
    t_sprite desenho;

    inicializa_desenho(&desenho, (LINHAS - LINJOGADOR) - 1, (COLUNAS / 2 - (COLJOGADOR / 2 + 1)), LINJOGADOR, COLJOGADOR, JOGADOR1, JOGADOR2, JOGADOR3, JOGADOR4, JOGADOR4);
    insere_fim_lista(desenho, jogador);
}

void move_jogador(t_lista *jogador, int dir)
{
    int bordax = 0, borday = 0;
    t_sprite desenho_jogador;

    inicializa_atual_inicio(jogador);
    consulta_item_atual(&desenho_jogador, jogador);
    if ((dir == RIGHT) && ((desenho_jogador.x + desenho_jogador.col) < COLUNAS))
        move_item_atual(jogador, STAY, RIGHT, &bordax, &borday);

    else if ((dir == LEFT) && ((desenho_jogador.x > 1)))
        move_item_atual(jogador, STAY, LEFT, &bordax, &borday);
}

void mata_jogador(t_lista *jogador)
{
    inicializa_atual_inicio(jogador);
    muda_estado_atual(jogador, MORTO);
}

/*&&&&&&&&&&&&&&&&&& ALIENS &&&&&&&&&&&&&&&&&&*/

void inicializa_aliens(t_lista *aliens)
{

    int i, j;
    t_sprite d;

    /* inicializa primeira linha de aliens */
    for (i = 0; i < 11; i++)
    {
        inicializa_desenho(&d, 5, i * 7 + 1, LINALIENS, COLALIENS, ALIEN1A, ALIEN1B, ALIEN1C, ALIEN1D, EXPLOSAO);
        insere_fim_lista(d, aliens);
    }
    /* inicializa segunda e terceira linha de aliens */
    for (i = 0; i < 2; i++)
        for (j = 0; j < 11; j++)
        {
            inicializa_desenho(&d, 9 + 4 * i, j * 7 + 1, LINALIENS, COLALIENS, ALIEN2A, ALIEN2B, ALIEN2C, ALIEN2D, EXPLOSAO);
            insere_fim_lista(d, aliens);
        }
    /* inicializa quarta e quinta linha de aliens */
    for (i = 0; i < 2; i++)
        for (j = 0; j < 11; j++)
        {
            inicializa_desenho(&d, 17 + 4 * i, j * 7 + 1, LINALIENS, COLALIENS, ALIEN3A, ALIEN3B, ALIEN3C, ALIEN3D, EXPLOSAO);
            insere_fim_lista(d, aliens);
        }
}

int move_aliens(t_lista *aliens, int *dir)
{
    int i, tam, bordax = 0, borday = 0;

    tamanho_lista(&tam, aliens);

    /* Move todos os aliens na direcao atual e detecta se bateram em alguma borda lateral */
    inicializa_atual_inicio(aliens);
    for (i = 0; i < tam; i++)
    {
        move_item_atual(aliens, STAY, *dir, &bordax, &borday);
        incrementa_atual(aliens);
    }

    /* Se bateu em alguma borda lateral, muda de direcao e move todos os aliens pra baixo */
    if (bordax)
    {
        (*dir) *= -1;
        inicializa_atual_inicio(aliens);
        for (i = 0; i < tam; i++)
        {
            move_item_atual(aliens, DOWN, STAY, &bordax, &borday);
            incrementa_atual(aliens);
        }
    }
    return bordax;
}

int checa_posicao_aliens(t_lista *aliens, t_lista *barreiras, t_lista *jogador)
{

    int i, j;
    int qnt_aliens, qnt_barreiras;
    t_sprite alien, barreira, desenho_jogador;

    tamanho_lista(&qnt_aliens, aliens);
    tamanho_lista(&qnt_barreiras, barreiras);

    inicializa_atual_inicio(jogador);
    consulta_item_atual(&desenho_jogador, jogador);

    inicializa_atual_inicio(aliens);

    for (i = 0; i < qnt_aliens; i++)
    {
        consulta_item_atual(&alien, aliens);
        inicializa_atual_inicio(barreiras);

        for (j = 0; j < qnt_barreiras; j++)
        {
            consulta_item_atual(&barreira, barreiras);

            /* Confere se os aliens bateram nas barreiras, se sim, remove as barreiras */
            if (detecta_colisao_completa(barreira, alien))
                remove_item_atual(barreiras);
            else
                incrementa_atual(barreiras);
        }

        /* Checa se o alien encostou no jogador ou no fim da tela */
        if (detecta_colisao_completa(alien , desenho_jogador) || ((alien.y + alien.lin - 1) >= LINHAS - 1))
            return 0;
        incrementa_atual(aliens);
    }

    return 1;
}

/*&&&&&&&&&&&&&&&&&& PROJETEIS &&&&&&&&&&&&&&&&&&*/

void atirar(t_lista *tiros, t_lista *jogador, int maxtiros)
{
    int qntd_tiros;
    t_sprite tiro, desenho_jogador;

    tamanho_lista(&qntd_tiros, tiros);
    inicializa_atual_inicio(jogador);
    consulta_item_atual(&desenho_jogador, jogador);

    if (qntd_tiros < maxtiros)
    {
        inicializa_desenho(&tiro, desenho_jogador.y,desenho_jogador.x + (desenho_jogador.col / 2), 1,1, TIRO1,  TIRO2, TIRO3, TIRO4, TIRO4);
        insere_fim_lista(tiro, tiros);
    }
}

void bombardear(t_lista *bombas, t_lista *aliens, int maxbombas)
{
    int i;
    int qnt_bombas, qnt_aliens, alien_atirador;
    t_sprite alien, bomba;

    tamanho_lista(&qnt_aliens, aliens);
    tamanho_lista(&qnt_bombas, bombas);

    /* Escolhe um alien aleatorio na lista para atirar a bomba */
    if ((qnt_bombas < maxbombas) && (qnt_aliens > 0))
    {
        alien_atirador = rand() % qnt_aliens;
        inicializa_atual_inicio(aliens);
        for (i = 0; i < alien_atirador; i++)
            incrementa_atual(aliens);

        consulta_item_atual(&alien, aliens);

        /* Cria e Insere a bomba na lista */
        inicializa_desenho(&bomba, alien.y + alien.lin, alien.x + alien.col/2, 1,1, BOMBA1,  BOMBA2, BOMBA3, BOMBA4, BOMBA5);
        insere_fim_lista(bomba, bombas);
    }
}

void move_projeteis(t_lista *projeteis, int dir)
{
    int i, tam;
    int bordax = 0, borday = 0;
    t_sprite projetil;

    tamanho_lista(&tam, projeteis);
    inicializa_atual_inicio(projeteis);
    for (i = 0; i < tam; i++)
    {
        borday = 0;
        move_item_atual(projeteis, dir, STAY, &bordax, &borday);
        consulta_item_atual(&projetil, projeteis);

        /* caso o projetil saia da tela, remove ele da lista */
        if (((dir == UP) && (projetil.y < 1)) || ((dir == DOWN) && (projetil.y >= LINHAS - 1)))
            remove_item_atual(projeteis);
        else
            incrementa_atual(projeteis);
    }
}

int detecta_projetil(t_lista *lista_a, t_lista *lista_b, int *score, int pontos)
{
    int i, j;
    int acertou = 0, contador = 0, tam_a, tam_b;
    t_sprite desenho_a, desenho_b;

    tamanho_lista(&tam_a, lista_a); /* Obtem o tamanho das listas */
    tamanho_lista(&tam_b, lista_b);

    inicializa_atual_inicio(lista_a);

    for (i = 0; i < tam_a; i++)
    {
        consulta_item_atual(&desenho_a, lista_a);
        inicializa_atual_inicio(lista_b);

        for (j = 0; j < tam_b; j++)
        {
            acertou = 0;
            consulta_item_atual(&desenho_b, lista_b);

            /* Verifica todas as coordenadas para detectar a colisao entre todos os elementos das duas listas */
            if ((estado_atual(lista_b) == VIVO) && (estado_atual(lista_a) == VIVO)){
                /* Sabe que são duas estruturas 1x1, o que evita as outras comparações, senão faz a checagem completa */
                if (((pontos == PONTUACAOBOMBA) && detecta_colisao_simples(desenho_a, desenho_b)) || (detecta_colisao_completa(desenho_a, desenho_b))){                    
                    acertou = 1;
                    remove_item_atual(lista_a);
                    muda_estado_atual(lista_b, MORTO);
                    muda_versao_atual(lista_b, ESTADOMORTO);
                    *score += pontos;
                    break;
                }
            }
            incrementa_atual(lista_b);
        }

        if (acertou)
            contador += 1;
        else
            incrementa_atual(lista_a);
    }
    return contador;
}

/*&&&&&&&&&&&&&&&&&& BARREIRA &&&&&&&&&&&&&&&&&&*/

void inicializa_barreiras(t_lista *barreiras)
{
    int i, j, k, l, peca_aleatoria;
    t_sprite peca;

    srand(time(NULL));

    for (i = 16; i < 100; i += 21)
    {
        for (j = 0; j < LINHASBARREIRA; j++)
        {
            for (k = 0; k < COLUNASBARREIRA; k++)
            {
                peca.lin = 1;
                peca.col = 1;
                peca.estado = VIVO;
                peca.versao = 0;
                peca.x = i + k;
                peca.y = 31 + j;
                for (l = 0; l < 4; l++)
                {
                    peca_aleatoria = rand() % 100;
                    if (peca_aleatoria < 50)
                        peca.corpo[l][0][0] = BARREIRA1;
                    else
                        peca.corpo[l][0][0] = BARREIRA2;
                }
                peca.corpo[4][0][0] = BARREIRA3;

                insere_fim_lista(peca, barreiras);
            }
        }
    }
}

/*&&&&&&&&&&&&&&&&&& NAVE MÃE &&&&&&&&&&&&&&&&&&*/

void inicializa_navemae(t_lista *navemae)
{
    t_sprite navemae_sprite;

    inicializa_desenho(&navemae_sprite, 1, 1, LINMAE, COLMAE, NAVEMAE1, NAVEMAE2, NAVEMAE3, NAVEMAE4, EXPLOSAONAVEMAE);
    insere_fim_lista(navemae_sprite, navemae);
}

/*&&&&&&&&&&&&&&&&&&          &&&&&&&&&&&&&&&&&&*/
