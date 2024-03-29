/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB01 */

#include "lista.h"

int main () {
    int N, R, i;
    int *req;

    No *fichario;

    scanf("%d %d", &N, &R);

    //Cria a lista com os N inteiros, em ordem crescente
    fichario = createList(N);

    //Cria vetor que armazena a ordem dos arquivos a serem acessados
    req = malloc (R * sizeof(int));

    for (i = 0; i < R; i++)
        scanf("%d", &req[i]);

    MTF (fichario, req, R, N);
    TR (fichario, req, R, N);
    FC (fichario, req, R, N);
    
    //Desaloca memoria restante
    removeLista(fichario);
    
    free(req);
   
    return 0;
}