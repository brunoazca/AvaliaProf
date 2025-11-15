#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina_universidade.h"

typedef struct {
    char disciplinaCodigo[50];
    char universidadeCnpj[100];
} tpDisciplinaUniversidadeRel;

static tpDisciplinaUniversidadeRel *relacoes = NULL;
static int qtdRelacoes = 0;
static int disciplina_universidade_forced_return = 0;

static int disciplina_universidade_consume_forced_return(void) {
    if (disciplina_universidade_forced_return != 0) {
        int value = disciplina_universidade_forced_return;
        disciplina_universidade_forced_return = 0;
        return value;
    }
    return 0;
}

void disciplina_universidade_set_forced_return(int valor) {
    disciplina_universidade_forced_return = valor;
}

int link_disciplina_universidade(tpDisciplina *disciplina, tpUniversidade *universidade){
    int forced = disciplina_universidade_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (disciplina == NULL || universidade == NULL ||
        strlen(disciplina->codigo) == 0 || strlen(universidade->cnpj) == 0) {
        return 2;
    }

    tpDisciplina disciplinaEncontrada;
    tpUniversidade universidadeEncontrada;

    if (read_disciplina(disciplina->codigo, &disciplinaEncontrada) != 0) {
        return 1;
    }

    if (read_universidade(universidade->cnpj, &universidadeEncontrada) != 0) {
        return 1;
    }

    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].disciplinaCodigo, disciplina->codigo) == 0) {
            snprintf(relacoes[i].universidadeCnpj, sizeof(relacoes[i].universidadeCnpj), "%s", universidade->cnpj);
            return 0;
        }
    }

    tpDisciplinaUniversidadeRel *novaLista = realloc(relacoes, (qtdRelacoes + 1) * sizeof(tpDisciplinaUniversidadeRel));
    if (novaLista == NULL) {
        return 99;
    }

    relacoes = novaLista;
    snprintf(relacoes[qtdRelacoes].disciplinaCodigo, sizeof(relacoes[qtdRelacoes].disciplinaCodigo), "%s", disciplina->codigo);
    snprintf(relacoes[qtdRelacoes].universidadeCnpj, sizeof(relacoes[qtdRelacoes].universidadeCnpj), "%s", universidade->cnpj);
    qtdRelacoes++;

    return 0;
}

int get_disciplinas_universidade(tpUniversidade *universidade, tpDisciplina **disciplinas, int *quantidade){
    int forced = disciplina_universidade_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (universidade == NULL || disciplinas == NULL || quantidade == NULL || strlen(universidade->cnpj) == 0) {
        return 2;
    }

    int total = 0;
    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].universidadeCnpj, universidade->cnpj) == 0) {
            total++;
        }
    }

    if (total == 0) {
        *disciplinas = NULL;
        *quantidade = 0;
        return 1;
    }

    tpDisciplina *lista = malloc(total * sizeof(tpDisciplina));
    if (lista == NULL) {
        return 99;
    }

    int indice = 0;
    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].universidadeCnpj, universidade->cnpj) == 0) {
            tpDisciplina disciplinaEncontrada;
            if (read_disciplina(relacoes[i].disciplinaCodigo, &disciplinaEncontrada) == 0) {
                lista[indice++] = disciplinaEncontrada;
            }
        }
    }

    if (indice == 0) {
        free(lista);
        *disciplinas = NULL;
        *quantidade = 0;
        return 1;
    }

    *disciplinas = lista;
    *quantidade = indice;
    return 0;
}

void disciplina_universidade_detach_state(void **estado, int *quantidade) {
    if (estado == NULL || quantidade == NULL) {
        return;
    }
    *estado = relacoes;
    *quantidade = qtdRelacoes;
    relacoes = NULL;
    qtdRelacoes = 0;
}

void disciplina_universidade_attach_state(void *estado, int quantidade) {
    if (relacoes != NULL) {
        free(relacoes);
    }
    relacoes = estado;
    qtdRelacoes = quantidade;
}

void disciplina_universidade_free_state(void *estado) {
    free(estado);
}
