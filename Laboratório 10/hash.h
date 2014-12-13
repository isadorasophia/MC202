/* Biblioteca responsavel por implementar operacoes de tabela de espalhamento */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* Estrutura de aluno, em lista ligada */
typedef struct Aluno {
    int ra;
    char *nome;
    struct Aluno *next;
} Aluno;

/* Estrutura da tabela de espalhamento */
typedef struct TabelaHash {
    Aluno *aluno;
} TabelaHash;

/* Cria a tabela de espalhamento de tamanho definido */
TabelaHash *CriaTabela();

/* Remove um elemento da tabela - retorna 0 se falhou */
int RemoveTabela(TabelaHash *t, char buf[]);

/* Insere um elemento na tabela, em ordem lexicografica - retorna
 * 0 se falhou */
int InsereTabela(TabelaHash *t, Aluno *a);

/* Caso exista na tabela, retorna informacoes do aluno em *a */
int ConsultaTabela(TabelaHash* t, char *buf, Aluno *a);

/* Imprime a tabela */
void ImprimeTabela(TabelaHash *t);

/* Retorna o numero de alunos na tabela */
int NumeroAlunosTabela(TabelaHash *t);

/* Libera a memoria da tabela */
void LiberaTabela(TabelaHash *t);