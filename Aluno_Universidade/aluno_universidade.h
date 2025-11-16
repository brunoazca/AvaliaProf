#ifndef ALUNO_UNIVERSIDADE_H
#define ALUNO_UNIVERSIDADE_H

#include "../Aluno/aluno.h"
#include "../Universidade/universidade.h"

int link_aluno_universidade(tpAluno *aluno, tpUniversidade *universidade);
int get_universidade_aluno(tpAluno *aluno, tpUniversidade *universidade);

void aluno_universidade_detach_state(void **relacoes, int *quantidade);
void aluno_universidade_attach_state(void *relacoes, int quantidade);
void aluno_universidade_free_state(void *relacoes);
void aluno_universidade_set_forced_return(int valor);

void carregarAlunoUniversidade();
void salvarAlunoUniversidade();

#endif

