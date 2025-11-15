#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"

tpDisciplina *listaDisciplinas = NULL;
int qtdDisciplinas = 0;

static void listarDisciplinas(void);

int read_disciplina(char *codigo, tpDisciplina *disciplina) {
    if (codigo == NULL || disciplina == NULL || strlen(codigo) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].codigo, codigo) == 0) {
            *disciplina = listaDisciplinas[i];
            return 0;
        }
    }

    return 1;
}

int delete_disciplina(char *codigo) {
    if (codigo == NULL || strlen(codigo) == 0) {
        return 2;
    }

    if (qtdDisciplinas == 0) {
        return 1;
    }

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].codigo, codigo) == 0) {
            for (int j = i; j < qtdDisciplinas - 1; j++) {
                listaDisciplinas[j] = listaDisciplinas[j + 1];
            }
            qtdDisciplinas--;

            tpDisciplina *tmp = realloc(listaDisciplinas, qtdDisciplinas * sizeof(tpDisciplina));
            if (tmp != NULL || qtdDisciplinas == 0) {
                listaDisciplinas = tmp;
            } else {
                return 99;
            }
            listarDisciplinas();
            return 0;
        }
    }

    return 1;
}

int create_disciplina(tpDisciplina *disciplina) {
    if (disciplina == NULL || strlen(disciplina->codigo) == 0 || strlen(disciplina->nome) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].codigo, disciplina->codigo) == 0) {
            return 1;
        }
    }

    tpDisciplina *novaLista = realloc(listaDisciplinas, (qtdDisciplinas + 1) * sizeof(tpDisciplina));
    if (novaLista == NULL) {
        return 99;
    }

    listaDisciplinas = novaLista;
    listaDisciplinas[qtdDisciplinas] = *disciplina;
    qtdDisciplinas++;

    listarDisciplinas();
    return 0;
}

int update_disciplina(char *codigo, tpDisciplina *disciplina) {
    if (codigo == NULL || disciplina == NULL || strlen(codigo) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].codigo, codigo) == 0) {
            if (strlen(disciplina->nome) > 0) {
                snprintf(listaDisciplinas[i].nome, sizeof(listaDisciplinas[i].nome), "%s", disciplina->nome);
            }
            return 0;
        }
    }

    return 1;
}

static void listarDisciplinas(void) {
    if (qtdDisciplinas == 0) {
        printf("\nNenhuma disciplina cadastrada.\n");
        return;
    }

    printf("\n===== LISTA DE DISCIPLINAS =====\n");
    for (int i = 0; i < qtdDisciplinas; i++) {
        printf("[%d]\n", i + 1);
        printf("  Código: %s\n", listaDisciplinas[i].codigo);
        printf("  Nome:   %s\n", listaDisciplinas[i].nome);
    }
    printf("================================\n");
}
