#include "disco.h"

#define MAX_OPERACAO 10
#define NUM_BLOCOS 8

//TODO: Nao usar malloc como arquivo = malloc (sizeof (arquivo))...

/* Prototipo de funcoes necessarias para a implementacao da biblioteca */
long int converteTipo(long int valor, char tipo);
char statusBloco(BlocoMem p, long int size);
int fillDisk(BlocoMem diskStatus[], long int size, No *files);
Bool distribuiFiles(BlocoMem diskStatus[], long int size, No *files,
                    Bool *otimizado);
No *findPos (No *files, long int size);

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
    
    /* Converte o tipo de memoria para Kb - distribuido em cada celula */
    size = converteTipo(size, type)/NUM_BLOCOS;
    
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
        
        free (operacao);
    }
    
    /* Preenche os blocos que indicam o estado do disco - 
     * imprime caso a operacao tenha sido realizada com sucesso (1) ou 
     * fracassado (0) */
    if (fillDisk(diskStatus, size, files))
        for (i = 0; i < NUM_BLOCOS; i++)
            printf("[%c]", diskStatus[i].status);
    else
        printf("ERRO: disco cheio");
    
    printf("\n");
    
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
    Bool otimizado = false, canGo = true, success = false;
    No *head = files;
    
    while (canGo && !success) {
        if (otimizado)
            canGo = false;
        
        /* Inicializa os blocos do disco, seguindo o formato padrao */
        for (i = 0; i < NUM_BLOCOS; i++) {
            diskStatus[i].totalMemoria = 0;
            diskStatus[i].memoriaOcupada = 0;
            diskStatus[i].status = ' ';
        }
        
        files = head;
        
        /* Inicializa os valores necessarios para a implementacao 
         * do algoritmo */
        while (files->next != NULL) {
            files->next->sizeNotLocated = files->next->size;
            files = files->next;
        }
        
        /* Realiza a distribuicao dos arquivos nos blocos */
        success = distribuiFiles(diskStatus, size, head, &otimizado);
    }
    
    return success;
}

/* Distribui os arquivos contidos em files nas celulas do disco, retorna se a
 * operacao foi realizada com sucesso ou nao */
Bool distribuiFiles(BlocoMem diskStatus[], long int size, No *files,
    Bool *otimizado) {
    int i = 0;
    No *head = files;

    /* Enquanto ainda houver arquivos ou blocos a percorrer */
    while (i < NUM_BLOCOS && files->next != NULL) {
//      printf("\n file size: %ld | file name: %s | disk size: %ld | disk
//              useful size: %ld | number: %d", files->next->sizeNotLocated,
//              files->next, diskStatus[i].totalMemoria,
//              diskStatus[i].memoriaOcupada, i);
        /* Caso o arquivo caiba no bloco */
        if (diskStatus[i].totalMemoria + files->next->sizeNotLocated <= size) {
            /* Acrescenta memoria do arquivo no bloco */
            diskStatus[i].totalMemoria += files->next->sizeNotLocated;
            
            /* Acrescenta memoria como ativa, caso esta esteja ocupada */
            if (files->next->ocupado == true)
                diskStatus[i].memoriaOcupada += files->next->sizeNotLocated;
            
            /* Caso o bloco tenha sido completamente preenchido,
             * coordena para o proximo bloco */
            if (diskStatus[i].memoriaOcupada == size)
                i++;
            
            /* Coordena para o proximo arquivo */
            files = files->next;
        }
        /* ...ou caso o arquivo nao caiba inteiro no bloco */
        else {
            /* Reparte a memoria ainda nao alocada no disco do arquivo */
            files->next->sizeNotLocated -= size - diskStatus[i].totalMemoria;
            
            /* Acrescenta memoria como ativa, caso esta esteja ocupada:
             * a qual corresponde ao restante necessario para preencher
             * a memoria do bloco */
            if (files->next->ocupado == true)
                diskStatus[i].memoriaOcupada += size -
                diskStatus[i].totalMemoria;
            
            /* Portanto, o bloco esta cheio */
            diskStatus[i].totalMemoria = size;
            
            /* Coordena para o proximo bloco */
            i++;
        }
    }
    
    /* Finalmente, computa o estado de cada bloco do disco */
    for (i = 0; i < NUM_BLOCOS; i++)
        diskStatus[i].status = statusBloco(diskStatus[i], size);
    
    /* Caso todos os arquivos tenham sido alocados, indica sucesso */
    if (files->next == NULL)
        return true;
    
    /* Caso o arquivo nao tenha sido otimizado, os blocos foram todos
     * coordenados e ha arquivos ainda nao alocados, otimiza-os! */
    if (i >= NUM_BLOCOS && files->next != NULL && !(*otimizado)) {
        otimizaFile(head);
        (*otimizado) = true;
        return false;
    }
    
    /* Caso nao tenha alocado todos os arquivos e ja foi feita a tentativa 
     * de otimizar, fracassou */
    return false;
}

