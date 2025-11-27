#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "disciplina.h"
#include "disciplina_test.h"

void run_tests_disciplina(void) {
    TestSuite suite;
    test_suite_init(&suite, "Disciplina");

    tpDisciplina *estadoOriginal = NULL;
    int qtdOriginal = 0;
    disciplina_detach_state(&estadoOriginal, &qtdOriginal);

    tpDisciplina d1 = create_instancia_disciplina("DISC1", "Disciplina 1");
    tpDisciplina leitura;

    test_suite_expect(&suite, "create_disciplina - sucesso", 0, create_disciplina(&d1));
    test_suite_expect(&suite, "create_disciplina - duplicada", 1, create_disciplina(&d1));
    test_suite_expect(&suite, "create_disciplina - parâmetro inválido", 2, create_disciplina(NULL));

    test_suite_expect(&suite, "read_disciplina - parâmetro inválido", 2, read_disciplina(NULL, &leitura));
    test_suite_expect(&suite, "read_disciplina - não encontrada", 1, read_disciplina("NAO_EXISTE", &leitura));
    test_suite_expect(&suite, "read_disciplina - sucesso", 0, read_disciplina(d1.codigo, &leitura));

    tpDisciplina atualizacao = create_instancia_disciplina("DISC1", "Novo Nome");
    test_suite_expect(&suite, "update_disciplina - parâmetro inválido", 2, update_disciplina(NULL, &atualizacao));
    test_suite_expect(&suite, "update_disciplina - não encontrada", 1, update_disciplina("NAO_EXISTE", &atualizacao));
    test_suite_expect(&suite, "update_disciplina - sucesso", 0, update_disciplina(d1.codigo, &atualizacao));

    test_suite_expect(&suite, "delete_disciplina - parâmetro inválido", 2, delete_disciplina(NULL));
    test_suite_expect(&suite, "delete_disciplina - sucesso", 0, delete_disciplina(d1.codigo));
    test_suite_expect(&suite, "delete_disciplina - não encontrada", 1, delete_disciplina(d1.codigo));

    tpDisciplina *listaDisciplinas = NULL;
    int quantidadeDisciplinas = 0;
    test_suite_expect(&suite, "get_all_disciplinas - parâmetro inválido", 2, get_all_disciplinas(NULL, &quantidadeDisciplinas));
    test_suite_expect(&suite, "get_all_disciplinas - vazio", 1, get_all_disciplinas(&listaDisciplinas, &quantidadeDisciplinas));
    free(listaDisciplinas);
    listaDisciplinas = NULL;
    quantidadeDisciplinas = 0;
    
    tpDisciplina d2 = create_instancia_disciplina("DISC2", "Disciplina 2");
    create_disciplina(&d2);
    test_suite_expect(&suite, "get_all_disciplinas - sucesso", 0, get_all_disciplinas(&listaDisciplinas, &quantidadeDisciplinas));
    free(listaDisciplinas);

    tpDisciplina *estadoTestes = NULL;
    int qtdTestes = 0;
    disciplina_detach_state(&estadoTestes, &qtdTestes);
    disciplina_free_state(estadoTestes);
    disciplina_attach_state(estadoOriginal, qtdOriginal);

    test_suite_finish(&suite);
}

