#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

typedef struct {
    char cnpj[100];
    char nome[150];
    char descricao[255];
} tpUniversidade;

int read_Universidade(char *cnpj, tpUniversidade *universidade);
int delete_Universidade(char *cnpj);
int create_Universidade(tpUniversidade *universidade);
int get_Universidades(tpUniversidade **universidades);

#endif

