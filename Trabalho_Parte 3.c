#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// branca 1
// preta -1
#define MAX_NIVEL 3
int TAB[8][8];

struct posicao {
    int tabuleiro[8][8];
    int jogadorVez;
};

struct jogada {
    int linha, coluna, quant,max;
    struct jogada * prox, * ant;
};

void IniciaTabuleiroPontuacao(){
    TAB[0][0] = TAB[0][7] = TAB[7][0] = TAB[7][7] = 120;
    TAB[2][2] = TAB[2][5] = TAB[5][2] = TAB[5][5] = 15;
    TAB[1][1] = TAB[1][6] = TAB[6][1] = TAB[6][6] = -40;
    TAB[0][1] = TAB[1][0] = TAB[0][6] = TAB[1][7] = TAB[6][0] = TAB[7][1] = TAB[7][6] = TAB[6][7] = -20;
    TAB[0][2] = TAB[2][0] = TAB[0][5] = TAB[2][7] = TAB[5][0] = TAB[7][2] = TAB[7][5] = TAB[5][7] = 20;
    TAB[3][0] = TAB[4][0] = TAB[0][3] = TAB[0][4] = TAB[7][3] = TAB[7][4] = TAB[3][7] = TAB[4][7] = 5;
    TAB[1][2] = TAB[1][3] = TAB[1][4] = TAB[1][5] = TAB[2][1] = TAB[3][1] = TAB[4][1] = TAB[5][1] = TAB[6][2] = TAB[6][3] = TAB[6][4] = TAB[6][5] = TAB[2][6] = TAB[3][6] = TAB[4][6] = TAB[5][6] = -5;
    TAB[2][3] = TAB[2][4] = TAB[3][2] = TAB[3][3] = TAB[3][4] = TAB[3][5] = TAB[4][2] = TAB[4][3] = TAB[4][4] = TAB[4][5] = TAB[5][3] = TAB[5][4] = 3;
}

struct posicao * IniciaTabuleiro() {
    struct posicao * auxPos = (struct posicao * ) malloc(sizeof(struct posicao)+1);
    auxPos -> jogadorVez = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auxPos -> tabuleiro[i][j] = 0;
        }
    }
    auxPos -> tabuleiro[3][3] = auxPos -> tabuleiro[4][4] = 1;
    auxPos -> tabuleiro[4][3] = auxPos -> tabuleiro[3][4] = -1;
    return auxPos;
}

struct jogada * CriaJogada() {
    struct jogada * sentinela = (struct jogada * ) malloc(sizeof(struct jogada)+1);
    sentinela -> prox = sentinela;
    sentinela -> ant = sentinela;
    return sentinela;
};

