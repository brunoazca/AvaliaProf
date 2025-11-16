#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor_disciplina.h"


static tpProfessorDisciplinaRel *relacoes = NULL;
static int qtdRelacoes = 0;
static int professor_disciplina_forced_return = 0;
static const char *ARQ_REL_PD = "Professor_Disciplina/dados.json";

static int professor_disciplina_consume_forced_return(void) {
    if (professor_disciplina_forced_return != 0) {
        int value = professor_disciplina_forced_return;
        professor_disciplina_forced_return = 0;
        return value;
    }
    return 0;
}

void professor_disciplina_set_forced_return(int valor) {
    professor_disciplina_forced_return = valor;
}

int link_professor_disciplina(tpDisciplina *disciplina, tpProfessor *professor){
    int forced = professor_disciplina_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
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
    int forced = professor_disciplina_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
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

void professor_disciplina_detach_state(tpProfessorDisciplinaRel **estado, int *quantidade) {
    if (estado == NULL || quantidade == NULL) {
        return;
    }
    *estado = relacoes;
    *quantidade = qtdRelacoes;
    relacoes = NULL;
    qtdRelacoes = 0;
}

void professor_disciplina_attach_state(tpProfessorDisciplinaRel *estado, int quantidade) {
    if (relacoes != NULL) {
        free(relacoes);
    }
    relacoes = estado;
    qtdRelacoes = quantidade;
}

void professor_disciplina_free_state(tpProfessorDisciplinaRel *estado) {
    free(estado);
}

void carregarProfessorDisciplina() {
    FILE *fp = fopen(ARQ_REL_PD, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpProfessorDisciplinaRel r;
    int state = 0;
    if (relacoes) { free(relacoes); relacoes = NULL; }
    qtdRelacoes = 0;
    memset(&r, 0, sizeof(r));
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"disciplinaCodigo\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.disciplinaCodigo);
            state = 1;
        } else if(strstr(linha, "\"professorCpf\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", r.professorCpf);
            if (state == 1) {
                relacoes = realloc(relacoes, (qtdRelacoes+1) * sizeof(tpProfessorDisciplinaRel));
                relacoes[qtdRelacoes++] = r;
                memset(&r, 0, sizeof(r));
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregadas %d relações Professor-Disciplina do arquivo!\n", qtdRelacoes);
    if (qtdRelacoes == 0) {
        printf("Nenhuma relação cadastrada.\n");
    } else {
        printf("===== LISTA PROFESSOR x DISCIPLINA =====\n");
        for (int i = 0; i < qtdRelacoes; i++) {
            printf("[%d] disciplina %s -> professor %s\n", i + 1, relacoes[i].disciplinaCodigo, relacoes[i].professorCpf);
        }
    }
}

void salvarProfessorDisciplina() {
    FILE *fp = fopen(ARQ_REL_PD, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdRelacoes; i++){
        fprintf(fp,
            "  {\n"
            "    \"disciplinaCodigo\": \"%s\",\n"
            "    \"professorCpf\": \"%s\"\n"
            "  }%s\n",
            relacoes[i].disciplinaCodigo,
            relacoes[i].professorCpf,
            (i == qtdRelacoes-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Professor_Disciplina/dados.json <<\n");
}
