#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../tests/test_utils.h"
#include "../Aluno/aluno.h"
#include "../Professor/professor.h"
#include "avaliacao.h"

static tpAvaliacao criarAvaliacao(const char *id, const char *nota) {
    tpAvaliacao avaliacao;
    memset(&avaliacao, 0, sizeof(tpAvaliacao));
    snprintf(avaliacao.id, sizeof(avaliacao.id), "%s", id);
    snprintf(avaliacao.nota, sizeof(avaliacao.nota), "%s", nota);
    snprintf(avaliacao.comentario, sizeof(avaliacao.comentario), "%s", "Muito bom");
    snprintf(avaliacao.timestamp, sizeof(avaliacao.timestamp), "%s", "2025-11-15T10:00:00Z");
    return avaliacao;
}

static tpAluno criarAluno(const char *cpf, const char *nome, const char *email) {
    tpAluno aluno;
    memset(&aluno, 0, sizeof(tpAluno));
    snprintf(aluno.cpf, sizeof(aluno.cpf), "%s", cpf);
    snprintf(aluno.nome, sizeof(aluno.nome), "%s", nome);
    snprintf(aluno.email, sizeof(aluno.email), "%s", email);
    snprintf(aluno.senha, sizeof(aluno.senha), "%s", "senha");
    snprintf(aluno.curso, sizeof(aluno.curso), "%s", "Computação");
    snprintf(aluno.universidade, sizeof(aluno.universidade), "%s", "UFTestes");
    return aluno;
}

static tpProfessor criarProfessor(const char *cpf, const char *nome) {
    tpProfessor professor;
    memset(&professor, 0, sizeof(tpProfessor));
    snprintf(professor.cpf, sizeof(professor.cpf), "%s", cpf);
    snprintf(professor.nome, sizeof(professor.nome), "%s", nome);
    snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", "Álgebra");
    return professor;
}

void run_tests_avaliacao(void) {
    TestSuite suite;
    test_suite_init(&suite, "Avaliação");

    tpAluno *estadoAlunos = NULL;
    int qtdAlunos = 0;
    aluno_detach_state(&estadoAlunos, &qtdAlunos);

    tpProfessor *estadoProfessores = NULL;
    int qtdProfessores = 0;
    professor_detach_state(&estadoProfessores, &qtdProfessores);

    void *estadoAvaliacoes = NULL;
    int qtdAvaliacoes = 0;
    avaliacao_detach_state(&estadoAvaliacoes, &qtdAvaliacoes);

    tpAluno aluno = criarAluno("88877766655", "Aluno Aval", "aval@aluno.com");
    registrar(&aluno);

    tpProfessor professor = criarProfessor("55544433322", "Prof Aval");
    create_professor(&professor);

    tpAvaliacao avaliacao = criarAvaliacao("AV1", "5");
    tpProfessor professorOutro = criarProfessor("22233344455", "Prof Sem Aval");
    create_professor(&professorOutro);

    test_suite_expect(&suite, "create_avaliacao - parâmetro inválido", 2, create_avaliacao(NULL, &professor, &avaliacao));
    test_suite_expect(&suite, "create_avaliacao - sucesso", 0, create_avaliacao(&aluno, &professor, &avaliacao));
    test_suite_expect(&suite, "create_avaliacao - duplicada", 1, create_avaliacao(&aluno, &professor, &avaliacao));
    tpAvaliacao invalida = criarAvaliacao("AV2", "6"); // nota inválida
    test_suite_expect(&suite, "create_avaliacao - nota inválida", 2, create_avaliacao(&aluno, &professor, &invalida));

    tpAvaliacao *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get_avaliacoes_professor - parâmetro inválido", 2, get_avaliacoes_professor(NULL, &lista, &quantidade));
    test_suite_expect(&suite, "get_avaliacoes_professor - sem registros", 1, get_avaliacoes_professor(&professorOutro, &lista, &quantidade));
    test_suite_expect(&suite, "get_avaliacoes_professor - sucesso", 0, get_avaliacoes_professor(&professor, &lista, &quantidade));
    free(lista);
    lista = NULL;
    quantidade = 0;

    void *estadoTeste = NULL;
    int qtdTeste = 0;
    avaliacao_detach_state(&estadoTeste, &qtdTeste);
    avaliacao_free_state(estadoTeste);
    avaliacao_attach_state(estadoAvaliacoes, qtdAvaliacoes);

    tpAluno *estadoAlunosTeste = NULL;
    int qtdAlunosTeste = 0;
    aluno_detach_state(&estadoAlunosTeste, &qtdAlunosTeste);
    aluno_free_state(estadoAlunosTeste);
    aluno_attach_state(estadoAlunos, qtdAlunos);

    tpProfessor *estadoProfessoresTeste = NULL;
    int qtdProfessoresTeste = 0;
    professor_detach_state(&estadoProfessoresTeste, &qtdProfessoresTeste);
    professor_free_state(estadoProfessoresTeste);
    professor_attach_state(estadoProfessores, qtdProfessores);

    test_suite_finish(&suite);
}

