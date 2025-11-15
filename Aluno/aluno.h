#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tpAluno {
    char cpf[100];
    char nome[100];
    char email[100];
    char senha[100];
    char curso[100];
    char universidade[100];
} tpAluno;


// variável global (será definida em aluno.c)
extern tpAluno tipoAluno;

extern tpAluno *listaAlunos;
// quantidade atual
extern int qtdAlunos;

// só declara as funções (não implementa aqui)
int read_aluno(char *cpf, tpAluno *aluno);
int delete_aluno(char *cpf);
int registrar(tpAluno *aluno);
int login(char *email, char *senha);
void salvarJSON();
void carregarAlunos();
#endif
