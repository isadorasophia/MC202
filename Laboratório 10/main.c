/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB10 - Hash */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "hash.h"

#define TAMMAXNOME 100 /* Tamanho maximo de nome de aluno */

/* Le RA e nome de aluno */
void LeAluno(Aluno *a) {
    char buf[TAMMAXNOME];
    scanf("%d \"%[^\"]\"", &a->ra, buf);
    
    a->nome = malloc(strlen(buf)+1);
    strcpy(a->nome, buf);
    return;
}

/* Le linha de comando */
void lelinha() {
    int c;
    do { c = getchar(); } while (c!='\n');
}

int main(int argc, char *argv[]) {
    
    TabelaHash *t = CriaTabela();
    char comando[100], buf[TAMMAXNOME];
    Aluno a;  
    
    /* Loop para ler entrada */
    while (scanf("%s", comando) > 0) {
        if (strcmp(comando,"insere") == 0) {
            
            LeAluno(&a);
            printf("Insere: %06d \"%s\"\n", a.ra, a.nome);
            
            /* Insere aluno 'a' na tabela 't' */
            if (!InsereTabela(t, &a)) {
                printf("Nome repetido: \"%s\"\n", a.nome);
                free(a.nome);
            }
            
        } else if (strcmp(comando, "remove") == 0) { 
            scanf(" \"%[^\"]\"", buf);
            printf("Remove: \"%s\"\n", buf);
            
            /* Remove aluno de nome 'buf' da tabela 't' */
            if (!RemoveTabela(t, buf))
                printf("Nome inexistente: \"%s\"\n", buf);
    
        } else if ( strcmp(comando, "consulta") == 0 ) {
            scanf(" \"%[^\"]\"", buf);
            printf("Consulta: \"%s\"\n", buf);
            /* Consulta aluno de nome 'buf' na tabela 't', grava
             * dados em 'a', retorna 0 se nao encontrou aluno */
            if (ConsultaTabela(t, buf, &a))
                printf("%06d \"%s\"\n", a.ra, a.nome);
            else
                printf("Nome inexistente: \"%s\"\n", buf);
            
        } else if ( strcmp(comando, "imprime") == 0 ) {
            /*Calcula numero de alunos na tabela 't'*/
            printf("\nImprime Tabela: %d aluno(s):\n", NumeroAlunosTabela(t));
            
            ImprimeTabela(t);
            printf("\n");
            
        } else if ( strcmp(comando, "sair") == 0 ) { 
            /* Termina programa */
            break;
            
        } else {
            printf("Comando desconhecido: `%sŽ\n", comando);
            
        }
    }

    LiberaTabela(t); /* Libera memoria */

    return 0;
}