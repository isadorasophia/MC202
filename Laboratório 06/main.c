/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB06 - Pre, in e pos */

#include <stdio.h>
#include <stdlib.h>

/* Prototipos de funcao */
void imprimePos(char *preOrdem, char *inOrdem, int tam);
int find (char key, char *vet, int tam);

int main () {
    int C, N;
    char *s1, *s2;
    
    scanf ("%d", &C);
    
    /* Enquanto houver arvores a serem lidas */
    while (C--) {
        scanf("%d", &N);
        
        s1 = malloc ((N + 1) * sizeof(char));
        s2 = malloc ((N + 1) * sizeof(char));
        
        scanf("%s %s", s1, s2);
        
        imprimePos(s1, s2, N);
        printf("\n");
        
        free(s1);
        free(s2);
    }
    
    return 0;
}

/* A partir de pre-ordem e in-ordem, imprime a sequencia pos-ordem */
void imprimePos(char *preOrdem, char *inOrdem, int tam) {
    int indexRaiz;
    
    /* Encontra o endereco da raiz (o primeiro elemento de pre-ordem)
     * na sequencia in-ordem */
    indexRaiz = find(preOrdem[0], inOrdem, tam);
    
    /* Percorre a subarvore esquerda, se houver subarvore esquerda */
    if (indexRaiz != 0)
        imprimePos (preOrdem + 1, inOrdem, indexRaiz);
    
    /* Percorre a subarvore direita, se houver subarvore direita */
    if (indexRaiz != tam - 1)
        imprimePos (preOrdem + indexRaiz + 1, inOrdem + indexRaiz + 1, 
                    tam - indexRaiz - 1);
        
    printf("%c", preOrdem[0]);
}

/* Retorna o endereco de dado elemento em "vet" */
int find (char key, char *vet, int tam) {
    int i;
    
    for (i = 0; i < tam; i++) {
        if (vet[i] == key)
            return i;
    }
}