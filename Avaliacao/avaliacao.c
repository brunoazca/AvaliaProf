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

typedef struct tpProfessor {
    char *cpf;
    char *nome;
    char *area_de_Atuacao;
} tpProfessor; 

typedef struct tpAvaliacao {
    char *id;
    char *nota;
    char *comentario;
    char *timestamp;
} tpAvaliacao; 


int create_Avaliacao(tpAluno *tpAluno ,tpProfessor *tpProfessor,tpAvaliacao *tpAvaliacao) {
    return 0;
}

int get_Avaliacoes_Professor(tpProfessor *tpProfessor,tpAvaliacao **tpAvaliacao) {
    return 0;
}
