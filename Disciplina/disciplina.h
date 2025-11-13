#ifndef DISCIPLINA_H
#define DISCIPLINA_H

typedef struct {
    char codigo[50];
    char nome[150];
} tpDisciplina;

extern tpDisciplina *listaDisciplinas;
extern int qtdDisciplinas;

int read_Disciplina(char *codigo, tpDisciplina *disciplina);
int delete_Disciplina(char *codigo);
int create_Disciplina(tpDisciplina *disciplina);
int update_Disciplinas(char *codigo, tpDisciplina *disciplina);

#endif

