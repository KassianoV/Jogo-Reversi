#include <stdio.h>

#include <stdlib.h>

// branca 1
// preta -1

void IniciaTabuleiro (int tab[8][8]) {
  tab[0][0]=0;
  tab[0][1]=0;
  tab[0][2]=0;
  tab[0][3]=0;
  tab[0][4]=0;
  tab[0][5]=0;
  tab[0][6]=0;
  tab[0][7]=0;
  tab[1][0]=0;
  tab[1][1]=0;
  tab[1][2]=0;
  tab[1][3]=0;
  tab[1][4]=0;
  tab[1][5]=0;
  tab[1][6]=0;
  tab[1][7]=0;
  tab[2][0]=0;
  tab[2][1]=0;
  tab[2][2]=0;
  tab[2][3]=0;
  tab[2][4]=0;
  tab[2][5]=0;
  tab[2][6]=0;
  tab[2][7]=0;
  tab[3][0]=0;
  tab[3][1]=0;
  tab[3][2]=0;
  tab[3][3]=1;
  tab[3][4]=-1;
  tab[3][5]=0;
  tab[3][6]=0;
  tab[3][7]=0;
  tab[4][0]=0;
  tab[4][1]=0;
  tab[4][2]=0;
  tab[4][3]=-1;
  tab[4][4]=1;
  tab[4][5]=0;
  tab[4][6]=0;
  tab[4][7]=0;
  tab[5][0]=0;
  tab[5][1]=0;
  tab[5][2]=0;
  tab[5][3]=0;
  tab[5][4]=0;
  tab[5][5]=0;
  tab[5][6]=0;
  tab[5][7]=0;
  tab[6][0]=0;
  tab[6][1]=0;
  tab[6][2]=0;
  tab[6][3]=0;
  tab[6][4]=0;
  tab[6][5]=0;
  tab[6][6]=0;
  tab[6][7]=0;
  tab[7][0]=0;
  tab[7][1]=0;
  tab[7][2]=0;
  tab[7][3]=0;
  tab[7][4]=0;
  tab[7][5]=0;
  tab[7][6]=0;
  tab[7][7]=0;
}

struct jogada {
  int linha, coluna;
};

void DesenhaTabuleiro(int tab[8][8]) {
  int i, j;
  printf("    +---+---+---+---+---+---+---+---+\n");
  for (i = 0; i < 8; i++) {
    printf("%d", i + 1);
    for (j = 0; j < 8; j++) {
      printf("   %d", tab[i][j]);

    }
    printf("\n    +---+---+---+---+---+---+---+---+\n");
  }
  printf("     1   2   3   4   5   6   7   8 \n");
}

struct jogada EscolhaJogada(struct jogada movimento) {
  printf("Escolha a linha que deseja jogar: ");
  scanf("%d", & movimento.linha);
  printf("Escolha a coluna que deseja jogar: ");
  scanf("%d", & movimento.coluna);
  return movimento;
}

