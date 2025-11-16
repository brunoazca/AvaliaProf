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
static const char *ARQ_REL = "Disciplina_Universidade/dados.json";

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

void carregarDisciplinaUniversidade() {
    FILE *fp = fopen(ARQ_REL, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpDisciplinaUniversidadeRel r;
    int state = 0;
    if (relacoes) { free(relacoes); relacoes = NULL; }
    qtdRelacoes = 0;
    memset(&r, 0, sizeof(r));
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"disciplinaCodigo\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.disciplinaCodigo);
            state = 1;
        } else if(strstr(linha, "\"universidadeCnpj\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.universidadeCnpj);
            if (state == 1) {
                relacoes = realloc(relacoes, (qtdRelacoes+1) * sizeof(tpDisciplinaUniversidadeRel));
                relacoes[qtdRelacoes++] = r;
                memset(&r, 0, sizeof(r));
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregadas %d relações Disciplina-Universidade do arquivo!\n", qtdRelacoes);
    if (qtdRelacoes == 0) {
        printf("Nenhuma relação cadastrada.\n");
    } else {
        printf("===== LISTA DISCIPLINA x UNIVERSIDADE =====\n");
        for (int i = 0; i < qtdRelacoes; i++) {
            printf("[%d] disciplina %s -> universidade %s\n", i + 1, relacoes[i].disciplinaCodigo, relacoes[i].universidadeCnpj);
        }
    }
}

void salvarDisciplinaUniversidade() {
    FILE *fp = fopen(ARQ_REL, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdRelacoes; i++){
        fprintf(fp,
            "  {\n"
            "    \"disciplinaCodigo\": \"%s\",\n"
            "    \"universidadeCnpj\": \"%s\"\n"
            "  }%s\n",
            relacoes[i].disciplinaCodigo,
            relacoes[i].universidadeCnpj,
            (i == qtdRelacoes-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Disciplina_Universidade/dados.json <<\n");
}
