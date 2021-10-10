#include <stdio.h>
#include <stdlib.h>

// branca 1
// preta -1

struct posicao {
  int tabuleiro[8][8];
  int jogadorVez;
};

struct jogada {
  int linha, coluna, quant;
  struct jogada * prox, * ant;
};

struct posicao * IniciaTabuleiro() {
  struct posicao * auxPos = (struct posicao * ) malloc(sizeof(struct posicao));
  auxPos -> jogadorVez = -1;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      auxPos -> tabuleiro[i][j] = 0;
    }
  }
  auxPos->tabuleiro[3][3] = auxPos->tabuleiro[4][4] = 1;
auxPos->tabuleiro[4][3] = auxPos->tabuleiro[3][4] = -1;
    return auxPos;
}

struct jogada * CriaJogada() {
  struct jogada * sentinela = (struct jogada * ) malloc(sizeof(struct jogada));
  sentinela -> prox = sentinela;
  sentinela -> ant = sentinela;
  return sentinela;
};

struct jogada * CriaElemento(int linha, int coluna, int quant) {
  struct jogada * resp = (struct jogada * ) malloc(sizeof(struct jogada));
  resp -> linha = linha;
  resp -> coluna = coluna;
  resp -> quant = quant;
  resp -> prox = NULL;
  resp -> ant = NULL;
  return resp;
}

void insereFim(struct jogada * lista, int linha, int coluna, int quant) {
  struct jogada * novo = CriaElemento(linha, coluna, quant);
  novo -> prox = lista;
  novo -> ant = lista -> ant;
  lista -> ant -> prox = novo;
  lista -> ant = novo;
}

struct jogada * DestruirLista(struct jogada * lista) {
  struct jogada * aux = lista;
  lista -> ant -> prox = NULL;

  while (aux != NULL) {
    lista = lista -> prox;
    free(aux);
    aux = lista;
  }
  return NULL;
}

void DesenhaTabuleiro(struct posicao *pos){
    printf("Vez do jogador %d\n\n",pos->jogadorVez);

    printf("   0   1   2   3   4   5   6   7\n");
    for (int i=0;i<8;i++){
        printf("%d",i);
        for (int j=0;j<8;j++){
            if (pos->tabuleiro[i][j]!=0){
                printf(" %2d ",pos->tabuleiro[i][j]);
            }else printf("    ");
        }
        printf("\n");
    }
    printf("\n");
}

void ListarJogadas(struct jogada * lista) {
  struct jogada * aux = lista -> prox;
  int cont = 1;
  while (aux != lista) {
    printf("%d -- l:%d|c:%d Quantidade de pecas que serao sanduichadas: %d\n", cont, aux -> linha, aux -> coluna, aux -> quant);
    aux = aux -> prox;
    cont++;
  }
}


struct jogada * EscolhaJogada(struct jogada * jog) {
  int escolha = 0, cont;
  struct jogada * aux = jog -> prox;
  printf("Jogadas possiveis: \n");
  ListarJogadas(jog);
  scanf("%d", & escolha);
  for (cont = 1; cont < escolha; cont++) {
    aux = aux -> prox;
  }
  return aux;
}

int PodeJogar(struct posicao * pos, int l, int c, int deltaLinha, int deltaColuna) {
  int cont = 0;
  int i = l + deltaLinha;
  int j = c + deltaColuna;
  if(pos->tabuleiro[i][j]!=-pos->jogadorVez)  return 0;
  while (i >= 0 && j >= 0 && i < 8 && j < 8 && pos -> tabuleiro[i][j] == -pos -> jogadorVez) {
    i += deltaLinha;
    j += deltaColuna;
    cont++;
  }
  if (i < 0 || j < 0 || i >= 8 || j >= 8) return 0; ///cheguei até a borda do tabuleiro, não deu pra fazer sanduíche
  if (pos -> tabuleiro[i][j] == 0) return 0; ///cheguei até uma casa vazia, não deu pra fazer sanduíche

  if (cont > 0)  return cont; 
}

void Troca(struct posicao *pos,struct jogada *jog, int deltaLinha, int deltaColuna){
    int i = jog->linha+deltaLinha;
    int j = jog->coluna+deltaColuna;
    if(pos->tabuleiro[i+deltaLinha][j+deltaColuna]!=0){
    while (pos->tabuleiro[i][j]==-pos->jogadorVez){
        pos->tabuleiro[i][j] = -pos->tabuleiro[i][j];
        i += deltaLinha;
        j += deltaColuna;
    }
    }
}