int ExecutaJogada(int tab[8][8], int player, struct jogada mov) {
  mov.linha = mov.linha - 1;
  mov.coluna = mov.coluna - 1;
  int i, t, adversario,marcador=-5,contador=0;
  if (player == -1) {
    adversario = 1;
  } else if (player == 1) {
    adversario = -1;
  }
  if(tab[mov.linha][mov.coluna] == 0) {
      /*------------------verifica horizontalmente pra direita-----------------*/
      for (i = mov.coluna+1; i < 9; i++) {
        if(tab[mov.linha][i] == 0){
            i=9;
        }else if(tab[mov.linha][i] == player){
            marcador=i;
            contador=1;
        }
      }
      if(marcador!=-5){
        tab[mov.linha][mov.coluna] = player;
        for (i = mov.coluna+1; i < marcador+1; i++){
        if(tab[mov.linha][i] != 0) {
          if(tab[mov.linha][i] == adversario) {
            tab[mov.linha][i] = player;
          } else {
            i = 10;
          }
        } else {
          i = 10;
        }
      }
      }
      marcador=-5;
      /*------------------verifica horizontalmente pra esquerda----------------*/
      for(i = mov.coluna - 1; i > -1; i--) {
        if(tab[mov.linha][i] == 0){
            i=-2;
        }else if(tab[mov.linha][i] == player){
            marcador=i;
            contador=1;
        }
      }
      if(marcador!=-5){
        tab[mov.linha][mov.coluna] = player;
        for(i = mov.coluna - 1; i > marcador-1; i--){
        if(tab[mov.linha][i] != 0) {
        if(tab[mov.linha][i] != player) {
            tab[mov.linha][i] = player;
          } else {
            tab[mov.linha][i] = player;
            i = -2;
          }
        } else {
          tab[mov.linha][i] = player;
          i = -2;
        }
      }
      }
      marcador=-5;
      /*------------------verifica verticalmente pra baixo-----------------*/
      for(i = mov.linha + 1; i < 8; i++) {
        if(tab[i][mov.coluna] == 0){
            i=9;
        }else if(tab[i][mov.coluna] == player){
            marcador=i;
            contador=1;
        }
      }
      if(marcador != -5){
        tab[mov.linha][mov.coluna] = player;
      for(i = mov.linha + 1; i < marcador+1; i++){
      if (tab[i][mov.coluna] != 0) {
          if (tab[i][mov.coluna] != player) {
            tab[i][mov.coluna] = player;
          } else {
            tab[i][mov.coluna] = player;
            i = 9;
          }
        } else {
          tab[i][mov.coluna] = player;
          i = 9;
        }
        }
      }
        marcador=-5;
      /*------------------verifica verticalmente pra cima-----------------*/
      for (i = mov.linha - 1; i > -1; i--) {
        if(tab[i][mov.coluna] == 0){
             i=-2;
        }
        else if(tab[i][mov.coluna] == player){
            marcador=i;
            contador=1;
        }
      }
      if(marcador != -5){
      tab[mov.linha][mov.coluna] = player;
        for(i = mov.linha-1; i > marcador-1; i--){
            if (tab[i][mov.coluna] != 0) {
            if (tab[i][mov.coluna] == adversario) {
                tab[i][mov.coluna] = player;
            } else {
                tab[i][mov.coluna] = player;
                i = -2;
            }
            } else {
              tab[i][mov.coluna] = player;
              i = -2;
            }
        }
      }
        marcador=-5;
      /*------------------verifica diagonalmente pra cima-direita-----------------*/
        t = mov.coluna+1;
        for (i = mov.linha - 1; i > -1; i--) {
            if(tab[i][t] == 0){
                i=-2;
            }
            else if(tab[i][t] == player){
                marcador=i;
                contador=1;
            }
            t++;
        }
        t = mov.coluna+1;
        if(marcador!=-5){
            tab[mov.linha][mov.coluna] = player;
            for(i = mov.linha - 1; i > marcador-1; i--){
                if (tab[i][t] != 0) {
                    if (tab[i][t] == adversario) {
                        tab[i][t] = player;
                    } else {
                        tab[i][t] = player;
                        i = -2;
                    }
                } else {
                    tab[i][t] = player;
                    i = -2;
                }
                t++;
            }
        }

      /*------------------verifica diagonalmente pra cima-esquerda-----------------*/
      t = mov.coluna-1;
        marcador=-5;
      for (i = mov.linha -1; i > -1; i--) {
        if(tab[i][t] == 0){
            i=-2;
        }
        else if(tab[i][t] == player){
            marcador=i;
            contador=1;
        }
        t--;
      }
      t = mov.coluna-1;
      if(marcador != -5){
            tab[mov.linha][mov.coluna] = player;
        for(i = mov.linha - 1; i > marcador-1; i--){
            if (tab[i][t] != 0) {
            if (tab[i][t] == adversario) {
                tab[i][t] = player;
            } else {
                tab[i][t] = player;
                i = -2;
            }
            } else {
            tab[i][t] = player;
            i = -2;
            }
            t--;
        }
      }
        t = mov.coluna+1;
        marcador=-5;
      /*------------------verifica diagonalmente pra baixo-direita-----------------*/

      for (i = mov.linha +1 ; i < 8; i++) {
        if(tab[i][t] == 0){
            i=9;
        }
        else if(tab[i][t] == player){
            marcador=i;
            contador=1;
        }
        t++;
      }
      t= mov.coluna+1;
      if(marcador!=-5){
            tab[mov.linha][mov.coluna] = player;
        for(i = mov.linha + 1; i < marcador+1; i++){
            if (tab[i][t] != 0) {
            if (tab[i][t] == adversario) {
                tab[i][t] = player;
            } else {
                i = 9;
            }
            } else {

              tab[i][t] = player;
              i = 9;
            }
            t++;
        }
      }
      t = mov.coluna-1;
      marcador=-5;
      /*------------------verifica diagonalmente pra baixo-esquerda----------------*/
      for (i = mov.linha +1; i < 8; i++) {
        if(tab[i][t] == 0){
            i=9;
        }
        else if(tab[i][t] == player){
            marcador=i;
            contador=1;
        }
        t--;
      }
      t = mov.coluna-1;
      if(marcador!=-5){
        tab[mov.linha][mov.coluna] = player;
        for(i = mov.linha + 1; i < marcador+1; i++){

            if (tab[i][t] != 0) {
            if (tab[i][t] == adversario) {
                tab[i][t] = player;
              } else {
                tab[i][t] = player;
                i = 9;
              }
            } else {
              tab[i][t] = player;
              i = 9;
            }
            t--;
        }
      }
    }else{
    printf("Essa casa nao esta vazia, por favor escolha uma casa vazia.");
    return 0;
  }
  if(contador==1){
    return 1;
  }else{
    return 0;
  }
}

