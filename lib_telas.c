#include "lib_telas.h"


void desenha_layout()
{
    /* Divisão */
    move(0, 0);    addch(ACS_ULCORNER);
    move(0, 1);    hline(ACS_HLINE, 99);
    move(0, 101);  hline(ACS_HLINE, 18);
    move(0, 100);  addch(ACS_TTEE);
    move(0, 119);  addch(ACS_URCORNER);
    move(1, 0);    vline(ACS_VLINE, 36);
    move(1, 100);  vline(ACS_VLINE, 36);
    move(1, 119);  vline(ACS_VLINE, 36);
    move(37, 0);   addch(ACS_LLCORNER);
    move(37, 1);   hline(ACS_HLINE, 99);
    move(37, 100); addch(ACS_BTEE);
    move(37, 101); hline(ACS_HLINE, 18);
    move(37, 119); addch(ACS_LRCORNER);

    /* Score */
    move(1, 101);  addch(ACS_ULCORNER);
    move(1, 102);  hline(ACS_HLINE, 16);
    move(1, 118);  addch(ACS_URCORNER);
    move(2, 101);  addch(ACS_VLINE);
    move(2, 118);  addch(ACS_VLINE);
    move(3, 101);  addch(ACS_LLCORNER);
    move(3, 102);  hline(ACS_HLINE, 16);
    move(3, 118);  addch(ACS_LRCORNER);
}

void imprime_tela_inicio()
{
    int key;

    attron(COLOR_PAIR(3));

    clear();
    mvprintw(0, 1, "                            _            _          _                   _              _                                                  ");
    mvprintw(1, 1, "                           / /\\         /\\ \\       / /\\                /\\ \\           /\\ \\                                        ");
    mvprintw(2, 1, "                          / /  \\       /  \\ \\     / /  \\              /  \\ \\         /  \\ \\                                       ");
    mvprintw(3, 1, "                         / / /\\ \\__   / /\\ \\ \\   / / /\\ \\            / /\\ \\ \\       / /\\ \\ \\                                 ");
    mvprintw(4, 1, "                        / / /\\ \\___\\ / / /\\ \\_\\ / / /\\ \\ \\          / / /\\ \\ \\     / / /\\ \\_\\                              ");
    mvprintw(5, 1, "                        \\ \\ \\ \\/___// / /_/ / // / /  \\ \\ \\        / / /  \\ \\_\\   / /_/_ \\/_/                                  ");
    mvprintw(6, 1, "                         \\ \\ \\     / / /__\\/ // / /___/ /\\ \\      / / /    \\/_/  / /____/\\                                        ");
    mvprintw(7, 1, "                     _    \\ \\ \\   / / /_____// / /_____/ /\\ \\    / / /          / /\\____\\/                                         ");
    mvprintw(8, 1, "                    /_/\\__/ / /  / / /      / /_________/\\ \\ \\  / / /________  / / /______                                            ");
    mvprintw(9, 1, "                    \\ \\/___/ /  / / /      / / /_       __\\ \\_\\/ / /_________\\/ / /_______\\                                        ");
    mvprintw(10, 1, "                     \\_____\\/   \\/_/       \\_\\___\\     /____/_/\\/____________/\\/__________/                                      ");
    mvprintw(11, 1, "                                                                                                                                         ");
    mvprintw(12, 1, "          _          _           _          _       _                _            _            _          _                              ");
    mvprintw(13, 1, "         /\\ \\       /\\ \\     _  /\\ \\    _ / /\\     / /\\             /\\ \\         /\\ \\         /\\ \\       / /\\             ");
    mvprintw(14, 1, "         \\ \\ \\     /  \\ \\   /\\_\\\\ \\ \\  /_/ / /    / /  \\           /  \\ \\____   /  \\ \\       /  \\ \\     / /  \\         ");
    mvprintw(15, 1, "         /\\ \\_\\   / /\\ \\ \\_/ / / \\ \\ \\ \\___\\/    / / /\\ \\         / /\\ \\_____\\ / /\\ \\ \\     / /\\ \\ \\   / / /\\ \\__");
    mvprintw(16, 1, "        / /\\/_/  / / /\\ \\___/ /  / / /  \\ \\ \\   / / /\\ \\ \\       / / /\\/___  // / /\\ \\_\\   / / /\\ \\_\\ / / /\\ \\___\\    ");
    mvprintw(17, 1, "       / / /    / / /  \\/____/   \\ \\ \\   \\_\\ \\ / / /  \\ \\ \\     / / /   / / // /_/_ \\/_/  / / /_/ / / \\ \\ \\ \\/___/        ");
    mvprintw(18, 1, "      / / /    / / /    / / /     \\ \\ \\  / / // / /___/ /\\ \\   / / /   / / // /____/\\    / / /__\\/ /   \\ \\ \\                   ");
    mvprintw(19, 1, "     / / /    / / /    / / /       \\ \\ \\/ / // / /_____/ /\\ \\ / / /   / / // /\\____\\/   / / /_____/_    \\ \\ \\                  ");
    mvprintw(20, 1, " ___/ / /__  / / /    / / /         \\ \\ \\/ // /_________/\\ \\ \\\\ \\ \\__/ / // / /______  / / /\\ \\ \\ /_/\\__/ / /               ");
    mvprintw(21, 1, "/\\__\\/_/___\\/ / /    / / /           \\ \\  // / /_       __\\ \\_\\\\ \\___\\/ // / /_______\\/ / /  \\ \\ \\\\ \\/___/ /            ");
    mvprintw(22, 1, "\\/_________/\\/_/     \\/_/             \\_\\/ \\_\\___\\     /____/_/ \\/_____/ \\/__________/\\/_/    \\_\\/ \\_____\\/               ");

    attron(COLOR_PAIR(7));
    mvprintw(30, 40, "Jogo criado por Jorge L. V. Jabczenski");
    mvprintw(35, 45, "Aperte 'a' para iniciar o jogo");
    refresh();

    nodelay(stdscr, FALSE);
    key = getch();
    while (key != 'a')
        key = getch();
    nodelay(stdscr, TRUE);
    clear();
}

