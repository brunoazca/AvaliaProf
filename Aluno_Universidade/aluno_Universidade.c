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
static int aluno_universidade_forced_return = 0;

static int aluno_universidade_consume_forced_return(void) {
    if (aluno_universidade_forced_return != 0) {
        int value = aluno_universidade_forced_return;
        aluno_universidade_forced_return = 0;
        return value;
    }
    return 0;
}

void aluno_universidade_set_forced_return(int valor) {
    aluno_universidade_forced_return = valor;
}

int link_aluno_universidade(tpAluno *aluno, tpUniversidade *universidade){
    int forced = aluno_universidade_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
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
    int forced = aluno_universidade_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
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

void aluno_universidade_detach_state(void **estado, int *quantidade) {
    if (estado == NULL || quantidade == NULL) {
        return;
    }
    *estado = relacoes;
    *quantidade = qtdRelacoes;
    relacoes = NULL;
    qtdRelacoes = 0;
}

void aluno_universidade_attach_state(void *estado, int quantidade) {
    if (relacoes != NULL) {
        free(relacoes);
    }
    relacoes = estado;
    qtdRelacoes = quantidade;
}

void aluno_universidade_free_state(void *estado) {
    free(estado);
}
