#include "lib_graficos.h"

void imprime_tela_final(int score, int aliens_mortos, int bombas_destruidas, int rodada){

    int key;
    nodelay(stdscr, FALSE);


    attron(COLOR_PAIR(1));
    clear();
    mvprintw(0,15," ____                            __               _____                                                               ");
    mvprintw(1,15,"/\\  _`\\   __                    /\\ \\             /\\___ \\                                                        ");
    mvprintw(2,15,"\\ \\ \\L\\_\\/\\_\\    ___ ___        \\_\\ \\     __     \\/__/\\ \\    ___      __     ___                         ");
    mvprintw(3,15," \\ \\  _\\/\\/\\ \\ /' __` __`\\      /'_` \\  /'__`\\      _\\ \\ \\  / __`\\  /'_ `\\  / __`\\                     ");
    mvprintw(4,15,"  \\ \\ \\/  \\ \\ \\/\\ \\/\\ \\/\\ \\    /\\ \\L\\ \\/\\  __/     /\\ \\_\\ \\/\\ \\L\\ \\/\\ \\L\\ \\/\\ \\L\\ \\  ");
    mvprintw(5,15,"   \\ \\_\\   \\ \\_\\ \\_\\ \\_\\ \\_\\   \\ \\___,_\\ \\____\\    \\ \\____/\\ \\____/\\ \\____ \\ \\____/          ");
    mvprintw(6,15,"    \\/_/    \\/_/\\/_/\\/_/\\/_/    \\/__,_ /\\/____/     \\/___/  \\/___/  \\/___L\\ \\/___/                        ");
    mvprintw(7,15,"                                                                      /\\____/                                        ");
    mvprintw(8,15,"                                                                      \\_/__/                                         ");



    mvprintw(15, 52, "Level Alcançado: %d", rodada+1);
    mvprintw(17, 55, "Pontuação: %d", score);
    mvprintw(19, 54, "Aliens Mortos: %d", aliens_mortos);
    mvprintw(21, 52, "Bombas Destruidas: %d", bombas_destruidas);
    mvprintw(30, 52, "Aperte q para sair");
    refresh();

    key = getch();
    while (key != 'q')
        key = getch();

}

