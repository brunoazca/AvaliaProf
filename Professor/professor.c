#include "professor.h"

static tpProfessor *listaProfessores = NULL;
static int qtdProfessores = 0;

static const char *ARQ_PROFESSORES = "Professor/dados.json";

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

void carregarProfessores() {
    FILE *fp = fopen(ARQ_PROFESSORES, "r");
    if(!fp){
        return;
    }
    char linha[512];
    tpProfessor p;
    int state = 0;
    qtdProfessores = 0;
    if (listaProfessores) { free(listaProfessores); listaProfessores = NULL; }
    while(fgets(linha, sizeof(linha), fp)){
        if(strstr(linha, "\"cpf\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", p.cpf);
            state = 1;
        } else if(strstr(linha, "\"nome\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", p.nome);
        } else if(strstr(linha, "\"area_de_atuacao\"")){
            sscanf(linha, " \"%*[^:\"]\" : \"%[^\"]\"", p.area_de_atuacao);
            if (state == 1) {
                listaProfessores = realloc(listaProfessores, (qtdProfessores+1) * sizeof(tpProfessor));
                listaProfessores[qtdProfessores++] = p;
                state = 0;
            }
        }
    }
    fclose(fp);
    printf("Carregados %d professores do arquivo!\n", qtdProfessores);
    listarProfessores();
}

void salvarProfessores() {
    FILE *fp = fopen(ARQ_PROFESSORES, "w");
    if(!fp){ return; }
    fprintf(fp, "[\n");
    for(int i = 0; i < qtdProfessores; i++){
        fprintf(fp,
            "  {\n"
            "    \"cpf\": \"%s\",\n"
            "    \"nome\": \"%s\",\n"
            "    \"area_de_atuacao\": \"%s\"\n"
            "  }%s\n",
            listaProfessores[i].cpf,
            listaProfessores[i].nome,
            listaProfessores[i].area_de_atuacao,
            (i == qtdProfessores-1 ? "" : ",")
        );
    }
    fprintf(fp, "]\n");
    fclose(fp);
    printf("\n>> dados salvos em Professor/dados.json <<\n");
}

tpProfessor create_instancia_professor(const char *cpf, const char *nome) {
    tpProfessor professor;
    memset(&professor, 0, sizeof(tpProfessor));
    if (cpf != NULL) {
        snprintf(professor.cpf, sizeof(professor.cpf), "%s", cpf);
    }
    if (nome != NULL) {
        snprintf(professor.nome, sizeof(professor.nome), "%s", nome);
    }
    snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", "Algoritmos");
    return professor;
}

int get_all_professores(tpProfessor **professores, int *quantidade) {
    if (professores == NULL || quantidade == NULL) {
        return 2;
    }

    if (qtdProfessores == 0) {
        *professores = NULL;
        *quantidade = 0;
        return 1;
    }

    tpProfessor *lista = malloc(qtdProfessores * sizeof(tpProfessor));
    if (lista == NULL) {
        return 99;
    }

    memcpy(lista, listaProfessores, qtdProfessores * sizeof(tpProfessor));
    *professores = lista;
    *quantidade = qtdProfessores;

    return 0;
}
