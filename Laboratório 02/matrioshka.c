#include "matrioshka.h"

//Retorna se a entrada de "n" inteiros eh Matrioshka
int AnalisaSequencia(int n) {
    int isValid = 1;
    long int a;
    No *t;
   
    t = IniciaPilha();
   
    while (n-- > 0) {
        scanf("%ld", &a);
        
        //Caso seja valida, verifica se a nova entrada invalida a sequencia
        if (isValid && !IsMatrioshka(t, a)) {
            isValid = 0;
        }
    }
    
    /* Caso a pilha esteja vazia e valida, retorna sucesso. Caso contrario,
     * retorna invalida. */
    if (PilhaVazia (t) && isValid) {
        FreePilha(t);
        return 1;
    } else {
        FreePilha(t);
        return 0;
    }
}

//Introduz "a" para a sequencia e retorna se esta continua valida
int IsMatrioshka (No *t, long int a) {
    //Caso seja um numero negativo, trata-se de um novo brinquedo
    if (a < 0) {
        //Caso ja exista um brinquedo, computa como contato direto
        if (!PilhaVazia(t)) {
            t->next->containDir += a;
            
            /* Caso o brinquedo contenha um valor maior ou igual ao
             * proprio, a sequencia eh invalida */
            if (t->next->containDir <= Topo(t))
                return 0;
        }
        
        //Insere o novo valor a pilha
        Push (t, a);
    }
    
    //Caso seja um numero positivo, fecha o brinquedo anterior
    else if (a > 0) {
        /* Se o valor for compativel com o topo da pilha, fecha o brinquedo com
         * sucesso */
        if (!PilhaVazia(t) && Topo(t) == -a)
            Pop(t);
        
        //Invalido
        else return 0;
    }
    
    //Valido
    return 1;
}

//Retorna o endereco de inicializacao da pilha com cabeca
No* IniciaPilha() {
    No *q = (No *)malloc (sizeof (No));
    q->n = 0;
    q->containDir = 0;
    q->next = NULL;
    
    return q;
}

//Libera a memoria ocupada pela pilha
void FreePilha (No *t) {
    while (t != NULL) {
        No *p = t->next;
        free(t);
        t = p;
    }
}

//Insere um novo topo a pilha de valor "a"
void Push (No *t, long int a) {
    No *q = (No *)malloc (sizeof (No));
    q->n = a;
    q->containDir = 0; 
    q->next = t->next;
    
    t->next = q;
}

//Remove o topo da pilha
void Pop (No *t) {
    No *q;
    
    q = t->next;
    t->next = q->next;
    free(q);
}

//Retorna o valor do topo da pilha
long int Topo (No *t) {
    return t->next->n;
}

//Retorna se a lista esta vazia
int PilhaVazia (No *t) {
    return (t->next == NULL);
}