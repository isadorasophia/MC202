/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB06 - Pre, in e pos
 * A Partir de uma sequencia in-ordem e pos-ordem, imprime pre-ordem */

#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND -1

/* Prototipos de funcao */
void imprimePre(char *posOrdem, char *inOrdem, int tam);
int find (char key, char *vet, int tam);

int main () {
    int C, N;
    char *s1, *s2;
    
    scanf ("%d", &C);
    
    /* Enquanto houverem arvores a serem lidas */
    while (C--) {
        scanf("%d", &N);
        
        s1 = malloc ((N + 1) * sizeof(char));
        s2 = malloc ((N + 1) * sizeof(char));
        
        scanf("%s %s", s1, s2);
        
        /* Imprime a sequencia pre-ordem da arvore */
        imprimePre(s1, s2, N);
        printf("\n");
        
        free(s1);
        free(s2);
    }
    
    return 0;
}

/* A partir de pos-ordem e in-ordem, imprime a sequencia pre-ordem */
void imprimePre(char *posOrdem, char *inOrdem, int tam) {
    int indexRaiz;
    
    /* Encontra o endereco da raiz (sendo esta o ultimo elemento da pos-ordem)
     * na sequencia in-ordem */
    indexRaiz = find(posOrdem[tam - 1], inOrdem, tam);
    
    if (indexRaiz == NOT_FOUND)
        return;
    
    /* Imprime a raiz ou a folha antes de percorrer as possiveis subarvores */
    printf("%c", posOrdem[tam - 1]);
    
    /* Percorre a subarvore esquerda, se houver subarvore esquerda */
    if (indexRaiz != 0)
        imprimePre (posOrdem, inOrdem, indexRaiz);
    
    /* Percorre a subarvore direita, se houver subarvore direita */
    if (indexRaiz != tam - 1)
        imprimePre (posOrdem + indexRaiz, inOrdem + indexRaiz + 1,
                    tam - indexRaiz - 1);
}

/* Retorna o endereco de dado elemento em "vet" */
int find (char key, char *vet, int tam) {
    int i;
    
    for (i = 0; i < tam; i++) {
        if (vet[i] == key)
            return i;
    }
    
    /* Caso nao encontre o elemento no vetor */
    return NOT_FOUND;
}