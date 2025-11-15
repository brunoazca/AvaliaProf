#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor_disciplina.h"


static tpProfessorDisciplinaRel *relacoes = NULL;
static int qtdRelacoes = 0;

int link_professor_disciplina(tpDisciplina *disciplina, tpProfessor *professor){
    if (disciplina == NULL || professor == NULL ||
        strlen(disciplina->codigo) == 0 || strlen(professor->cpf) == 0) {
        return 2;
    }

    tpDisciplina disciplinaEncontrada;
    tpProfessor professorEncontrado;

    if (read_disciplina(disciplina->codigo, &disciplinaEncontrada) != 0) {
        return 1;
    }

    if (read_professor(professor->cpf, &professorEncontrado) != 0) {
        return 1;
    }

    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].disciplinaCodigo, disciplina->codigo) == 0 &&
            strcmp(relacoes[i].professorCpf, professor->cpf) == 0) {
            return 0;
        }
    }

    tpProfessorDisciplinaRel *novaLista = realloc(relacoes, (qtdRelacoes + 1) * sizeof(tpProfessorDisciplinaRel));
    if (novaLista == NULL) {
        return 99;
    }

    relacoes = novaLista;
    snprintf(relacoes[qtdRelacoes].disciplinaCodigo, sizeof(relacoes[qtdRelacoes].disciplinaCodigo), "%s", disciplina->codigo);
    snprintf(relacoes[qtdRelacoes].professorCpf, sizeof(relacoes[qtdRelacoes].professorCpf), "%s", professor->cpf);
    qtdRelacoes++;

    return 0;
}

int get_professores_disciplina(tpDisciplina *disciplina, tpProfessor **professores, int *quantidade){
    if (disciplina == NULL || professores == NULL || quantidade == NULL || strlen(disciplina->codigo) == 0) {
        return 2;
    }

    int total = 0;
    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].disciplinaCodigo, disciplina->codigo) == 0) {
            total++;
        }
    }

    if (total == 0) {
        *professores = NULL;
        *quantidade = 0;
        return 1;
    }

    tpProfessor *lista = malloc(total * sizeof(tpProfessor));
    if (lista == NULL) {
        return 99;
    }

    int indice = 0;
    for (int i = 0; i < qtdRelacoes; i++) {
        if (strcmp(relacoes[i].disciplinaCodigo, disciplina->codigo) == 0) {
            tpProfessor professorEncontrado;
            if (read_professor(relacoes[i].professorCpf, &professorEncontrado) == 0) {
                lista[indice++] = professorEncontrado;
            }
        }
    }

    if (indice == 0) {
        free(lista);
        *professores = NULL;
        *quantidade = 0;
        return 1;
    }

    *professores = lista;
    *quantidade = indice;
    return 0;
}
