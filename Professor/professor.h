#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cpf[100];
    char nome[150];
    char area_de_atuacao[150];
} tpProfessor;

// variável global (será definida em aluno.c)
extern tpProfessor tipoProfessor;

extern tpProfessor *listaProfessores;

// quantidade atual
extern int qtdProfessores;


int read_Professor(char *cpf, tpProfessor *professor);
int delete_Professor(char *cpf);
int create_Professor(tpProfessor *professor);
int update_Professors(char *cpf, tpProfessor *professor);

#endif

