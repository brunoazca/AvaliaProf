#ifndef PROFESSOR_H
#define PROFESSOR_H

typedef struct {
    char cpf[100];
    char nome[150];
    char area_de_atuacao[150];
} tpProfessor;

int read_Professor(char *cpf, tpProfessor *professor);
int delete_Professor(char *cpf);
int create_Professor(tpProfessor *professor);
int update_Professors(char *cpf, tpProfessor *professor);

#endif