struct jogada * CriaElemento(int linha, int coluna, int quant) {
    struct jogada * resp = (struct jogada * ) malloc(sizeof(struct jogada)+1);
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

void DestruirLista(struct jogada * lista) {
    struct jogada * aux = lista;
    lista -> ant -> prox = NULL;

    while (aux != NULL) {
        lista = lista -> prox;
        free(aux);
        aux = lista;
    }

}

void DesenhaTabuleiro(struct posicao * pos) {
    if(pos->jogadorVez!=0)printf("Vez do jogador %d\n",pos->jogadorVez);
    printf("   0   1   2   3   4   5   6   7\n");
    for (int i = 0; i < 8; i++) {
        printf("%d", i);
        for (int j = 0; j < 8; j++) {
            if (pos -> tabuleiro[i][j] != 0) {
                printf(" %2d ", pos -> tabuleiro[i][j]);
            } else printf("    ");
        }
        printf("\n");
    }
    printf("\n");
}

int ListarJogadas(struct jogada * lista) {
    struct jogada * aux = lista -> prox;
    int cont = 0;
    while (aux != lista) {
        printf("%d -- l:%d|c:%d Quantidade de pecas que serao sanduichadas: %d\n", cont+1, aux -> linha, aux -> coluna, aux -> quant);
        aux = aux -> prox;
        cont++;
    }
    return cont;
}

struct jogada * EscolhaJogada(struct jogada * jog) {
    int escolha = 0, cont,max,auxCont=0;
    struct jogada * aux = jog -> prox;
    while(auxCont==0){
        printf("Jogadas possiveis: \n");
        max=ListarJogadas(jog);
        scanf("%d", & escolha);
        if(escolha<=0||escolha>max){
            printf("O numero da jogada e invalido, por favor escolha outra jogada.\n");
        }else auxCont=1;
    }
    for (cont = 1; cont < escolha; cont++) {
        aux = aux -> prox;
    }
    return aux;
}

int PodeJogar(struct posicao * pos, int l, int c, int deltaLinha, int deltaColuna) {
    int cont = 0;
    int i = l + deltaLinha;
    int j = c + deltaColuna;
    if (pos -> tabuleiro[i][j] != -pos -> jogadorVez) return 0;
    while (i >= 0 && j >= 0 && i < 8 && j < 8 && pos -> tabuleiro[i][j] == -pos -> jogadorVez) {
        i += deltaLinha;
        j += deltaColuna;
        cont++;
    }
    if (i < 0 || j < 0 || i >= 8 || j >= 8) return 0; ///cheguei até a borda do tabuleiro, não deu pra fazer sanduíche
    if (pos -> tabuleiro[i][j] == 0) return 0; ///cheguei até uma casa vazia, não deu pra fazer sanduíche

    if (cont > 0) return cont;
}

void Troca(struct posicao * pos, struct jogada * jog, int deltaLinha, int deltaColuna) {
    int i = jog -> linha + deltaLinha;
    int j = jog -> coluna + deltaColuna;
    if (pos -> tabuleiro[i + deltaLinha][j + deltaColuna] != 0) {
        while (pos -> tabuleiro[i][j] == -pos -> jogadorVez) {
            pos -> tabuleiro[i][j] = -pos -> tabuleiro[i][j];
            i += deltaLinha;
            j += deltaColuna;
        }
    }
}

void ExecutaJogada(struct posicao * pos, struct jogada * jog) {
    if (jog == NULL || jog->linha==9 || jog->coluna == 9) pos -> jogadorVez = -pos -> jogadorVez;
    else{
        int deltaColuna, deltaLinha;
        pos -> tabuleiro[jog -> linha][jog -> coluna] = pos -> jogadorVez;
        for (deltaLinha=-1;deltaLinha<=1;deltaLinha++){
            for (deltaColuna=-1;deltaColuna<=1;deltaColuna++){
                if (deltaLinha!=0||deltaColuna!=0){
                    if (PodeJogar(pos,jog->linha,jog->coluna,deltaLinha,deltaColuna)>0){
                        Troca(pos,jog,deltaLinha,deltaColuna);
                    }
                }
            }
        }
        pos -> jogadorVez = -pos -> jogadorVez;
    }
}

struct jogada * CriaJogadasValidas(struct posicao * pos) {
    int i, j, deltaLinha, deltaColuna, cont = 0;
    struct jogada * jog;
    jog = CriaJogada();
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (pos -> tabuleiro[i][j] == 0) {
                for (deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                    for (deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                        if (deltaLinha != 0 || deltaColuna != 0) {
                            cont = cont + PodeJogar(pos, i, j, deltaLinha, deltaColuna);
                        }
                    }
                }
                if (cont > 0) {
                    insereFim(jog, i, j, cont);
                }
            }
            cont = 0;
        }
    }
    if (jog -> prox == jog) {
        insereFim(jog, 9, 9, 0);
    }
    return jog;
};

void InformaVencedor(struct posicao * pos) {
    int brancas = 0, pretas = 0;
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (pos -> tabuleiro[i][j] == 1)
                brancas++;
            else pretas++;
        }
    }
    if (brancas > pretas) {
        printf("Brancas venceram!!!\n");
    } else if (pretas > brancas) {
        printf("Pretas venceram!!!\n");
    } else printf("Empate!!!\n");
}

int VerificaJogadas(struct posicao * pos) {
    struct jogada *jog;
    int max;
    jog=CriaJogadasValidas(pos);
    if(jog->prox->linha!=9||jog->prox->coluna!=9) return 1;
    return 0;
}

double CalculaValor(struct posicao *pos,int l, int c){
    double resp=TAB[l][c];
    return resp;
}

