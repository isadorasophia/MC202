#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

/* árvore.c - falta implementar funções arvore23_insere e arvore23_busca*/
/* Cuidado ao alterar funções já implementadas*/

/* arvore23_aloca() - Cria árvore 2-3. */
arvore23_t *arvore23_aloca()
{
    return NULL;
}

/* arvore23_libera() - Libera árvore 2-3. */
void arvore23_libera(arvore23_t *t)
{
    if(t!=NULL){
        arvore23_libera(t->filho1);
        arvore23_libera(t->filho2);
        arvore23_libera(t->filho3);
        free(t); t=NULL;
    }
}

void arvore23_insere(arvore23_t **t, int chave)
{
    if (*t==NULL) /* Se t for vazia */ {
        (*t) = (arvore23_t *) malloc(sizeof(arvore23_t));
        (*t)->nchaves = 1;
        (*t)->chave1 = chave;
        (*t)->pai = (*t)->filho1 = (*t)->filho2 = (*t)->filho3 = NULL;
        return;
    }
    
    if (arvore23_busca((*t), chave)) /* Se chave ja existe em árvore */ 
        return;
    
    int nodeFound = 0, located = 0; /* Flags */
    int aux, goesUp;
    arvore23_t *target = *t, *target_aux, *filhoUp;

    /* Enquanto nao encontra a folha adequada... */
    while (!nodeFound) {
        /* Caso nao seja um no cheio */
        if (target->nchaves == 1) {
            /* Caso seja menor... */
            if (chave < target->chave1) {
                /* Nao eh um no folha, continua a percorrer */
                if (target->filho1)
                    target = target->filho1;
                
                /* Eh um no folha, simplesmente aloca */
                else {
                    aux = target->chave1;
                    target->chave1 = chave;
                    target->chave2 = aux;
                    
                    target->nchaves++;
                    
                    return;
                }
            }
            
            /* ...ou caso seja maior */
            else if (chave > target->chave1) {
                /* Nao eh um no folha, continua a percorrer */
                if (target->filho2)
                    target = target->filho2;
                
                /* Eh um no folha, simplesmente aloca */
                else {
                    target->chave2 = chave;
                    target->nchaves++;
                    
                    return;
                }
            }
        }
        
        /* ...ou caso seja um no cheio */
        else {
            /* Se a chave for o menor elemento */
            if (chave < target->chave1) {
                /* Nao eh um no folha, continua a percorrer */
                if (target->filho1) {
                    target = target->filho1;
                }
                
                /* Eh um no folha, aloca - realizando a divisao da folha */
                else {
                    nodeFound = 1;
                    
                    goesUp = target->chave1;
                    
                    target->chave1 = chave;
                    
                    /* Divide a folha */
                    filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                    filhoUp->nchaves = 1;
                    filhoUp->chave1 = target->chave2;
                    filhoUp->pai = filhoUp->filho1 = filhoUp->filho2 =
                    filhoUp->filho3 = NULL;
                    
                    target->nchaves--;
                }
            }
            
            /* Se a chave for o elemento intermediario */
            else if (chave > target->chave1 && chave < target->chave2) {       
                /* Nao eh um no folha, continua a percorrer */
                if (target->filho2) {
                    target = target->filho2;
                }
                
                /* Eh um no folha, aloca - realizando a divisao da folha */
                else {
                    nodeFound = 1;
                    
                    goesUp = chave;
                    
                    /* Divide a folha */
                    filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                    filhoUp->nchaves = 1;
                    filhoUp->chave1 = target->chave2;
                    filhoUp->pai = filhoUp->filho1 = filhoUp->filho2 =
                    filhoUp->filho3 = NULL;
                    
                    target->nchaves--;
                }
            }
            
            /* Se a chave for o maior elemento */
            else {
                /* Nao eh um no folha, continua a percorrer */
                if (target->filho3) {
                    target = target->filho3;
                }
                
                /* Eh um no folha, aloca - realizando a divisao da folha */
                else {
                    nodeFound = 1;
                    
                    goesUp = target->chave2;
                    
                    filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                    filhoUp->nchaves = 1;
                    filhoUp->chave1 = chave;
                    filhoUp->pai = filhoUp->filho1 = filhoUp->filho2 =
                    filhoUp->filho3 = NULL;
                    
                    target->nchaves--;
                }
            }
        }
    }

    /* A partir do caso de um no folha lotado, encontra a regiao adequada
     * para a insercao desta chave - estudando o target->pai */
    while (!located) {
        /* Target->pai nao esta lotado - portanto, apropriado para a insercao */
        if (target->pai && target->pai->nchaves == 1) {
            target = target->pai;
            located = 1;
            
            /* Caso seja a menor chave */
            if (goesUp < target->chave1) {
                target->nchaves++;
               
                aux = target->chave1;                
                target->chave1 = goesUp;
                target->chave2 = aux;
               
                /* Assim, o filho 2 se torna o filho 3 */
                target_aux = target->filho2;
                target->filho2 = filhoUp;
                target->filho3 = target_aux;
                
                target->filho2->pai = target;
                target->filho3->pai = target;
            }
            
            /* ...ou caso seja a maior */
            else {
                target->nchaves++;
                
                target->chave2 = goesUp;
                
                target->filho3 = filhoUp;
                filhoUp->pai = target;
            }
        }
        
        /* Target->pai esta lotado, devem ser realizas mais divisoes */
        else {
            /* Caso seja o menor elemento */
            if (target->pai && goesUp < target->pai->chave1) {
                target = target->pai;
                
                aux = target->chave1;
                target->chave1 = goesUp;
                goesUp = aux;
              
                target_aux = target->filho2;
                
                target->filho2 = filhoUp;
                target->filho2->pai = target;
                
                filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                filhoUp->nchaves = 1;
                filhoUp->chave1 = target->chave2;
                filhoUp->pai = NULL;
                
                filhoUp->filho1 = target_aux;
                filhoUp->filho1->pai = filhoUp;
                
                filhoUp->filho2 = target->filho3;
                filhoUp->filho2->pai = filhoUp;
                
                filhoUp->filho3 = NULL;
                
                target->nchaves--;
            }
            
            /* ...ou caso seja o elemento intermediario */
            else if (target->pai && goesUp > target->pai->chave1
                && goesUp < target->pai->chave2) {
                target = target->pai;
            
                target_aux = filhoUp;
                
                filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                filhoUp->nchaves = 1;
                filhoUp->chave1 = target->chave2;
                filhoUp->pai = NULL;
            
                filhoUp->filho1 = target_aux;
                filhoUp->filho1->pai = filhoUp;
                
                filhoUp->filho2 = target->filho3;
                filhoUp->filho2->pai = filhoUp;
                
                filhoUp->filho3 = NULL;
                
                target->nchaves--;
            }
            
            /* ...ou caso seja o maior elemento */
            else if (target->pai && goesUp > target->pai->chave2) {
                target = target->pai;
                
                aux = target->chave2;
                target->chave2 = goesUp;
                goesUp = aux;
                
                target_aux = filhoUp;
                
                filhoUp = (arvore23_t *) malloc(sizeof(arvore23_t));
                filhoUp->nchaves = 1;
                filhoUp->chave1 = target->chave2;
                filhoUp->pai = NULL;
                
                filhoUp->filho1 = target->filho3;
                filhoUp->filho1->pai = filhoUp;
                
                filhoUp->filho2 = target_aux;
                filhoUp->filho2->pai = filhoUp;
                
                filhoUp->filho3 = NULL;
                
                target->nchaves--;
            }
            
            /* Caso tenha chegado ao no da raiz, cria uma nova raiz */
            if (target == *t) {                
                located = 1;
                
                target->pai = (arvore23_t *) malloc(sizeof(arvore23_t));
                target->pai->nchaves = 1;
                target->pai->chave1 = goesUp;
                
                target->pai->filho1 = target;
                
                target->pai->filho2 = filhoUp;
                target->pai->filho2->pai = target->pai;
                
                target->pai->filho3 = NULL;
                
                *t = target->pai;
            }
        }
    }
}

int arvore23_busca(arvore23_t *t, int chave)
{
    if (!t)
        return 0;
    
    /* Assumindo que o no possui, pelo menos, uma chave */
    if (chave < t->chave1)
        return arvore23_busca(t->filho1, chave);
    else if (chave > t->chave1)
        /* Caso tenha mais de um no */
        if (t->nchaves > 1)
            if (chave < t->chave2)
                return arvore23_busca(t->filho2, chave);
            else if (chave > t->chave2)
                return arvore23_busca(t->filho3, chave);
            /* Encontrou! */
            else
                return 1;
        /* Apela para o caso do segundo filho */
        else
            return arvore23_busca(t->filho2, chave);
    /* Encontrou! */
    else
        return 1;
}

void arvore23_imprime(arvore23_t *t){
    if(t!=NULL){
        printf("( ");
        if (t->nchaves == 1){
            arvore23_imprime(t->filho1);
            printf("%d ",t->chave1);
            arvore23_imprime(t->filho2);
        }
        else /*t->nchaves == 2*/{
            arvore23_imprime(t->filho1);
            printf("%d ",t->chave1);
            arvore23_imprime(t->filho2);
            printf("%d ",t->chave2);
            arvore23_imprime(t->filho3);
        }
        printf(") ");
    }
}