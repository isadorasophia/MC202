#include "lista.h"

typedef enum {
    Kb = 1,
    Mb = 1024,
    Gb = 1024 * 1024
} FileSize;

// Estrutura para a impressao do estado do disco
typedef struct BlocoMem {
    long int totalMemoria;
    long int memoriaOcupada;
    char estado;
} BlocoMem;

// Gerencia operacoes e imprime estado do disco
void gerenciaDisco(int quant);

// Insere arquivo no disco
void insereFile(char[] nome, int tamanho);

// Remove um arquivo especifico no disco
void removeFile(char[] nome);

// Otimiza o disco
void otimizaFile();