/* Retorna um char que indica o estado da porcentagem de bytes livres 
 * no bloco p */
char statusBloco(BlocoMem p, long int size) {
    float bytesLivres;
    
    bytesLivres = (float)(size - p.memoriaOcupada)/size;
    
    /* Relaciona o formato adequado ao bloco */
    if (bytesLivres <= .25)
        return '#';
    else if (bytesLivres <= .75)
        return '-';
    else
        return ' ';
}

/* Insere arquivo no disco */
void insereFile(No *files) {
    No *p;
    char name[11], type;
    long int sizeNo;
    
    scanf("%s %ld%c", name, &sizeNo, &type);
    getchar();
    
    /* Converte o tamanho do arquivo para Kb */
    sizeNo = converteTipo(sizeNo, type);
    
    /* Antes de realizar a insercao, verifica se ja existe um arquivo com o
     * nome solicitado */
    p = findNo(name, files);
    
    /* Caso o nome exista, apenas acrescenta a este arquivo */
    if (p != NULL && p->ocupado) {
        p->size += sizeNo;
        return;
    }

    /* Caso nao exista, cria-se um novo no */
    p = malloc (sizeof (No));
    strcpy(p->name, name);
    p->size = sizeNo;
    p->ocupado = true;
    p->next = NULL;
    
    /* Encontra a posicao mais apropriada para a alocar o no */
    files = findPos (files, sizeNo);
    
    /* Finalmente, adiciona o no para a posicao mais apropriada */
    addNext(files, p);
}

/* Retorna a posicao valida para a alocao de um novo no mais proxima do 
 * inicio do disco */
No *findPos (No *files, long int size) {
    long int sizeLivre = 0;
    Bool found = false;
    No *toEncaixar = NULL;
    
    while (!found && files->next != NULL) {        
        if (files->next->ocupado == false) {
            /* Caso tenha sido o primeiro arquivo desocupado nao-consecutivo
             * encontrado, estabelece-o como possivel local de alocao do no */
            if (sizeLivre == 0)
                toEncaixar = files;
            
            /* Espaco desocupado, sujeito a alocal do no */
            sizeLivre += files->next->size;
        }
        /* Espaco ocupado, reinicia qualquer estudo de espaco desocupado */
        else if (files->next->ocupado == true) {
            sizeLivre = 0;
        }
        
        /* Caso haja espaco livre suficiente para alocar o no e este seja
         * valido */
        if (sizeLivre >= size && toEncaixar != NULL) {
            found = true;
            files = toEncaixar;
            
            /* Enquanto nao estiver no fim da lista e o proximo arquivo for
             * desocupado, remove este espaco para o no ser alocado */
            while (files->next != NULL && files->next->ocupado == false) {
                /* Caso o tamanho nao seja suficiente para o no, avanca para
                 * os proximos rquivos desocupados */
                if (files->next->size <= size) {
                    size -= files->next->size;
                    removeNext(files);
                } 
                /* ...ou caso seja necessario remover apenas parte da memoria
                 * do arquivo desocupado */
                else {
                    files->next->size -= size;
                    
                    /* Finaliza o processo de remocao de memoria */
                    break;
                }
            }
        }
        
        /* Como ainda nao encontrou a posicao apropriada, avanca para o
         * proximo arquivo da lista */
        if (!found)
            files = files->next;
    }
    
    return files;
}

/* Remove um arquivo especifico no disco */
void removeFile(No *t) {
    char nameFile[11];
    No *aux = NULL;
    
    scanf("%s", nameFile);
    
    /* Encontra o arquivo com o nome solicitado */
    aux = findNo(nameFile, t);
     
    /* Caso exista uma arquivo com esse nome, o desocupa */
    if (aux != NULL) {
        strcpy(aux->name, "empty");
        aux->ocupado = false;
    }
}

/* Otimiza o disco */
void otimizaFile(No *t) {
    while (t->next != NULL) {
        /* Caso o arquivo esteja desocupado, o remove */
        if (t->next->ocupado == false) {
            removeNext(t);
        } else
            t = t->next;
    }
}