#ifndef DISCIPLINA_H
#define DISCIPLINA_H

typedef struct {
    char codigo[50];
    char nome[150];
    char universidade[150];
    char professor[150];
} tpDisciplina;

extern tpDisciplina *listaDisciplinas;
extern int qtdDisciplinas;

int read_disciplina(char *codigo, tpDisciplina *disciplina);
int delete_disciplina(char *codigo);
int create_disciplina(tpDisciplina *disciplina);
int update_disciplina(char *codigo, tpDisciplina *disciplina);

void disciplina_detach_state(tpDisciplina **lista, int *quantidade);
void disciplina_attach_state(tpDisciplina *lista, int quantidade);
void disciplina_free_state(tpDisciplina *lista);

void carregarDisciplinas();
void salvarDisciplinas();

#endif

