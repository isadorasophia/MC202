#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disco.h"

int main () {
    int N;
    
    scanf("%d", &N);
    
    // Executa enquanto o disco for valido
    while(N) {
        // Realiza as operacoes no disco
        gerenciaDisco(N);

        scanf("%d", &N);
    }

    return 0;
}