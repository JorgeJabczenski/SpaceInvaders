#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

void desenha_layout();

void imprime_tela_inicio();                                                                                                                                                                     

void imprime_tela_final(int score, int aliens_mortos, int bombas_destruidas, int rodada);
