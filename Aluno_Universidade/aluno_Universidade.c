#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno_universidade.h"

typedef struct {
    char alunoCpf[100];
    char universidadeCnpj[100];
} tpAlunoUniversidadeRel;

static tpAlunoUniversidadeRel *relacoes = NULL;
static int qtdRelacoes = 0;

int link_aluno_universidade(tpAluno *aluno, tpUniversidade *universidade){
    if (aluno == NULL || universidade == NULL ||
        strlen(aluno->cpf) == 0 || strlen(universidade->cnpj) == 0) {
        return 2;
    }

    tpAluno alunoEncontrado;
    tpUniversidade universidadeEncontrada;

    if (read_aluno(aluno->cpf, &alunoEncontrado) != 0) {
        return 1;
    }

    if (read_universidade(universidade->cnpj, &universidadeEncontrada) != 0) {
        return 1;
    }

    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].alunoCpf, aluno->cpf) == 0) {
            snprintf(relacoes[i].universidadeCnpj, sizeof(relacoes[i].universidadeCnpj), "%s", universidade->cnpj);
            return 0;
        }
    }

    tpAlunoUniversidadeRel *novaLista = realloc(relacoes, (qtdRelacoes + 1) * sizeof(tpAlunoUniversidadeRel));
    if (novaLista == NULL) {
        return 99;
    }

    relacoes = novaLista;
    snprintf(relacoes[qtdRelacoes].alunoCpf, sizeof(relacoes[qtdRelacoes].alunoCpf), "%s", aluno->cpf);
    snprintf(relacoes[qtdRelacoes].universidadeCnpj, sizeof(relacoes[qtdRelacoes].universidadeCnpj), "%s", universidade->cnpj);
    qtdRelacoes++;

    return 0;
}

int get_universidade_aluno(tpAluno *aluno, tpUniversidade *universidade){
    if (aluno == NULL || universidade == NULL || strlen(aluno->cpf) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].alunoCpf, aluno->cpf) == 0) {
            return read_universidade(relacoes[i].universidadeCnpj, universidade);
        }
    }

    return 1;
}
