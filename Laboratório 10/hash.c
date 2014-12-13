#include "hash.h"

#define TABLESIZE 13

/* Prototipo de funcoes auxiliares para a implementacao da biblioteca */
int hash (char *name);

/* Cria a tabela de espalhamento de tamanho definido */
TabelaHash *CriaTabela() {
    int i;
    TabelaHash *t = malloc(TABLESIZE * sizeof(TabelaHash));
    
    /* Inicializa todos os elementos */
    for (i = 0; i < TABLESIZE; i++)
        t[i].aluno = NULL;
    
    return t;
}

/* Remove um elemento da tabela - retorna 0 se falhou */
int RemoveTabela(TabelaHash *t, char buf[]) {
    int position = hash(buf); /* Posicao segundo a funcao hash */
    Aluno *aluno_aux, *garbage;
    
    aluno_aux = t[position].aluno;

    /* Caso o elemento seja o primeiro no, remove-o */
    if (aluno_aux && strcmp(aluno_aux->nome, buf) == 0) {
        t[position].aluno = aluno_aux->next;
        
        free(aluno_aux);
        
        return 1;
    }
    
    /* Nao sendo o primeiro elemento, continuamos a percorrer a lista */
    while (aluno_aux && aluno_aux->next) {
        /* Elemento encontrado! Remove-o */
        if (strcmp(aluno_aux->next->nome, buf) == 0) {
            garbage = aluno_aux->next;
            
            aluno_aux->next = aluno_aux->next->next;
            
            free(garbage);
            
            return 1;
        }
        
        aluno_aux = aluno_aux->next;
    }
    
    /* Elemento nao encontrado, remocao fracassada */
    return 0;
}

/* Insere um elemento na tabela, em ordem lexicografica - retorna
 * 0 se falhou */
int InsereTabela(TabelaHash *t, Aluno *a) {
    int position = hash(a->nome); /* Posicao segundo a funcao hash */
    Aluno *aluno_aux, *newNode;
    
    /* Cria o novo no */
    newNode = malloc(sizeof(Aluno));
    *newNode = *a;
    newNode->next = NULL;
    
    aluno_aux = t[position].aluno;
    
    /* Caso a lista esteja vazia ou o elemento deve ser inserido no 
     * primeiro no */
    if ((!aluno_aux) || 
        (aluno_aux && strcmp(newNode->nome, aluno_aux->nome) < 0)) {
        t[position].aluno = newNode;
        newNode->next = aluno_aux;
        
        return 1;
    }
    /* Ou o nome ja existe na tabela, insercao fracassada */
    else if (strcmp(newNode->nome, aluno_aux->nome) == 0)
        return 0;
    
    /* Nao sendo o primeiro elemento, continuamos a percorrer a lista */
    while (aluno_aux && aluno_aux->next) {
        /* Encontrou a posicao adequada para a insercao! */
        if (strcmp(newNode->nome, aluno_aux->next->nome) < 0) {
            newNode->next = aluno_aux->next;
            aluno_aux->next = newNode;
            
            return 1;
        } 
        /* Ou o nome ja existe na tabela, insercao fracassada */
        else if (strcmp(newNode->nome, aluno_aux->next->nome) == 0)
            return 0;

        aluno_aux = aluno_aux->next;
    }
    
    /* Como chegou ao fim da lista, apenas insere o elemento */
    if (!aluno_aux->next)
        aluno_aux->next = newNode;
    
    return 1;
}

/* Caso exista na tabela, retorna informacoes do aluno em *a */
int ConsultaTabela(TabelaHash* t, char *buf, Aluno *a) {
    int position = hash(buf); /* Posicao do elemento, segundo a funcao hash */
    Aluno *aluno_aux;
   
    aluno_aux = t[position].aluno;
    
    while (aluno_aux) {
        /* Encontrou! */
        if (strcmp(buf, aluno_aux->nome) == 0) { 
            *a = *aluno_aux;
            return 1;
        }
        
        aluno_aux = aluno_aux->next;
    }
    
    /* Nao foi encontrado */
    return 0;
}

/* Imprime a tabela */
void ImprimeTabela(TabelaHash *t) {
    int i;
    Aluno *aluno_aux;
    
    for (i = 0; i < TABLESIZE; i++) {
        aluno_aux = t[i].aluno;
        
        /* Havendo um aluno, imprime */
        while (aluno_aux) {
            printf("(%d) %d \"%s\"\n", i, aluno_aux->ra, aluno_aux->nome);
            
            aluno_aux = aluno_aux->next;
        }
    }
}

/* Retorna o numero de alunos na tabela */
int NumeroAlunosTabela(TabelaHash t[]) {
    int i, quant = 0;
    Aluno *aluno_aux;
    
    /* Percorre os alunos de todas as posicoes da tabela */
    for (i = 0; i < TABLESIZE; i++) {
        aluno_aux = t[i].aluno;
        
        while (aluno_aux != NULL) {
            quant++;
            aluno_aux = aluno_aux->next;
        }
    }

    return quant;
}

/* Libera a memoria da tabela */
void LiberaTabela(TabelaHash *t) {
    int i;
    Aluno *aluno_aux, *garbage;
    
    /* Para todas as posicoes da tabela, elimina as listas */
    for (i = 0; i < TABLESIZE; i++) {
        aluno_aux = t[i].aluno;
        
        while (aluno_aux) {
            garbage = aluno_aux;
            aluno_aux = aluno_aux->next;
            free(garbage);
        }
    }
    
    free(t);
}

/* A partir do nome, descobre a posicao na tabela pelo metodo
 * de XOR bit a bit */
int hash (char *name) {
    unsigned int XOR_bit; /* Variavel que guarda o resultado do XOR bit a bit */
    int i, size;
    
    /* Tamanho da string */
    size = strlen(name);
    
    XOR_bit = name[0];
    
    for (i = 1; i < size; i++)
        XOR_bit = XOR_bit ^ name[i];
    
    /* Faz operacao de mod para descobrir posicao na tabela Hash */
    XOR_bit = abs(XOR_bit) % TABLESIZE;
    
    return XOR_bit;
}