/* Retorna 1 para reiniciar o jogo e 0 para finaliza-lo */
int imprime_tela_final(int score, int aliens_mortos, int bombas_destruidas, int level)
{
    int key;

    attron(COLOR_PAIR(1));
    clear();
    mvprintw(0, 15, " ____                            __               _____                                                               ");
    mvprintw(1, 15, "/\\  _`\\   __                    /\\ \\             /\\___ \\                                                        ");
    mvprintw(2, 15, "\\ \\ \\L\\_\\/\\_\\    ___ ___        \\_\\ \\     __     \\/__/\\ \\    ___      __     ___                         ");
    mvprintw(3, 15, " \\ \\  _\\/\\/\\ \\ /' __` __`\\      /'_` \\  /'__`\\      _\\ \\ \\  / __`\\  /'_ `\\  / __`\\                     ");
    mvprintw(4, 15, "  \\ \\ \\/  \\ \\ \\/\\ \\/\\ \\/\\ \\    /\\ \\L\\ \\/\\  __/     /\\ \\_\\ \\/\\ \\L\\ \\/\\ \\L\\ \\/\\ \\L\\ \\  ");
    mvprintw(5, 15, "   \\ \\_\\   \\ \\_\\ \\_\\ \\_\\ \\_\\   \\ \\___,_\\ \\____\\    \\ \\____/\\ \\____/\\ \\____ \\ \\____/          ");
    mvprintw(6, 15, "    \\/_/    \\/_/\\/_/\\/_/\\/_/    \\/__,_ /\\/____/     \\/___/  \\/___/  \\/___L\\ \\/___/                        ");
    mvprintw(7, 15, "                                                                      /\\____/                                        ");
    mvprintw(8, 15, "                                                                      \\_/__/                                         ");

    mvprintw(15, 53, "Level Alcançado: %d", level);
    mvprintw(17, 56, "Pontuação: %d", score);
    mvprintw(19, 54, "Aliens Mortos: %d", aliens_mortos);
    mvprintw(21, 52, "Bombas Destruidas: %d", bombas_destruidas);
    mvprintw(28, 52, "Aperte r para recomeçar");
    mvprintw(30, 54, "Aperte q para sair");
    refresh();

    nodelay(stdscr, FALSE);
    key = getch();
    while (key != 'q' && key != 'r')
        key = getch();

    clear();
    nodelay(stdscr, TRUE);

    if (key == 'q')
        return 0; /* Se for 'q', sai do jogo     */ 
    return 1;     /* Se for 'r', reinicia o jogo */
}

void imprimir_score(int score, int aliens_mortos, int bombas_destruidas, int level)
{
    mvprintw(2, 104, "Score : %d", score);      /* Pontuação         */
    mvprintw(5, 104, "Aliens Mortos");          /* Alies Mortos      */
    mvprintw(6, 109, "%d", aliens_mortos);      /* Alies Mortos      */
    mvprintw(8, 107, "Bombas");                 /* Bombas Destruidas */
    mvprintw(9, 105, "Destruidas");             /* Bombas Destruidas */
    mvprintw(10, 109, "%d", bombas_destruidas); /* Bombas Destruidas */
    mvprintw(20, 107, "LEVEL %d", level);       /* Level             */
    mvprintw(34, 104, "p para pausar");         /* Instrucoes        */
    mvprintw(36, 105, "q para sair");           /* Instrucoes        */
}

