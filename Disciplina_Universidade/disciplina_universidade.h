#ifndef DISCIPLINA_UNIVERSIDADE_H
#define DISCIPLINA_UNIVERSIDADE_H

#include "../Disciplina/disciplina.h"
#include "../Universidade/universidade.h"

int link_disciplina_universidade(tpDisciplina *disciplina, tpUniversidade *universidade);
int get_disciplinas_universidade(tpUniversidade *universidade, tpDisciplina **disciplinas, int *quantidade);

void disciplina_universidade_detach_state(void **relacoes, int *quantidade);
void disciplina_universidade_attach_state(void *relacoes, int quantidade);
void disciplina_universidade_free_state(void *relacoes);
void disciplina_universidade_set_forced_return(int valor);

#endif

