#include "lista.h"

//Retorna o endereco de uma lista (com cabeca) de N nos
No *createList (int N) {
    No *no;
    
    //Aloca a cabeca da lista
    no = malloc (sizeof (No));
    
    //Adiciona os N elementos a lista ligada
    addNo(no, 1, N);
    
    //Retorna o endereco da cabeca da lista
    return no;
}

//Adiciona os N nos a lista - de n a N
void addNo (No *no, int n, int N) {
    //Finaliza a funcao caso ja tenha sido adicionado os N nos
    if (n > N) {
        no->next = NULL;
        return;
    }
    
    //Cria o no
    No *head;
    head = malloc (sizeof (No));
    head->n = n;
    head->freq = 0;
    
    //Adiciona o no a lista
    no->next = head;
    
    addNo(no->next, n + 1, N);
}

//Desaloca a memoria ocupada pela lista
void removeLista (No *no) {
    if (no->next == NULL) {
        free(no);
        return;
    }
    
    removeLista (no->next);
    free(no);
}

//Aplica o algoritmo MTF
void MTF (No *fichario, int *req, int R, int N) {
    int *custo, i;
    No *found;

    custo = malloc (sizeof (int));
    (*custo) = 0;
    
    for (i = 0; i < R; i++) {
        //Encontra o no anterior ao arquivo desejado
        found = findReq(req[i], custo, fichario);
        
        //Caso o arquivo tenha sido encontrado e nao seja o primeiro elemento,
        //este é movido para o inicio da lista
        if (found != NULL && found != fichario) {
            //Insere o arquivo ao inicio da lista
            insertAfter(req[i], 0, fichario);
            //Elimina a antiga posicao do arquivo
            deleteNext(found);
        }
    }
    
    printf("%d ", *custo);

    free(custo);
   
    //Reinicia valores da lista ligada
    removeLista(fichario);
    fichario = createList(N);
}

//Aplica o algoritmo TR
void TR (No *fichario, int *req, int R, int N) {
    int *custo, i;
    No *found;
    
    custo = malloc (sizeof (int));
    (*custo) = 0;
    
    for (i = 0; i < R; i++) {
        //Encontra o no anterior ao arquivo desejado
        found = findReq(req[i], custo, fichario);
        
        //Caso o arquivo tenha sido encontrado e nao seja o primeiro elemento,
        //este é transposto com o arquivo anterior
        if (found != NULL && found != fichario) {
            (*custo)++;
            swapValues(found);
        }
    }
    
    printf("%d ", *custo);
    
    free(custo);
    
    //Reinicia valores da lista ligada
    removeLista(fichario);
    fichario = createList(N);
}

//Aplica o algoritmo FC
void FC (No *fichario, int *req, int R, int N) {
    int *custo, i;
    No *found;
    
    custo = malloc (sizeof (int));
    (*custo) = 0;
    
    for (i = 0; i < R; i++) {
        //Encontra o no anterior ao arquivo desejado
        found = findReq(req[i], custo, fichario);
       
        if (found != NULL) {
            found->next->freq++;
            
            //Caso o arquivo nao seja o primeiro elemento, este é ordenado
            //de acordo com as frequencias da lista
            if (found != fichario)
                ordenaFreq(fichario, found);
        }
    }
    
    printf("%d\n", *custo);
    
    free(custo);
}

//Retorna o no anterior ao arquivo com a informacao n, ou NULL caso ele nao
//exista
No *findReq(int n, int *custo, No *p) {
    //Fim da lista, arquivo nao encontrado
    if (p->next == NULL) {
        return NULL;
    }
    
    //Arquivo encontrado
    if (p->next->n == n) {
        (*custo)++;
        return p;
    }
    
    (*custo)++;
    return findReq(n, custo, p->next);
}

//Deleta o no apos *p
void deleteNext (No *p) {
    No *q;
    
    q = p->next;
    p->next = q->next;
    
    free(q);
}
    
//Insere um no com as informacoes n e freq apos *p
void insertAfter (int n, int freq, No *p) {
    No *q;
    
    //Cria o no
    q = malloc (sizeof (No));
    q->n = n;
    q->freq = freq;
    
    q->next = p->next;
    p->next = q;
}

//Troca o valor do no atual com o proximo e vice-versa
void swapValues (No *no) {
    int aux;
   
    aux = no->n;
    no->n = no->next->n;
    no->next->n = aux;
}

//Organiza a lista por ordem decrescente de frequencia
void ordenaFreq (No *head, No *found) {
    if (head->next == NULL || found->next == NULL) {
        return;
    }
    
    if (head->next->freq <= found->next->freq) {
        insertAfter(found->next->n, found->next->freq, head);
        deleteNext(found);
        return;
    }
    
    ordenaFreq(head->next, found);
}