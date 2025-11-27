#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"
#include "../Aluno_Universidade/aluno_universidade.h"
#include "../Professor_Disciplina/professor_disciplina.h"
#include "../Disciplina_Universidade/disciplina_universidade.h"
#include "../Professor/professor.h"
static tpDisciplina *listaDisciplinas = NULL;
static int qtdDisciplinas = 0;

static void listarDisciplinas(void);
static const char *ARQ_DISCIPLINAS = "Disciplina/dados.json";

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

    tpUniversidade *universidades = NULL;
    tpProfessor *professor =NULL;
            int quantidade = 0;
            int status = get_universidades(&universidades, &quantidade);
            if (status == 0) {
                for (int i = 0; i < quantidade; i++) {
                    if (strcmp(universidades[i].nome, disciplina->universidade) == 0){
                        if(read_professor(disciplina->professor,professor)){
                            link_disciplina_universidade(disciplina,&universidades[i]);
                            link_professor_disciplina(disciplina,professor);
                        }

                        return 0;
                    }
                }
            }

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
        printf("  Universidade:   %s\n", listaDisciplinas[i].universidade);
        printf("  Professor:   %s\n", listaDisciplinas[i].professor);
    }
    printf("================================\n");
}

void disciplina_detach_state(tpDisciplina **lista, int *quantidade) {
    if (lista == NULL || quantidade == NULL) {
        return;
    }
    *lista = listaDisciplinas;
    *quantidade = qtdDisciplinas;
    listaDisciplinas = NULL;
    qtdDisciplinas = 0;
}

void disciplina_attach_state(tpDisciplina *lista, int quantidade) {
    if (listaDisciplinas != NULL) {
        free(listaDisciplinas);
    }
    listaDisciplinas = lista;
    qtdDisciplinas = quantidade;
}

void disciplina_free_state(tpDisciplina *lista) {
    free(lista);
}

void carregarDisciplinas() {
    FILE *fp = fopen(ARQ_DISCIPLINAS, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpDisciplina d;
    int state = 0;
    if (listaDisciplinas) { free(listaDisciplinas); listaDisciplinas = NULL; }
    qtdDisciplinas = 0;
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"codigo\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", d.codigo);
            state = 1;
        } else if(strstr(linha, "\"nome\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", d.nome);
            if (state == 1) {
                listaDisciplinas = realloc(listaDisciplinas, (qtdDisciplinas+1) * sizeof(tpDisciplina));
                listaDisciplinas[qtdDisciplinas++] = d;
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregadas %d disciplinas do arquivo!\n", qtdDisciplinas);
    listarDisciplinas();
}

void salvarDisciplinas() {
    FILE *fp = fopen(ARQ_DISCIPLINAS, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdDisciplinas; i++){
        fprintf(fp,
            "  {\n"
            "    \"codigo\": \"%s\",\n"
            "    \"nome\": \"%s\"\n"
            "  }%s\n",
            listaDisciplinas[i].codigo,
            listaDisciplinas[i].nome,
            (i == qtdDisciplinas-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Disciplina/dados.json <<\n");
}

tpDisciplina create_instancia_disciplina(const char *codigo, const char *nome) {
    tpDisciplina disciplina;
    memset(&disciplina, 0, sizeof(tpDisciplina));
    if (codigo != NULL) {
        snprintf(disciplina.codigo, sizeof(disciplina.codigo), "%s", codigo);
    }
    if (nome != NULL) {
        snprintf(disciplina.nome, sizeof(disciplina.nome), "%s", nome);
    }
    return disciplina;
}

int get_all_disciplinas(tpDisciplina **disciplinas, int *quantidade) {
    if (disciplinas == NULL || quantidade == NULL) {
        return 2;
    }

    if (qtdDisciplinas == 0) {
        *disciplinas = NULL;
        *quantidade = 0;
        return 1;
    }

    tpDisciplina *lista = malloc(qtdDisciplinas * sizeof(tpDisciplina));
    if (lista == NULL) {
        return 99;
    }

    memcpy(lista, listaDisciplinas, qtdDisciplinas * sizeof(tpDisciplina));
    *disciplinas = lista;
    *quantidade = qtdDisciplinas;

    return 0;
}