void imprime_tela_inicio(){

    int key;

    attron(COLOR_PAIR(3));

    clear();
    mvprintw(0,1,"                            _            _          _                   _              _                                                  ");
    mvprintw(1,1,"                           / /\\         /\\ \\       / /\\                /\\ \\           /\\ \\                                        ");
    mvprintw(2,1,"                          / /  \\       /  \\ \\     / /  \\              /  \\ \\         /  \\ \\                                       ");                                         
    mvprintw(3,1,"                         / / /\\ \\__   / /\\ \\ \\   / / /\\ \\            / /\\ \\ \\       / /\\ \\ \\                                 ");                                           
    mvprintw(4,1,"                        / / /\\ \\___\\ / / /\\ \\_\\ / / /\\ \\ \\          / / /\\ \\ \\     / / /\\ \\_\\                              ");                                          
    mvprintw(5,1,"                        \\ \\ \\ \\/___// / /_/ / // / /  \\ \\ \\        / / /  \\ \\_\\   / /_/_ \\/_/                                  ");                                   
    mvprintw(6,1,"                         \\ \\ \\     / / /__\\/ // / /___/ /\\ \\      / / /    \\/_/  / /____/\\                                        ");                             
    mvprintw(7,1,"                     _    \\ \\ \\   / / /_____// / /_____/ /\\ \\    / / /          / /\\____\\/                                         ");                         
    mvprintw(8,1,"                    /_/\\__/ / /  / / /      / /_________/\\ \\ \\  / / /________  / / /______                                            ");                   
    mvprintw(9,1,"                    \\ \\/___/ /  / / /      / / /_       __\\ \\_\\/ / /_________\\/ / /_______\\                                        ");                   
    mvprintw(10,1,"                     \\_____\\/   \\/_/       \\_\\___\\     /____/_/\\/____________/\\/__________/                                      ");                  
    mvprintw(11,1,"                                                                                                                                         ");       
    mvprintw(12,1,"          _          _           _          _       _                _            _            _          _                              ");    
    mvprintw(13,1,"         /\\ \\       /\\ \\     _  /\\ \\    _ / /\\     / /\\             /\\ \\         /\\ \\         /\\ \\       / /\\             ");
    mvprintw(14,1,"         \\ \\ \\     /  \\ \\   /\\_\\\\ \\ \\  /_/ / /    / /  \\           /  \\ \\____   /  \\ \\       /  \\ \\     / /  \\         ");
    mvprintw(15,1,"         /\\ \\_\\   / /\\ \\ \\_/ / / \\ \\ \\ \\___\\/    / / /\\ \\         / /\\ \\_____\\ / /\\ \\ \\     / /\\ \\ \\   / / /\\ \\__");
    mvprintw(16,1,"        / /\\/_/  / / /\\ \\___/ /  / / /  \\ \\ \\   / / /\\ \\ \\       / / /\\/___  // / /\\ \\_\\   / / /\\ \\_\\ / / /\\ \\___\\    ");
    mvprintw(17,1,"       / / /    / / /  \\/____/   \\ \\ \\   \\_\\ \\ / / /  \\ \\ \\     / / /   / / // /_/_ \\/_/  / / /_/ / / \\ \\ \\ \\/___/        ");
    mvprintw(18,1,"      / / /    / / /    / / /     \\ \\ \\  / / // / /___/ /\\ \\   / / /   / / // /____/\\    / / /__\\/ /   \\ \\ \\                   ");
    mvprintw(19,1,"     / / /    / / /    / / /       \\ \\ \\/ / // / /_____/ /\\ \\ / / /   / / // /\\____\\/   / / /_____/_    \\ \\ \\                  ");
    mvprintw(20,1," ___/ / /__  / / /    / / /         \\ \\ \\/ // /_________/\\ \\ \\\\ \\ \\__/ / // / /______  / / /\\ \\ \\ /_/\\__/ / /               ");
    mvprintw(21,1,"/\\__\\/_/___\\/ / /    / / /           \\ \\  // / /_       __\\ \\_\\\\ \\___\\/ // / /_______\\/ / /  \\ \\ \\\\ \\/___/ /            "); 
    mvprintw(22,1,"\\/_________/\\/_/     \\/_/             \\_\\/ \\_\\___\\     /____/_/ \\/_____/ \\/__________/\\/_/    \\_\\/ \\_____\\/               ");

    
    attron(COLOR_PAIR(7));
    mvprintw(30,40,"Jogo criado por Jorge L. V. Jabczenski");
    mvprintw(35,45,"Aperte 'a' para iniciar o jogo");
    refresh();

    nodelay(stdscr, FALSE);
    key = getch();
    while(key != 'a')
        key = getch();
    nodelay(stdscr, TRUE);
    clear();                                                                                                                                                                                                             
}

void desenha_layout(){
        
        /* Divisão */
        move(0,0)   ; addch(ACS_ULCORNER);
        move(0,1)   ; hline(ACS_HLINE, 99);
        move(0,101) ; hline(ACS_HLINE,18);
        move(0,100) ; addch(ACS_TTEE);
        move(0,119) ; addch(ACS_URCORNER);
        move(1,0)   ; vline(ACS_VLINE, 36);
        move(1, 100); vline(ACS_VLINE, 36);
        move(1,119) ; vline(ACS_VLINE,36);
        move(37,0)  ; addch(ACS_LLCORNER);
        move(37,1)  ; hline(ACS_HLINE, 99);
        move(37,100); addch(ACS_BTEE);
        move(37,101); hline(ACS_HLINE,18);
        move(37,119); addch(ACS_LRCORNER);

        /* Score */
        move(1,101) ; addch(ACS_ULCORNER);
        move(1,102) ; hline(ACS_HLINE, 16);
        move(1,118) ; addch(ACS_URCORNER);
        move(2,101) ; addch(ACS_VLINE);
        move(2,118) ; addch(ACS_VLINE);
        move(3,101) ; addch(ACS_LLCORNER);
        move(3,102) ; hline(ACS_HLINE, 16);
        move(3,118) ; addch(ACS_LRCORNER);
}