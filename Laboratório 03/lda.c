#include "lda.h"

// Retorna se determinada celula se trata de um ponto dissipador
int VerificaDissipador (int i, int j, int H, int W, Celula **mapa) {
    //Elemento acima
    if (i != 0 && 
        mapa[i - 1][j].altura < mapa[i][j].altura)
        return 0;
    //Elemento abaixo
    else if (i != H - 1 && 
        mapa[i + 1][j].altura < mapa[i][j].altura)
        return 0;
    //Elemento a esquerda
    else if (j != 0 && 
        mapa[i][j - 1].altura < mapa[i][j].altura)
        return 0;
    //Elemento a direita
    else if (j != W - 1 &&
        mapa[i][j + 1].altura < mapa[i][j].altura)
        return 0;
    
    return 1;
}

// Encontra os vizinhos da celula "n", os rotula e os insere na fila ordenada
void EncontraVizinhos(Celula n, int H, int W, 
                      FilaOrdenada filaOrdenada[], Celula **mapa) {

    //Elemento acima
    if (n.i != 0 && 
        mapa[n.i - 1][n.j].rotulo == '\0') {
        mapa[n.i - 1][n.j].rotulo = n.rotulo;
        InsFila(mapa[n.i - 1][n.j], 
                &(filaOrdenada[mapa[n.i - 1][n.j].altura].s),
                &(filaOrdenada[mapa[n.i - 1][n.j].altura].t));
    } // Elemento abaixo
    if (n.i != H - 1 && 
        mapa[n.i + 1][n.j].rotulo == '\0') {
        mapa[n.i + 1][n.j].rotulo = n.rotulo;
        InsFila(mapa[n.i + 1][n.j], 
                &(filaOrdenada[mapa[n.i + 1][n.j].altura].s),
                &(filaOrdenada[mapa[n.i + 1][n.j].altura].t));
    } //Elemento a esquerda
    if (n.j != 0 && 
        mapa[n.i][n.j - 1].rotulo == '\0') {
        mapa[n.i][n.j - 1].rotulo = n.rotulo;
        InsFila(mapa[n.i][n.j - 1], 
                &(filaOrdenada[mapa[n.i][n.j - 1].altura].s),
                &(filaOrdenada[mapa[n.i][n.j - 1].altura].t));
    } //Elemento a direita
    if (n.j != W - 1 && 
        mapa[n.i][n.j + 1].rotulo == '\0') {
        mapa[n.i][n.j + 1].rotulo = n.rotulo;
        InsFila(mapa[n.i][n.j + 1], 
                &(filaOrdenada[mapa[n.i][n.j + 1].altura].s),
                &(filaOrdenada[mapa[n.i][n.j + 1].altura].t));
    }
}

// Encontra o elemento de maior prioridade na fila ordenada e executa a
// rotulacao em seus elementos vizinhos
void EncontraPrioridade (FilaOrdenada filaOrdenada[], 
                         Celula **mapa, int H, int W) {
    int i;
    Celula aux;
    
    for (i = 0; i < 101; i++) {
        if(!FilaVazia(filaOrdenada[i].s)) {
            aux = filaOrdenada[i].s->n;
            
            // Remove o elemento da fila
            RemFila(&(filaOrdenada[i].s), &(filaOrdenada[i].t));
            
            // Encontra seus vizinhos na matriz, os rotula e os adiciona a fila
            // ordenada
            EncontraVizinhos(aux, H, W, filaOrdenada, mapa);
            
            return;
        }
    }
}

// Atribui os rotulos de cada celula seguindo o algoritmo
void ldaAlgorithm (int H, int W, Celula **mapa) {
    int i, j;
    char rotulo = 'a';
    FilaOrdenada *filaOrdenada;
    
    // Inicia vetor de fila odernada
    filaOrdenada = malloc (101 * sizeof(FilaOrdenada));
    IniciaFilaOrdenada(filaOrdenada, 101);
    
    // Encontra os pontos dissipadores
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            //Caso tenha encontrado, configura o rotulo e a fila adequada
            if (VerificaDissipador(i, j, H, W, mapa)) {
                mapa[i][j].rotulo = rotulo++;
                InsFila(mapa[i][j], &(filaOrdenada[mapa[i][j].altura].s),
                        &(filaOrdenada[mapa[i][j].altura].t));
            }
        }
    }
    
    // Enquanto a fila nao esta vazia
    while (!FilaOrdenadaVazia(filaOrdenada, 101)) {
        EncontraPrioridade(filaOrdenada, mapa, H, W);
    }
    
    free(filaOrdenada);
}