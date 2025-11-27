#include <stdio.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "../Aluno/aluno.h"
#include "../Universidade/universidade.h"
#include "aluno_universidade.h"

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

    tpAluno aluno = create_instancia_aluno("10101010100", "Aluno Rel", "rel@aluno.com");
    tpUniversidade universidade = create_instancia_universidade("10.101.010/0001-00", "Uni Rel");
    registrar(&aluno, NULL);
    create_universidade(&universidade);

    tpAluno alunoNaoCadastrado = create_instancia_aluno("20202020200", "Aluno Rel", "rel@aluno.com");

    test_suite_expect(&suite, "link - parâmetro inválido", 2, link_aluno_universidade(NULL, &universidade));
    test_suite_expect(&suite, "link - aluno inexistente", 1, link_aluno_universidade(&alunoNaoCadastrado, &universidade));
    test_suite_expect(&suite, "link - sucesso", 0, link_aluno_universidade(&aluno, &universidade));

    tpUniversidade universidadeDestino;
    test_suite_expect(&suite, "get - parâmetro inválido", 2, get_universidade_aluno(NULL, &universidadeDestino));
    test_suite_expect(&suite, "get - aluno sem vínculo", 1, get_universidade_aluno(&alunoNaoCadastrado, &universidadeDestino));
    test_suite_expect(&suite, "get - sucesso", 0, get_universidade_aluno(&aluno, &universidadeDestino));

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

