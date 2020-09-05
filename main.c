#include "lib_telas.h"

/*      Autor       : Jorge Lucas Vicilli Jabczenski                        */
/*   Last update    : 22/11/2019                                            */
/*     GitHub       : https://github.com/JorgeJabczenski/                   */
/*     GitLab       : https://gitlab.com/jorgejabczenski/                   */
/*  Game Repository : https://gitlab.com/jorgejabczenski/space-invaders-v2  */


int main()
{
    int jogo = 1; /* Variável principal do jogo */
    int delay_aliens, delay_bombas, maxtiros, maxbombas, dir_aliens;
    int score, aliens_mortos, bombas_destruidas, ciclos, level;
    int nlin, ncol;
    t_lista aliens, tiros, bombas, barreiras, navemae, jogador;

    inicializa_lista    (&aliens); /*  Inicializa o TAD Lista  */
    inicializa_lista     (&tiros);
    inicializa_lista    (&bombas);
    inicializa_lista (&barreiras);
    inicializa_lista   (&navemae);
    inicializa_lista   (&jogador);

    /* Configurações do Ncurses */
    configuracoes_iniciais();

    /* Confere o tamanho da tela , ela deve ter no mínimo 38 linhas e 120 colunas */
    getmaxyx(stdscr, nlin, ncol);
    if ((nlin < LINHAS) || (ncol < COLUNAS + COLMENU)) /* Adiciona 20 colunas por conta do menu */
    {
        endwin();
        printf("O terminal deve possuir 38 linhas e 120 colunas\n");
        return 1;
    }

    /* Imprime a tela inicial do jogo */
    imprime_tela_inicio();

    /* Roda o jogo inteiro, feito para poder resetar o jogo sem executa-lo novamente */
    while (jogo)
    {
        delay_aliens = DELAYALIENS; /* Velocidade de movimento dos aliens */
        delay_bombas = DELAYBOMBAS; /* Velocidade de movimento das bombas */
        maxtiros     = MAXTIROS;    /* Maximo de tiros na tela */
        maxbombas    = MAXBOMBAS;   /* Maximo de bombas na tela */
        dir_aliens   = RIGHT;       /* Direcao de movimento dos aliens */
        score             = 0;      /* Conta a pontuação total */
        aliens_mortos     = 0;      /* Conta o total de aliens mortos */
        bombas_destruidas = 0;      /* Conta o total de bombas destruidas */
        ciclos            = 0;      /* Variável de ciclos de jogo, utilizada para as contas de movimentação */
        level             = 1;      /* Level do jogo */

        inicializa_aliens(&aliens);         /* Inicializa as listas de jogo com os valores adequados */
        inicializa_barreiras(&barreiras);
        inicializa_jogador(&jogador);
        inicializa_atual_inicio(&jogador);

        /* Loop Principal do Jogo, roda enquanto o jogador estiver vivo */
        while (estado_atual(&jogador) == VIVO)
        {

            /* Le os comandos possíveis (movimentação, atirar, pausar, sair)*/
            le_teclado(&jogador, &tiros, maxtiros);

            /* Controla a movimentação e detecção dos tiros */
            if (!(ciclos % DELAYTIROS))
            {
                move_projeteis(&tiros, UP);
                atualiza_versao(&tiros);    /* Atualiza o sprite os tiros */

                /* Detecta e conta quantos aliens e bombas foram mortas/destruidas */
                aliens_mortos     += detecta_projetil(&tiros, &aliens, &score, PONTUACAOALIEN*level);
                bombas_destruidas += detecta_projetil(&tiros, &bombas, &score, PONTUACAOBOMBA*level);
                detecta_projetil(&tiros, &navemae, &score, PONTUACAONAVEMAE*level);
                detecta_projetil(&tiros, &barreiras, &score, PONTUACAOBARREIRA*level);
            }
            
            /* Cuida da movimentação dos aliens */
            if (!(ciclos % delay_aliens))
            {
                int acelerador, vivo;

                atualiza_versao(&aliens); /* Atualiza o sprite dos aliens */
                acelerador = move_aliens(&aliens, &dir_aliens);   /* Se bateu em uma parede, a funçao move aliens retorna 1 */
                if (acelerador && delay_aliens > LIMITEALIENS)   /* Caso ainda seja possivel aumentar a velocidade/diminuir o delay dos aliens */     
                    delay_aliens -= 1; 
                
                /* A função checa_posicao_aliens retorna 0 caso os aliens enconstem no jogador ou no chão */
                vivo = checa_posicao_aliens(&aliens, &barreiras, &jogador);
                
                if (!vivo)                 /* Caso os aliens tenham enconstado no jogador ou no chão, matar o jogador */
                    mata_jogador(&jogador); 

                retira_mortos_lista(&aliens);
            }

            /* Chama a função para atirar mais bombas */
            if (!(ciclos % DELAYBOMBARDEAR))
            {
                bombardear(&bombas, &aliens, maxbombas);
            }

            /* Cuida da movimentação e detecção das bombas */
            if (!(ciclos % delay_bombas))
            {
                int acertou;

                atualiza_versao(&bombas);      /* Atualiza o sprite das bombas */
                move_projeteis(&bombas, DOWN); /* Move as bombas para baixo */
                detecta_projetil(&bombas, &barreiras, &score, PONTUACAOBARREIRA);
                acertou = detecta_projetil(&bombas, &jogador, &score, 0); /* detecta_projetil retorna um valor diferente de 0 caso houveram colisões */

                /* Houve detecção de tiro entre as duas listas, portanto o jogador foi atingido */
                if (acertou)
                    mata_jogador(&jogador);

                retira_mortos_lista(&bombas);
            }
   
            /* Controla o tempo de aparição da Nave Mae */
            if (!(ciclos % APARICAONAVEMAE))
            {
                inicializa_navemae(&navemae);
            }
        
            /* Controla a movimentação da nave mãe, se existir uma no momento */
            if (!(ciclos % DELAYNAVEMAE))
            {
                int bordax = 0, borday = 0;

                if (!(lista_vazia(&navemae))) /* Caso haja uma nave mãe, movimentar ela */
                {
                    inicializa_atual_inicio(&navemae);
                    move_item_atual(&navemae, STAY, RIGHT, &bordax, &borday);
                }
                if (bordax)  /* Caso a nave mae chegar na borda da tela, retirada da lista */
                    remove_item_atual(&navemae);

                atualiza_versao(&navemae); /* Atualiza o sprite da nave mae */
                retira_mortos_lista(&navemae);
            }

            /* Atualiza Sprite do Jogador */
            if (!(ciclos % DELAYJOGADOR))
            {
                atualiza_versao(&jogador); 
            }

            /* Atualiza Sprite das Barreias */
            if (!(ciclos % DELAYBARREIRA))
            {
                atualiza_versao(&barreiras); 
                retira_mortos_lista(&barreiras);
            }
            
            /* Imprime os elementos da tela */
            imprimir_fim_de_ciclo(&tiros, &navemae, &barreiras, &bombas, &aliens, &jogador, score, aliens_mortos, bombas_destruidas, level);

            /* Detecta se todos os aliens até aquele nivel já foram mortos para passar de nivel */
            if ((aliens_mortos > 0) && (!(aliens_mortos % (QNTDALIENS * level))))
            {
                proximo_level(&aliens, &tiros, &bombas, &navemae, &jogador, &barreiras, &level, &delay_aliens, &delay_bombas, &maxtiros, &dir_aliens, &maxbombas);
                imprimir_tela_proximo_level(score, aliens_mortos, bombas_destruidas);
            }
        
            usleep(DELAY);
            ciclos = (ciclos + 1) % 65000;
        }

        /* Confere se o jogo realmente acabou ou vai apenas recomeçar */
        jogo = imprime_tela_final(score, aliens_mortos, delay_bombas, level); /* Retorna 1 para recomeçar e 0 para encerrar */
        if (jogo){                     /* O jogo vai reiniciar */
            esvazia_lista(&aliens);     /* Esvazia as listas */
            esvazia_lista(&tiros);
            esvazia_lista(&barreiras);
            esvazia_lista(&bombas);
            esvazia_lista(&navemae);
            esvazia_lista(&jogador);
        } else {                       /* O jogo vai ser encerrado */
            destroi_lista(&aliens);       /* Destroi as listas */
            destroi_lista(&tiros);
            destroi_lista(&barreiras);
            destroi_lista(&bombas);
            destroi_lista(&navemae);
            destroi_lista(&jogador);
        }
    }
    endwin();
    return 0;
}
