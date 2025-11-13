#include "professor.h"

tpProfessor *listaProfessores = NULL;
int qtdProfessores = 0;

static void listarProfessores(void);

int read_Professor(char *cpf, tpProfessor *professor) {
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

int delete_Professor(char *cpf){
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

            tpProfessor *tmp = realloc(listaProfessores, qtdProfessores * sizeof(tpProfessores));
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

int create_Professor(tpProfessor *professor) {
    return 0;
}

int update_Professors(char *cpf, tpProfessor *professor) {
    return 0;
}