int main(void) {
  int tab[8][8], player = -1,i,t,cont=1,jogada,pretas=0,brancas=0;
  struct jogada movimento;
  IniciaTabuleiro(tab);
  while(cont==1){
    cont=0;
    DesenhaTabuleiro(tab);
    movimento = EscolhaJogada(movimento);
    jogada=ExecutaJogada(tab, player, movimento);
    if(jogada==1){
        if(player==-1){
            player=1;
        }else{
            player=-1;
        }
    }else{
        printf("Jogada invalida, por favor jogue novamente:\n");
    }
    for(i=0;i<8;i++){
        for(t=0;t<8;t++){
            if(tab[i][t]==0){
                cont=1;
                i=8;
                t=8;
            }
        }
    }
  }
  for(i=0;i<8;i++){
        for(t=0;t<8;t++){
            if(tab[i][t]==-1){
                pretas++;
            }else if(tab[i][t]==1){
                brancas++;
            }
        }
    }
    printf("Quantidade de pecas pretas: %d\n",pretas);
    printf("Quantidade de pecas brancas: %d\n",brancas);
    if(brancas>pretas){
        printf("O vencedor e o jogador branco!Parabens.\n");
    }else if(pretas>brancas){
        printf("O vencedor e o jogador preto!Parabens.\n");
    }else if(brancas==pretas){
        printf("Houve um empate.\n");
    }
}

/*
1) OK O tabuleiro deve ser representado por uma matriz 8x8 de números inteiros. As casas vazias possuem
o valor 0. As pedras brancas são indicadas pelo valor 1 e as pedras pretas pelo valor -1.
2) OK Cada jogada é representada pelo struct jogada (indicado abaixo).
3) OK Faça uma função IniciaTabuleiro(), que receba uma matriz como parâmetro e retorne o tabuleiro na
posição inicial.
4) OK O programa deve ter uma função DesenhaTabuleiro(), que receba o tabuleiro (matriz) e desenhe na
tela as pedras já colocadas no tabuleiro da melhor forma possível (parecendo uma matriz na tela). A
função também deve indicar na tela a numeração das linhas e colunas.
5) OK Faça uma função EscolheJogada(), na qual o jogador da vez indique uma linha e uma coluna onde ele
deseja colocar sua pedra. A jogada (struct jogada) deve ser retornada pela função.
6) OK Faça uma função ExecutaJogada() que recebe o tabuleiro (matriz), o jogador da vez e a jogada (struct jogada) retornada pela função EscolheJogada(). Se a jogada for válida, a função deve modificar o
tabuleiro de acordo com as regras e retornar 1; caso contrário, deve manter o tabuleiro como está e
retornar 0.
7) OK Se a função ExecutaJogada() retornar 0, o programa deve indicar que a jogada é inválida e solicitar
uma nova jogada. Isso deve acontecer até que o jogador da vez informe uma jogada válida.
Considere, nessa primeira versão do trabalho, que sempre existirá pelo menos uma jogada valida.
8) OK Se a função ExecutaJogada() retornar 1, o programa deve mudar o jogador da vez.
9) OK Quando nenhuma casa estiver vazia, o jogo deve informar quem foi o jogador vencedor ou se houve
empate.
*/
