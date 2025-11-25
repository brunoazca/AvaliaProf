#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../tests/test_utils.h"
#include "../Aluno/aluno.h"
#include "../Professor/professor.h"
#include "avaliacao.h"

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

    tpAluno aluno = create_instancia_aluno("88877766655", "Aluno Aval", "aval@aluno.com");
    registrar(&aluno);

    tpProfessor professor = create_instancia_professor("55544433322", "Prof Aval");
    create_professor(&professor);

    tpAvaliacao avaliacao = create_instancia_avaliacao("AV1", "5");
    tpProfessor professorOutro = create_instancia_professor("22233344455", "Prof Sem Aval");
    create_professor(&professorOutro);

    test_suite_expect(&suite, "create_avaliacao - parâmetro inválido", 2, create_avaliacao(NULL, &professor, &avaliacao));
    test_suite_expect(&suite, "create_avaliacao - sucesso", 0, create_avaliacao(&aluno, &professor, &avaliacao));
    test_suite_expect(&suite, "create_avaliacao - duplicada", 1, create_avaliacao(&aluno, &professor, &avaliacao));
    tpAvaliacao invalida = create_instancia_avaliacao("AV2", "6"); // nota inválida
    test_suite_expect(&suite, "create_avaliacao - nota inválida", 2, create_avaliacao(&aluno, &professor, &invalida));

    tpAvaliacao *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get_avaliacoes_professor - parâmetro inválido", 2, get_avaliacoes_professor(NULL, &lista, &quantidade));
    test_suite_expect(&suite, "get_avaliacoes_professor - sem registros", 1, get_avaliacoes_professor(&professorOutro, &lista, &quantidade));
    test_suite_expect(&suite, "get_avaliacoes_professor - sucesso", 0, get_avaliacoes_professor(&professor, &lista, &quantidade));
    free(lista);
    lista = NULL;
    quantidade = 0;

    tpAvaliacao *todasAvaliacoes = NULL;
    int quantidadeTodas = 0;
    test_suite_expect(&suite, "get_all_avaliacoes - parâmetro inválido", 2, get_all_avaliacoes(NULL, &quantidadeTodas));
    test_suite_expect(&suite, "get_all_avaliacoes - sucesso", 0, get_all_avaliacoes(&todasAvaliacoes, &quantidadeTodas));
    free(todasAvaliacoes);

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

