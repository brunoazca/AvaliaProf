#ifndef PROFESSOR_DISCIPLINA_H
#define PROFESSOR_DISCIPLINA_H

#include "../Professor/professor.h"
#include "../Disciplina/disciplina.h"

int link_professor_disciplina(tpDisciplina *disciplina, tpProfessor *professor);
int get_professor_disciplina(tpDisciplina *disciplina, tpProfessor **professores);

#endif