double AvaliaPosicao(struct posicao * pos) {
    double jog1=0,jog2=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(pos->tabuleiro[i][j]==1) jog1=CalculaValor(pos,i,j);
            else if(pos->tabuleiro[i][j]==-1){
                jog2=CalculaValor(pos,i,j);
            }
        }
    }
    return jog2-jog1;
}

struct jogada * ExecutaIA(struct posicao * pos, int nivel, double alfa, double beta) {
    struct jogada * lista, * jogadaAux;
    struct posicao *posCopia=(struct posicao * ) malloc(sizeof(struct posicao));
    int podado = 0,max;
    double melhorValor, valorJogada;
    struct jogada * melhorjogada, * jogadaIA;
    memcpy(posCopia,pos,sizeof(struct posicao));
    if (nivel % 2 == 0) {
        posCopia -> jogadorVez = 1;
        lista = CriaJogadasValidas(posCopia);
        melhorValor = -INFINITY;
    } else {
        posCopia -> jogadorVez = -1;
        lista = CriaJogadasValidas(posCopia);
        melhorValor = INFINITY;
    }
    if(lista!=NULL){
        jogadaAux = lista -> prox;
        while (jogadaAux != lista && podado == 0) {
            memcpy(posCopia,pos,sizeof(struct posicao));
            ExecutaJogada(posCopia, jogadaAux);
            if (nivel < MAX_NIVEL) {
                if (nivel % 2 == 0) jogadaIA = ExecutaIA(posCopia, nivel + 1, melhorValor, beta);
                else jogadaIA = ExecutaIA(posCopia, nivel + 1, alfa, melhorValor);
                ExecutaJogada(posCopia, jogadaIA);
            }
            valorJogada = AvaliaPosicao(posCopia);
            if (valorJogada < alfa || valorJogada > beta) podado = 1;
            if (nivel % 2 == 0 && valorJogada >= melhorValor) {
                melhorValor = valorJogada;
                melhorjogada = jogadaAux;
            } else if (nivel % 2 != 0 && valorJogada <= melhorValor) {
                melhorValor = valorJogada;
                melhorjogada = jogadaAux;
            }
            jogadaAux = jogadaAux->prox;
        }return melhorjogada;
    }
}

void SalvaJogada(struct jogada * Jogada) {
    FILE * arq;
    //abrir o arquivo de acordo com o valor do ponteiro
    if (Jogada == NULL) {
        arq = fopen("jogadas.bin", "ab");
        fclose(arq);
    } else { //salvar a jogada, se for o caso
        arq = fopen("jogadas.bin", "ab");
        fwrite( & Jogada -> linha, sizeof(int), 1, arq);
        fwrite( & Jogada -> coluna, sizeof(int), 1, arq);
    }
    //fechar o arquivo
    fclose(arq);
}

int main(void) {
    FILE *arq;
    arq=fopen("jogadas.bin","wb");
    fclose(arq);
    IniciaTabuleiroPontuacao();
    struct posicao * pos;
    pos = IniciaTabuleiro();
    struct jogada * jog;
    struct jogada * escolhida;
    int i, t, cont = 1, aux = 1;
    struct jogada movimento;
    while (aux != 0) {
        if(pos->jogadorVez==-1){
            DesenhaTabuleiro(pos);
            jog = CriaJogadasValidas(pos);
            if (jog != NULL) {
                escolhida = EscolhaJogada(jog);
            }
            ExecutaJogada(pos, escolhida);
            SalvaJogada(escolhida);
            DestruirLista(jog);
        }else {
            jog=ExecutaIA(pos,0,-INFINITY,INFINITY);
            ExecutaJogada(pos,jog);
            SalvaJogada(jog);
        }
        aux = VerificaJogadas(pos);
        system("cls");
        printf("Jogada IA: Linha: %d Coluna: %d\n",jog->linha,jog->coluna);
        if(aux==0){
            pos->jogadorVez=-pos->jogadorVez;
            aux = VerificaJogadas(pos);
            if(aux==0) printf("Nao existem mais jogadas validas. O jogo sera encerrado.\n");
            else printf("O jogador da vez nao tem jogadas validas. A vez sera passada ao proximo jogador\n");
        }
    }
    system("cls");
    pos->jogadorVez=0;
    DesenhaTabuleiro(pos);
    InformaVencedor(pos);
}
