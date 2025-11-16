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

void universidade_detach_state(tpUniversidade **lista, int *quantidade);
void universidade_attach_state(tpUniversidade *lista, int quantidade);
void universidade_free_state(tpUniversidade *lista);
void universidade_set_forced_return(int valor);

void carregarUniversidades();
void salvarUniversidades();

#endif

