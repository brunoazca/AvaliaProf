#include <stdio.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "../Aluno/aluno.h"
#include "../Universidade/universidade.h"
#include "aluno_universidade.h"

static tpAluno criarAluno(const char *cpf) {
    tpAluno aluno;
    memset(&aluno, 0, sizeof(tpAluno));
    snprintf(aluno.cpf, sizeof(aluno.cpf), "%s", cpf);
    snprintf(aluno.nome, sizeof(aluno.nome), "%s", "Aluno Rel");
    snprintf(aluno.email, sizeof(aluno.email), "%s", "rel@aluno.com");
    snprintf(aluno.senha, sizeof(aluno.senha), "%s", "123");
    snprintf(aluno.curso, sizeof(aluno.curso), "%s", "Engenharia");
    snprintf(aluno.universidade, sizeof(aluno.universidade), "%s", "Qualquer");
    return aluno;
}

static tpUniversidade criarUniversidade(const char *cnpj) {
    tpUniversidade universidade;
    memset(&universidade, 0, sizeof(tpUniversidade));
    snprintf(universidade.cnpj, sizeof(universidade.cnpj), "%s", cnpj);
    snprintf(universidade.nome, sizeof(universidade.nome), "%s", "Uni Rel");
    snprintf(universidade.descricao, sizeof(universidade.descricao), "%s", "Desc");
    return universidade;
}

void run_tests_aluno_universidade(void) {
    TestSuite suite;
    test_suite_init(&suite, "Aluno x Universidade");

    tpAluno *estadoAlunos = NULL;
    int qtdAlunos = 0;
    aluno_detach_state(&estadoAlunos, &qtdAlunos);

    tpUniversidade *estadoUniversidades = NULL;
    int qtdUniversidades = 0;
    universidade_detach_state(&estadoUniversidades, &qtdUniversidades);

    void *estadoRelacao = NULL;
    int qtdRelacao = 0;
    aluno_universidade_detach_state(&estadoRelacao, &qtdRelacao);

    tpAluno aluno = criarAluno("10101010100");
    tpUniversidade universidade = criarUniversidade("10.101.010/0001-00");
    registrar(&aluno);
    create_universidade(&universidade);

    tpAluno alunoNaoCadastrado = criarAluno("20202020200");

    test_suite_expect(&suite, "link - parâmetro inválido", 2, link_aluno_universidade(NULL, &universidade));
    test_suite_expect(&suite, "link - aluno inexistente", 1, link_aluno_universidade(&alunoNaoCadastrado, &universidade));
    test_suite_expect(&suite, "link - sucesso", 0, link_aluno_universidade(&aluno, &universidade));
    aluno_universidade_set_forced_return(99);
    test_suite_expect(&suite, "link - exceção forçada", 99, link_aluno_universidade(&aluno, &universidade));

    tpUniversidade universidadeDestino;
    test_suite_expect(&suite, "get - parâmetro inválido", 2, get_universidade_aluno(NULL, &universidadeDestino));
    test_suite_expect(&suite, "get - aluno sem vínculo", 1, get_universidade_aluno(&alunoNaoCadastrado, &universidadeDestino));
    test_suite_expect(&suite, "get - sucesso", 0, get_universidade_aluno(&aluno, &universidadeDestino));
    aluno_universidade_set_forced_return(99);
    test_suite_expect(&suite, "get - exceção forçada", 99, get_universidade_aluno(&aluno, &universidadeDestino));

    void *estadoRelacaoTeste = NULL;
    int qtdRelacaoTeste = 0;
    aluno_universidade_detach_state(&estadoRelacaoTeste, &qtdRelacaoTeste);
    aluno_universidade_free_state(estadoRelacaoTeste);
    aluno_universidade_attach_state(estadoRelacao, qtdRelacao);

    tpAluno *estadoAlunosTeste = NULL;
    int qtdAlunosTeste = 0;
    aluno_detach_state(&estadoAlunosTeste, &qtdAlunosTeste);
    aluno_free_state(estadoAlunosTeste);
    aluno_attach_state(estadoAlunos, qtdAlunos);

    tpUniversidade *estadoUniversidadesTeste = NULL;
    int qtdUniversidadesTeste = 0;
    universidade_detach_state(&estadoUniversidadesTeste, &qtdUniversidadesTeste);
    universidade_free_state(estadoUniversidadesTeste);
    universidade_attach_state(estadoUniversidades, qtdUniversidades);

    test_suite_finish(&suite);
}