void ExecutaJogada(struct posicao *pos,struct jogada *jog){
    if (jog==NULL) pos->jogadorVez = -pos->jogadorVez;
    int deltaColuna,deltaLinha;
    pos->tabuleiro[jog->linha][jog->coluna] = pos->jogadorVez;
    for (deltaLinha=-1;deltaLinha<=1;deltaLinha++){
        for (deltaColuna=-1;deltaColuna<=1;deltaColuna++){
            if (deltaLinha!=0||deltaColuna!=0){
                    Troca(pos,jog,deltaLinha,deltaColuna);
            }
        }
    }
    pos->jogadorVez = -pos->jogadorVez;
}

struct jogada * CriaJogadasValidas(struct posicao * pos) {
  int i, j, deltaLinha, deltaColuna, cont;
  struct jogada * jog;
  jog = CriaJogada();
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (pos -> tabuleiro[i][j] == 0) {
        for (deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
          for (deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
            if (deltaLinha != 0 || deltaColuna != 0) {
                cont = PodeJogar(pos, i, j, deltaLinha, deltaColuna);
              if (cont > 0) {
                insereFim(jog, i, j, cont);
              }
            }
          }
        }
      }
    }
  }
  if (jog -> prox == jog) jog = NULL;
  return jog;
};

void InformaVencedor(struct posicao *pos){
    int brancas=0,pretas=0;
    int i,j;
    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            if (pos->tabuleiro[i][j]==1)
                brancas++;
            else pretas++;
        }
    }
    if (brancas>pretas){
        printf("Brancas venceram!!!\n");
    }else if (pretas>brancas){
        printf("Pretas venceram!!!\n");
    }else printf("Empate!!!\n");
}

int VerificaJogadas(struct posicao *pos){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(pos->tabuleiro[i][j]==0) return 1;
        }
    }
    return 0;
}

int main(void) {
  struct posicao * pos;
  struct jogada * jog;
  struct jogada * escolhida;
  int i, t, cont = 1, aux=1;
  struct jogada movimento;
  pos = IniciaTabuleiro();
  while(aux!=0){
    aux=VerificaJogadas(pos);
    DesenhaTabuleiro(pos);
    jog = CriaJogadasValidas(pos);
    if(jog!=NULL){
        escolhida=EscolhaJogada(jog);
    }
    ExecutaJogada(pos,escolhida);
    jog=DestruirLista(jog);
  }
}

/*
1)ok O struct Posicao (abaixo) representa o tabuleiro do jogo (matriz 8x8 de números inteiros) e indica também qual é o jogador da vez. As casas vazias possuem o valor 0. As pedras brancas são indicadas pelo valor 1 e as pedras pretas pelo valor -1.
2)ok Cada jogada é representada pelo struct jogada (indicado abaixo).
3)ok Faça uma função IniciaTabuleiro(), sem parâmetros, que retorne a posição inicial do jogo (o tabuleiro na posição inicial o jogador da vez sendo o jogador de pretas).
4)ok O programa deve ter uma função DesenhaTabuleiro(), que receba um struct Posicao e desenhe na tela as pedras já colocadas no tabuleiro da melhor forma possível (parecendo uma matriz na tela). A função também deve indicar na tela a numeração das linhas e colunas.
5)ok Faça uma função CalculaJogadasValidas(), que deve receber, como parâmetro, a posição atual do jogo e deve retornar uma lista circular duplamente encadeada, contendo todas as possíveis jogadas que podem ser feitas pelo jogador da vez. Se não houver nenhuma jogada possível, a função deve retornar NULL. Um ponteiro da main deve receber o resultado da função.
6)ok Faça uma função EscolheJogada(), que receba como parâmetro apenas a lista de jogadas possíveis. A função deve mostrar todas essas jogadas na tela e deve perguntar ao usuário qual jogada ele quer fazer. A jogada escolhida deve ser retornada na forma de um ponteiro para o elemento (escolhido pelo usuário) da lista. A função EscolheJogada() só será executada se houver pelo menos uma jogada válida na lista de jogadas retornada pela função CalculaJogadasValidas().
7) ok Faça uma função ExecutaJogada() que recebe a posição atual e a jogada (ponteiro) retornada pela função EscolheJogada(). A função deve modificar o tabuleiro de acordo com as regras e inverter o jogado da vez. Se a lista de jogadas válidas estiver vazia, deve ser passado um ponteiro com valor NULL como sendo a jogada escolhida. Nesse caso, a função deve apenas mudar o jogador da vez, sem alterar o tabuleiro.

já criei a função DestruirLista
8) ok Após a execução da função, se a lista de jogadas válidas não estiver vazia, ela deve ser destruída (memória liberada).
9) ok Após a liberação da memória (se ocorrer), se ainda houver casas vazias no tabuleiro, o programa deve voltar ao passo 4. Caso o tabuleiro esteja completamente cheio, o programa deve indicar quem foi o vencedor (ou se houve empate) e encerrar.
*/
