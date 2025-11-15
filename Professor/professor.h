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


int read_professor(char *cpf, tpProfessor *professor);
int delete_professor(char *cpf);
int create_professor(tpProfessor *professor);
int update_professor(char *cpf, tpProfessor *professor);

void professor_detach_state(tpProfessor **lista, int *quantidade);
void professor_attach_state(tpProfessor *lista, int quantidade);
void professor_free_state(tpProfessor *lista);
void professor_set_forced_return(int valor);

#endif

