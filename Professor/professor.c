#include "professor.h"

tpProfessor *listaProfessores = NULL;
int qtdProfessores = 0;

static int professor_forced_return = 0;

static int professor_consume_forced_return(void) {
    if (professor_forced_return != 0) {
        int value = professor_forced_return;
        professor_forced_return = 0;
        return value;
    }
    return 0;
}

void professor_set_forced_return(int valor) {
    professor_forced_return = valor;
}

void listarProfessores() {
    if(qtdProfessores == 0){
        printf("\nNenhum professor cadastrado ainda.\n\n");
        return;
    }

    printf("\n===== LISTA DE TODOS OS PROFESSORES =====\n");
    for(int i = 0; i < qtdProfessores; i++){
        printf("[%d]\n", i+1);
        printf("  Nome:         %s\n", listaProfessores[i].nome);
        printf("  CPF:          %s\n", listaProfessores[i].cpf);
        printf("  Área:         %s\n", listaProfessores[i].area_de_atuacao);
        printf("-------------------------------------\n");
    }
    printf("\n");
}


int read_professor(char *cpf, tpProfessor *professor) {
    int forced = professor_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (cpf == NULL || professor == NULL || strlen(cpf) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdProfessores; i++) {
        if (strcmp(listaProfessores[i].cpf, cpf) == 0) {
            *professor = listaProfessores[i];
            return 0;
        }
    }
    
    return 1;
}

int delete_professor(char *cpf){
    int forced = professor_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (cpf == NULL || strlen(cpf) == 0) {
        return 2;
    }

    if (qtdProfessores == 0) {
        return 1;
    }

    for (int i = 0; i < qtdProfessores; i++) {
        if (strcmp(listaProfessores[i].cpf, cpf) == 0) {
            for (int j = i; j < qtdProfessores - 1; j++) {
                listaProfessores[j] = listaProfessores[j + 1];
            }
            qtdProfessores--;

            tpProfessor *tmp = realloc(listaProfessores, qtdProfessores * sizeof(tpProfessor));
            if (tmp != NULL || qtdProfessores == 0) {
                listaProfessores = tmp;
            } else {
                return 99;
            }
            listarProfessores();
            return 0;
        }
    }

    return 1;
}

int create_professor(tpProfessor *professor) {
    int forced = professor_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (professor == NULL || strlen(professor->cpf) == 0 || strlen(professor->nome) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdProfessores; i++) {
        if (strcmp(listaProfessores[i].cpf, professor->cpf) == 0) {
            return 1;
        }
    }

    tpProfessor *novaLista = realloc(listaProfessores, (qtdProfessores + 1) * sizeof(tpProfessor));
    if (novaLista == NULL) {
        return 99;
    }

    listaProfessores = novaLista;
    listaProfessores[qtdProfessores] = *professor;
    qtdProfessores++;

    listarProfessores();
    return 0;
}


int update_professor(char *cpf, tpProfessor *professor) {
    int forced = professor_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (cpf == NULL || professor == NULL || strlen(cpf) == 0) {
        return 2;
    }

    for (int i = 0; i < qtdProfessores; i++) {
        if (strcmp(listaProfessores[i].cpf, cpf) == 0) {
            if (strlen(professor->nome) > 0) {
                snprintf(listaProfessores[i].nome, sizeof(listaProfessores[i].nome), "%s", professor->nome);
            }
            if (strlen(professor->area_de_atuacao) > 0) {
                snprintf(listaProfessores[i].area_de_atuacao, sizeof(listaProfessores[i].area_de_atuacao), "%s", professor->area_de_atuacao);
            }
            return 0;
        }
    }

    return 1;
}

void professor_detach_state(tpProfessor **lista, int *quantidade) {
    if (lista == NULL || quantidade == NULL) {
        return;
    }
    *lista = listaProfessores;
    *quantidade = qtdProfessores;
    listaProfessores = NULL;
    qtdProfessores = 0;
}

void professor_attach_state(tpProfessor *lista, int quantidade) {
    if (listaProfessores != NULL) {
        free(listaProfessores);
    }
    listaProfessores = lista;
    qtdProfessores = quantidade;
}

void professor_free_state(tpProfessor *lista) {
    free(lista);
}
