#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tpAluno {
    char *cpf;
    char *nome;
    char *email;
    char *senha;
    char *curso;
    char *universidade;
} tpAluno;

typedef struct tpUniversidade {
    char *cnpj;
    char *nome;
    char *descrição;
} tpUniversidade; 

int link(tpAluno *tpAluno, tpUniversidade *tpUniversidade){
    return 0;
}

int get_aluno_universidade(tpAluno **tpAluno, tpUniversidade *tpUniversidade){
    return 0;
}
