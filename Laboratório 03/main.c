/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB03 */

#include <stdio.h>
#include <stdlib.h>
#include "lda.h"

int main () {
    int H, W;
    int i, j;
    Celula **mapa;

    scanf("%d %d", &H, &W);
    
    // Aloca a matriz do mapa
    mapa = malloc (H * sizeof (Celula));
    for (i = 0; i < H; i++)
        mapa[i] = malloc (W * sizeof (Celula));

    // Leitura do mapa e inicializacao de cada celula
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            scanf("%d", &mapa[i][j].altura);
            mapa[i][j].i = i;
            mapa[i][j].j = j;
            mapa[i][j].rotulo = '\0';
        }
    }
   
    ldaAlgorithm (H, W, mapa);
    
    // Imprime resposta
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            printf("%c ", mapa[i][j].rotulo);
        }
        printf("\n");
    }
    
    // Libera memoria
    for (i = 0; i < H; i++)
        free(mapa[i]);
    free(mapa);
    
    return 0;
}