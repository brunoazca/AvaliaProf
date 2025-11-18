#ifndef AVALIACAO_H
#define AVALIACAO_H

#include "../Aluno/aluno.h"
#include "../Professor/professor.h"

typedef struct {
    char id[50];
    char nota[10];
    char comentario[255];
    char timestamp[50];
} tpAvaliacao;

int create_avaliacao(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao);
int get_avaliacoes_professor(tpProfessor *professor, tpAvaliacao **avaliacoes, int *quantidade);

void avaliacao_detach_state(void **estado, int *quantidade);
void avaliacao_attach_state(void *estado, int quantidade);
void avaliacao_free_state(void *estado);

void carregarAvaliacoes();
void salvarAvaliacoes();

#endif

