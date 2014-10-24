#include "fila.h"

//Funcoes auxiliares para ldaAlgorithm
int VerificaDissipador (int i, int j, int H, int W, Celula **mapa);
void EncontraPrioridade (FilaOrdenada filaOrdenada[], 
                         Celula **mapa, int H, int W);
void EncontraVizinhos(Celula n, int H, int W, 
                      FilaOrdenada filaOrdenada[], Celula **mapa);

// Atribui os rotulos de cada celula seguindo o algoritmo
void ldaAlgorithm (int H, int W, Celula **mapa);