#ifndef PROFESSOR_DISCIPLINA_H
#define PROFESSOR_DISCIPLINA_H

#include "../Professor/professor.h"
#include "../Disciplina/disciplina.h"

typedef struct {
    char disciplinaCodigo[50];
    char professorCpf[100];
} tpProfessorDisciplinaRel;

int link_professor_disciplina(tpDisciplina *disciplina, tpProfessor *professor);
int get_professores_disciplina(tpDisciplina *disciplina, tpProfessor **professores, int *quantidade);

#endif

