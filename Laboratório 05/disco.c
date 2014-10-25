#include "disco.h"

#define MAX_OPERACAO 10
#define NUM_BLOCOS 8

//TODO: Nao usar malloc como arquivo = malloc (sizeof (arquivo))...

/* Prototipo de funcoes necessarias para a implementacao da biblioteca */
long int converteTipo(long int valor, char tipo);
int fillDisk(BlocoMem diskStatus[], long int size, No *files);
char statusBloco(BlocoMem p);

/* Gerencia operacoes e imprime estado do disco */
void gerenciaDisco(int quant) {
    int i;
    long int size;
    char type, *operacao;
    No *files;
    BlocoMem diskStatus[NUM_BLOCOS];
    
    /* Recebe o tamanho do disco */
    scanf("%ld%c", &size, &type);
    getchar();
    
    /* Converte o tipo de memoria para Kb */
    size = converteTipo(size, type);
    
//     printf("!!%ld", size);
    
    /* Inicializa a lista (com cabeca) de arquivos */
    files = malloc(sizeof (No));
    files->next = NULL;
    
    /* Realiza a leitura dos comandos */
    while (quant--) {        
        operacao = malloc (MAX_OPERACAO * sizeof(char));
        
        /* Realiza a operacao conforme a entrada recebida */
        scanf("%s", operacao);
        
        if (strcmp(operacao, "insere") == 0)
            insereFile(files);
            
        else if (strcmp(operacao, "remove") == 0)
            removeFile(files);
                
        else if (strcmp(operacao, "otimiza") == 0)
            otimizaFile(files);
        
        if (files->next == NULL)
            printf("oi");
        
//         printf("*%s*", operacao);
        
        free (operacao);
    }
    
    /* Preenche os blocos que indicam o estado do disco */
    if (fillDisk(diskStatus, size, files)) {
        /* Imprime caso a operacao tenha sido realizada com sucesso */
        for (i = 0; i < NUM_BLOCOS; i++)
            printf("[%c]", diskStatus[i].status);
    } else
        printf("ERRO: disco cheio");
    
    freeList(files);
}

/* Retorna o valor em Kb a partir de seu tipo */
long int converteTipo(long int valor, char tipo) {
    FileSize fatorCorrecao = Kb;
    
    switch (tipo) {
        case 'K':
            fatorCorrecao = Kb;
            break;
        case 'M':
            fatorCorrecao = Mb;
            break;
        case 'G':
            fatorCorrecao = Gb;
            break;
    }
    
    return valor * fatorCorrecao;
}

/* Preenche o disco: retorna 1 caso tenha sido realizado com sucesso, 0 caso
 * contrario */
int fillDisk(BlocoMem diskStatus[], long int size, No *files) {
    int i;
    long int sizeIndiv = size/NUM_BLOCOS;
    float bytesLivres;
    
    /* Inicia os blocos do disco, seguindo o formato padrao */
    for (i = 0; i < NUM_BLOCOS; i++) {
        diskStatus[i].totalMemoria = 0;
        diskStatus[i].memoriaOcupada = 0;
        diskStatus[i].status = ' ';
    }
    
    i = 0;
    
    /* Preenche os arquivos no disco */
    while (i < NUM_BLOCOS && files->next != NULL) {
        /* Caso o arquivo caiba no bloco */
        if (diskStatus[i].totalMemoria + files->next->size <= sizeIndiv) {
            diskStatus[i].totalMemoria += files->next->size;
            
            /* Acrescenta memoria, caso esta esteja ocupada */
            if (files->next->ocupado == true) {
                diskStatus[i].memoriaOcupada += files->next->size;
            }
            
            /* Caso o bloco tenha sido completamente preenchido */
            if (diskStatus[i].memoriaOcupada == sizeIndiv)
                diskStatus[i].status = statusBloco(diskStatus[i]);
            
            /* Coordena para o proximo arquivo */
            files = files->next;
        }
        /* Caso o arquivo nao caiba inteiro no bloco */
        else {
            /* Restante de memoria ainda nao alocada do arquivo */
            files->next->size -= sizeIndiv - diskStatus[i].totalMemoria;
            
            /* Acrescenta memoria, caso esta esteja ocupada */
            if (files->next->ocupado == true)
                /* O tamanho alocado corresponde ao restante para 
                 * preencher a memoria total do bloco */
                diskStatus[i].memoriaOcupada += sizeIndiv -
                diskStatus[i].totalMemoria;
            
            /* Bloco cheio */
            diskStatus[i].totalMemoria = sizeIndiv;
           
            /* Como o bloco esta cheio, atualiza seu status */
            diskStatus[i].status = statusBloco(diskStatus[i]);
            
            /* Coordena para o proximo bloco */
            i++;
        }
    }
    
    /* Caso o tamanho do disco tenha sido insuficiente para o armazenamento dos
     * arquivos */
    if (i >= NUM_BLOCOS)
        return 0;
    
    else
        return 1;
}

// Retorna um char que indica o estado da porcentagem de bytes livres no bloco p
char statusBloco(BlocoMem p) {
    float bytesLivres;
    
    bytesLivres = (float)(p.totalMemoria - p.memoriaOcupada)/p.totalMemoria;

    /* Relaciona o formato adequado ao bloco */
    if (bytesLivres <= .25)
        return '#';
    else if (bytesLivres <= .75)
        return '-';
    else
        return ' ';
}

/* Insere arquivo no disco */
void insereFile(No *t) {
    No *p;
    char type;
    
    p = malloc (sizeof (No));
    p->ocupado = true;
    p->next = NULL;
    
    scanf("%s %ld%c", p->name, &(p->size), &type);
    getchar();
    
    p->size = converteTipo(p->size, type);
    
    addNo(t, p);
}

/* Remove um arquivo especifico no disco */
void removeFile(No *t) {
    char nameFile[11];
    No *aux = NULL;
    
    scanf("%s", nameFile);
    
    aux = findNo(nameFile, t);
     
    /* Caso exista uma arquivo com esse nome, o desocupa */
    if (aux != NULL)
        aux->ocupado = false;
}

/* Otimiza o disco */
void otimizaFile(No *t) {
    while (t->next != NULL) {
        if (t->next->ocupado == false)
            removeFile(t);
        else
            t = t->next;
    }
}