#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "universidade.h"

tpUniversidade *listaUniversidades = NULL;
int qtdUniversidades = 0;

static void listarUniversidades(void);
static const char *ARQ_UNIVERSIDADES = "Universidade/dados.json";

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

void universidade_detach_state(tpUniversidade **lista, int *quantidade) {
    if (lista == NULL || quantidade == NULL) {
        return;
    }
    *lista = listaUniversidades;
    *quantidade = qtdUniversidades;
    listaUniversidades = NULL;
    qtdUniversidades = 0;
}

void universidade_attach_state(tpUniversidade *lista, int quantidade) {
    if (listaUniversidades != NULL) {
        free(listaUniversidades);
    }
    listaUniversidades = lista;
    qtdUniversidades = quantidade;
}

void universidade_free_state(tpUniversidade *lista) {
    free(lista);
}

void carregarUniversidades() {
    FILE *fp = fopen(ARQ_UNIVERSIDADES, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpUniversidade u;
    int state = 0;
    if (listaUniversidades) { free(listaUniversidades); listaUniversidades = NULL; }
    qtdUniversidades = 0;
    memset(&u, 0, sizeof(tpUniversidade));
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"cnpj\"")){
            memset(&u, 0, sizeof(tpUniversidade));
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", u.cnpj);
            state = 1;
        } else if(strstr(linha, "\"nome\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", u.nome);
        } else if(strstr(linha, "\"descricao\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", u.descricao);
            if (state == 1) {
                listaUniversidades = realloc(listaUniversidades, (qtdUniversidades+1) * sizeof(tpUniversidade));
                listaUniversidades[qtdUniversidades++] = u;
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregadas %d universidades do arquivo!\n", qtdUniversidades);
    listarUniversidades();
}

void salvarUniversidades() {
    FILE *fp = fopen(ARQ_UNIVERSIDADES, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdUniversidades; i++){
        fprintf(fp,
            "  {\n"
            "    \"cnpj\": \"%s\",\n"
            "    \"nome\": \"%s\",\n"
            "    \"descricao\": \"%s\"\n"
            "  }%s\n",
            listaUniversidades[i].cnpj,
            listaUniversidades[i].nome,
            listaUniversidades[i].descricao,
            (i == qtdUniversidades-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Universidade/dados.json <<\n");
}

tpUniversidade create_instancia_universidade(const char *cnpj, const char *nome) {
    tpUniversidade universidade;
    memset(&universidade, 0, sizeof(tpUniversidade));
    if (cnpj != NULL) {
        snprintf(universidade.cnpj, sizeof(universidade.cnpj), "%s", cnpj);
    }
    if (nome != NULL) {
        snprintf(universidade.nome, sizeof(universidade.nome), "%s", nome);
    }
    snprintf(universidade.descricao, sizeof(universidade.descricao), "%s", "Descrição de teste");
    return universidade;
}