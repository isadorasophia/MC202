/* Biblioteca responsavel por implementar funcoes para gerenciamento de disco */

#include "lista.h"

typedef enum {
    Kb = 1,
    Mb = 1024,
    Gb = 1024 * 1024
} FileSize;

/* Estrutura para a impressao do estado do disco */
typedef struct BlocoMem {
    long int totalMemoria;
    long int memoriaOcupada;
    char status;
} BlocoMem;

/* Gerencia operacoes e imprime estado do disco */
void gerenciaDisco(int quant);

/* Insere arquivo no disco */
void insereFile(No *t);

/* Remove um arquivo especifico no disco */
void removeFile(No *t);

/* Otimiza o disco */
void otimizaFile(No *t);