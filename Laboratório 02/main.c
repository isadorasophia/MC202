/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB02 */

#include "matrioshka.h"

int main () {
    int n;

    scanf("%d", &n);

    while (n) {
        AnalisaSequencia(n) ?
            printf(":-) Matrioshka!\n") :
            printf(":-( Tente novamente.\n");
        scanf("%d", &n);
    }

    return 0;
}