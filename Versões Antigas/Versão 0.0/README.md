# space-invaders
Jogo Space Invaders programado em C usando Ncurses para a matéria de Prog 1

Enunciado: 

Implementar uma versão texto do jogo Space Invaders na linguagem C,
usando o padrão ANSI. (https://pt.wikipedia.org/wiki/Space_Invaders)


O objetivo do jogo é usar um canhão para destruir os alienígenas antes
que eles cheguem ao chão.


O canhão está localizado na parte inferior da tela. Ele é controlado
pelo jogador que pode atirar ou movê-lo lateralmente.


O alienígenas são de 3 tipos diferentes e estão organizados
organizados em 5 linhas e 11 colunas. Eles se movem em bloco de um
lado a outro da tela. Quando o bloco chega ao limite da tela, ele
desce uma linha e segue na direção contrária até a outra borda da
tela. A cada linha que o bloco desce a velocidade de seu movimento
lateral aumenta. Caso algum alienígena atinja o chão ou o canhão o
jogo termina.


Os alienígenas lançam aleatoriamente bombas, que caem em linha
reta. Caso o canhão seja atingido por uma bomba o jogo termina.


Entre os alienígenas e o canhão existem 4 barreiras que protegem o
canhão das bombas que caem. Caso uma bomba ou um tiro atinja uma
barreira, parte dela é destruída. Caso um alienígena colida com uma
barreira, parte da barreira é distruída e o alienígena segue com seu
movimento.


De tempos em tempos uma nave mãe atravessa a parte superior da tela.


Na parte superior da tela um placar indica a pontuação corrente do
jogador, que é dada pela soma dos pontos obtidos com cada alienígena e
cada nave mãe destruida.


A cada vez que todos os alienígenas são eliminados, o jogo reinicia
com uma velocidade mais rápida.


A figura abaixo é um exemplo do jogo em execução:

----------------------------------------------------------------------------------------------------
|                                            0000001                                               |
|                                                                                                  |
| /MMMMM\                                                                                          |
|AMoMoMoMA                                                                                         |
| \/'-'\/                                                                                          |
|                                                                                                  |
|     A      A      A      A      A      A      A      A      A      A      A                      |
|    AMA    AMA    AMA    AMA    AMA    AMA    AMA    AMA    AMA    AMA    AMA                     |
|    /X\    /X\    /X\    /X\    /X\    /X\    /X\    /X\    /X\    /X\    /X\                     |
|                                                                                                  |
|   .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.                    |
|   }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{                    |
|    / \    / \    / \    / \    / \    / \    / \    / \    / \    / \    / \                     |
|                                                                                                  |
|   .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.  .v_v.                    |
|   }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{  }WMW{                    |
|    / \    / \    / \    / \    / \    / \    / \    / \    / \    / \    / \                     |
|                                                                                                  |
|    nmn    nmn    nmn    nmn    nmn    nmn    nmn    nmn    nmn    nmn    nmn                     |
|   dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb                    |
|   _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_                    |
|                                                                                                  |
|    nmn    nmn    nmn    nmn    nmn    nmn    \'/           nmn    nmn    nmn                     |
|   dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  dbMdb  -   -         dbMdb  dbMdb  dbMdb                    |
|   _/-\_  _/-\_  _/-\_  _/-\_  _/-\_  _/-\_   /,\          _/-\_  _/-\_  _/-\_                    |
|                                                                                                  |
|                                        $                                                         |
|                                             |                                                    |
|                    $                                                                             |
|                                                                                                  |
|               AMM                  AMMMA                AMMMA                AMMMA               |
|              AMMMMMA              AMMMMMA      |       AMMMMMA              AMMMMMA              |
|              MM   MM              MM   MM              MM   MM              MM   MM              |
|                       $                                                                          |
|                                               /^\                                                |
|                                              MMMMM                                               |
----------------------------------------------------------------------------------------------------


A tela do jogo é um terminal texto com pelo menos 38 linhas e 100
colunas.


Abaixo segue uma descrição rápida de algumas funções da biblioteca
ncurses que são úteis para desenhar a tela e controlar o teclado.


Para utilizar a biblioteca ncurses o program deve incluir:

  #include <ncurses.h>


Para compilar o program incluir a biblioteca ao final da na linha de
comando do compilador:

  $ gcc ... -lncurses


Ao início da execução o programa deve configurar alguns os recursos da
biblioteca:

  int main() {
    ...
  
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */
  
    ...
  }


O tamanho do terminal pode ser obtido pela macro:

  getmaxyx(stdscr, nlin, ncol);

após a execução desta macro as variávei nlin e ncol conterão o número
de linhas e colunas do terminal respectivamente.


A biblioteca ncurses usa uma tela escondida onde os caracteres são
escritos na posição corrente do cursor. Esta tela só é mostrada no
terminal com a chamada da função refresh().


A função clear() limpa a tela escondida.


A função move(lin, col) move o cursor para a posição (lin, col), sendo
a posição (0,0) o canto superior esquerdo da tela.


A função addch(c) escreve o caracter c na posição corrente do cursor.


A função getch() retorna a tecla digitada no teclado. Caso nenhuma
tecla tenha sido aceionada a função retorna a constante ERR. Exemplo:

  key = getch();
  
  if(key == ' ') {
    /* atira */
  }
  else
  if(key == KEY_LEFT) {
    /* move para a esquerda */
  }
  else if (key == KEY_RIGHT) {
    /* move para a esquerda */
  }
  else if (key == 'q') {
    endwin();
    exit(0);
  }


A função endwin() desativa a tela da ncurses e volta o terminal ao seu
estado normal.


Para usar cores na tela, é preciso iniciar o modo colorido e criar
pares de cores de frente e fundo. Por exemplo:

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);

isso cria três pares de cores, 1, 2 e 3. Para utilizar o par 1 basta
chamar a função:

  wattron(stdscr, COLOR_PAIR(1));

após esta chamada todos os caracteres escritos na tela usarão este par
de cores como cor de frente e fundo.


A parte mais complicada do trabalho é o controle do tempo. O único
recurso disponível para construirmos este controle é interromper a
execução do programa por um determinado tempo. A função:

  usleep(u);

interrompe a execução do programa por u microsegundos. Para utilizá-la
é necessário incluir:

  #include <unistd.h>

