#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

typedef struct {
    char cnpj[100];
    char nome[150];
    char descricao[255];
} tpUniversidade;

int read_universidade(char *cnpj, tpUniversidade *universidade);
int delete_universidade(char *cnpj);
int create_universidade(tpUniversidade *universidade);
int get_universidades(tpUniversidade **universidades, int *quantidade);

#endif

