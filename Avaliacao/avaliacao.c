#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avaliacao.h"

typedef struct {
    tpAvaliacao avaliacao;
    tpAluno aluno;
    tpProfessor professor;
} tpAvaliacaoRegistro;

static tpAvaliacaoRegistro *listaAvaliacoes = NULL;
static int qtdAvaliacoes = 0;
static int avaliacao_forced_return = 0;

static int validarCampos(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao);
static int avaliacao_consume_forced_return(void) {
    if (avaliacao_forced_return != 0) {
        int value = avaliacao_forced_return;
        avaliacao_forced_return = 0;
        return value;
    }
    return 0;
}

void avaliacao_set_forced_return(int valor) {
    avaliacao_forced_return = valor;
}

int create_avaliacao(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao) {
    int forced = avaliacao_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (!validarCampos(aluno, professor, avaliacao)) {
        return 2;
    }

    tpAluno alunoEncontrado;
    tpProfessor professorEncontrado;

    if (read_aluno(aluno->cpf, &alunoEncontrado) != 0) {
        return 1;
    }

    if (read_professor(professor->cpf, &professorEncontrado) != 0) {
        return 1;
    }

    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].avaliacao.id, avaliacao->id) == 0) {
            return 1;
        }
    }

    tpAvaliacaoRegistro *novaLista = realloc(listaAvaliacoes, (qtdAvaliacoes + 1) * sizeof(tpAvaliacaoRegistro));
    if (novaLista == NULL) {
        return 99;
    }

    listaAvaliacoes = novaLista;
    listaAvaliacoes[qtdAvaliacoes].avaliacao = *avaliacao;
    listaAvaliacoes[qtdAvaliacoes].aluno = alunoEncontrado;
    listaAvaliacoes[qtdAvaliacoes].professor = professorEncontrado;
    qtdAvaliacoes++;

    return 0;
}

int get_avaliacoes_professor(tpProfessor *professor, tpAvaliacao **avaliacoes, int *quantidade) {
    int forced = avaliacao_consume_forced_return();
    if (forced != 0) {
        return forced;
    }
    if (professor == NULL || avaliacoes == NULL || quantidade == NULL || strlen(professor->cpf) == 0) {
        return 2;
    }

    int total = 0;
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].professor.cpf, professor->cpf) == 0) {
            total++;
        }
    }

    if (total == 0) {
        *avaliacoes = NULL;
        *quantidade = 0;
        return 1;
    }

    tpAvaliacao *lista = malloc(total * sizeof(tpAvaliacao));
    if (lista == NULL) {
        return 99;
    }

    int indice = 0;
    for (int i = 0; i < qtdAvaliacoes; i++) {
        if (strcmp(listaAvaliacoes[i].professor.cpf, professor->cpf) == 0) {
            lista[indice++] = listaAvaliacoes[i].avaliacao;
        }
    }

    *avaliacoes = lista;
    *quantidade = total;
    return 0;
}

static int validarCampos(tpAluno *aluno, tpProfessor *professor, tpAvaliacao *avaliacao) {
    if (aluno == NULL || professor == NULL || avaliacao == NULL) {
        return 0;
    }

    if (strlen(aluno->cpf) == 0 || strlen(professor->cpf) == 0) {
        return 0;
    }

    if (strlen(avaliacao->id) == 0 ||
        strlen(avaliacao->nota) == 0 ||
        strlen(avaliacao->comentario) == 0 ||
        strlen(avaliacao->timestamp) == 0) {
        return 0;
    }

    int nota = atoi(avaliacao->nota);
    if (nota < 1 || nota > 5) {
        return 0;
    }

    return 1;
}

void avaliacao_detach_state(void **estado, int *quantidade) {
    if (estado == NULL || quantidade == NULL) {
        return;
    }
    *estado = listaAvaliacoes;
    *quantidade = qtdAvaliacoes;
    listaAvaliacoes = NULL;
    qtdAvaliacoes = 0;
}

void avaliacao_attach_state(void *estado, int quantidade) {
    if (listaAvaliacoes != NULL) {
        free(listaAvaliacoes);
    }
    listaAvaliacoes = estado;
    qtdAvaliacoes = quantidade;
}

void avaliacao_free_state(void *estado) {
    free(estado);
}
