#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "universidade.h"

tpUniversidade *listaUniversidades = NULL;
int qtdUniversidades = 0;

static void listarUniversidades(void);

int read_universidade(char *cnpj, tpUniversidade *universidade) {
    if (cnpj == NULL || universidade == NULL || strlen(cnpj) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdUniversidades; i++) {
        if (strcmp(listaUniversidades[i].cnpj, cnpj) == 0) {
            *universidade = listaUniversidades[i];
            return 0;
        }
    }

    return 1;
}

int delete_universidade(char *cnpj){
    if (cnpj == NULL || strlen(cnpj) == 0) {
        return 2;
    }

    if (qtdUniversidades == 0) {
        return 1;
    }

    for (int i = 0; i < qtdUniversidades; i++) {
        if (strcmp(listaUniversidades[i].cnpj, cnpj) == 0) {
            for (int j = i; j < qtdUniversidades - 1; j++) {
                listaUniversidades[j] = listaUniversidades[j + 1];
            }
            qtdUniversidades--;

            if (qtdUniversidades > 0) {
                tpUniversidade *tmp = realloc(listaUniversidades, qtdUniversidades * sizeof(tpUniversidade));
                if (tmp == NULL) {
                    qtdUniversidades++;
                    return 99;
                }
                listaUniversidades = tmp;
            } else {
                free(listaUniversidades);
                listaUniversidades = NULL;
            }
            listarUniversidades();
            return 0;
        }
    }

    return 1;
}

int create_universidade(tpUniversidade *universidade) {
    if (universidade == NULL ||
        strlen(universidade->cnpj) == 0 ||
        strlen(universidade->nome) == 0 ||
        strlen(universidade->descricao) == 0) {
        return 2;
    }

    tpUniversidade universidadeEncontrada;
    if (read_universidade(universidade->cnpj, &universidadeEncontrada) == 0) {
        return 1;
    }

    tpUniversidade *novaLista = realloc(listaUniversidades, (qtdUniversidades + 1) * sizeof(tpUniversidade));
    if (novaLista == NULL) {
        return 99;
    }

    listaUniversidades = novaLista;
    listaUniversidades[qtdUniversidades] = *universidade;
    qtdUniversidades++;
    listarUniversidades();

    return 0;
}

int get_universidades(tpUniversidade **universidades, int *quantidade) {
    if (universidades == NULL || quantidade == NULL) {
        return 2;
    }

    if (qtdUniversidades == 0) {
        *universidades = NULL;
        *quantidade = 0;
        return 1;
    }

    tpUniversidade *lista = malloc(qtdUniversidades * sizeof(tpUniversidade));
    if (lista == NULL) {
        return 99;
    }

    memcpy(lista, listaUniversidades, qtdUniversidades * sizeof(tpUniversidade));
    *universidades = lista;
    *quantidade = qtdUniversidades;

    return 0;
}

static void listarUniversidades(void) {
    if (qtdUniversidades == 0) {
        printf("\nNenhuma universidade cadastrada.\n");
        return;
    }

    printf("\n===== LISTA DE UNIVERSIDADES =====\n");
    for (int i = 0; i < qtdUniversidades; i++) {
        printf("[%d]\n", i + 1);
        printf("  Nome: %s\n", listaUniversidades[i].nome);
        printf("  CNPJ: %s\n", listaUniversidades[i].cnpj);
        printf("  Descrição: %s\n", listaUniversidades[i].descricao);
        printf("----------------------------------\n");
    }
}