void imprimir_fim_de_ciclo(t_lista *tiros, t_lista *navemae,t_lista *barreiras,t_lista *bombas,t_lista *aliens,t_lista *jogador,int score, int aliens_mortos, int bombas_destruidas, int level)
{
    erase();
    desenha_layout();
    imprime_lista(tiros);
    attron(COLOR_PAIR(6)); imprime_lista(bombas);
    attron(COLOR_PAIR(2)); imprime_lista(aliens);
    attron(COLOR_PAIR(5)); imprime_lista(navemae);
    attron(COLOR_PAIR(1)); imprime_lista(barreiras);
    attron(COLOR_PAIR(7)); imprime_lista(jogador);
    imprimir_score(score, aliens_mortos, bombas_destruidas, level);
}

void imprimir_tela_proximo_level(int score, int aliens_mortos, int bombas_destruidas){

    int key = 0;

    clear();
    attron(COLOR_PAIR(5));
    mvprintw(2,36,"|  \\                                   |  \\                       ");
    mvprintw(3,36,"| $$       ______  __     __   ______  | $$                       ");
    mvprintw(4,36,"| $$      /      \\|  \\   /  \\ /      \\ | $$                       ");
    mvprintw(5,36,"| $$     |  $$$$$$\\\\$$\\ /  $$|  $$$$$$\\| $$                       ");
    mvprintw(6,36,"| $$     | $$    $$ \\$$\\  $$ | $$    $$| $$                       ");
    mvprintw(7,36,"| $$_____| $$$$$$$$  \\$$ $$  | $$$$$$$$| $$                       ");
    mvprintw(8,36,"| $$     \\\\$$     \\   \\$$$   \\$$      \\| $$                       ");
    mvprintw(9,36,"\\$$$$$$$$  \\$$$$$$$    \\$      \\$$$$$$$ \\$$                       ");
    mvprintw(10,36,"                                                                              ");
    mvprintw(11,0,"                                                                              ");
    mvprintw(12,0,"                                                                              ");
    mvprintw(13,20,"  ______                                 __            __        __           ");
    mvprintw(14,20," /      \\                               |  \\          |  \\      |  \\          ");
    mvprintw(15,20,"|  $$$$$$\\  ______   _______    _______ | $$ __    __  \\$$  ____| $$  ______  ");
    mvprintw(16,20,"| $$   \\$$ /      \\ |       \\  /       \\| $$|  \\  |  \\|  \\ /      $$ /      \\ ");
    mvprintw(17,20,"| $$      |  $$$$$$\\| $$$$$$$\\|  $$$$$$$| $$| $$  | $$| $$|  $$$$$$$|  $$$$$$\\");
    mvprintw(18,20,"| $$   __ | $$  | $$| $$  | $$| $$      | $$| $$  | $$| $$| $$  | $$| $$  | $$");
    mvprintw(19,20,"| $$__/  \\| $$__/ $$| $$  | $$| $$_____ | $$| $$__/ $$| $$| $$__| $$| $$__/ $$");
    mvprintw(20,20," \\$$    $$ \\$$    $$| $$  | $$ \\$$     \\| $$ \\$$    $$| $$ \\$$    $$ \\$$    $$    ");
    mvprintw(21,20,"  \\$$$$$$   \\$$$$$$  \\$$   \\$$  \\$$$$$$$ \\$$  \\$$$$$$  \\$$  \\$$$$$$$  \\$$$$$$ ");
    
    attron(COLOR_PAIR(2));
    mvprintw(25, (COLUNAS + 20) / 2 - 8, "Pontucao Atual %d", score);
    mvprintw(27, (COLUNAS + 20) / 2 - 8, "Aliens Mortos: %d", aliens_mortos);
    mvprintw(29, (COLUNAS + 20) / 2 - 10, "Bombas Destruidas: %d", bombas_destruidas);
    attron(COLOR_PAIR(7));
    mvprintw(35, (COLUNAS + 20) / 2 - 12, "Aperte 'a' para continuar");
    refresh();

    nodelay(stdscr, FALSE);
    while (key != 'a')
        key = getch();
    nodelay(stdscr, TRUE);
    clear();
}
