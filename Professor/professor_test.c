#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "professor.h"

void run_tests_professor(void) {
    TestSuite suite;
    test_suite_init(&suite, "Professor");

    tpProfessor *estadoOriginal = NULL;
    int qtdOriginal = 0;
    professor_detach_state(&estadoOriginal, &qtdOriginal);

    tpProfessor p1 = create_instancia_professor("12345678900", "Prof. Teste");
    tpProfessor leitura;

    test_suite_expect(&suite, "create_professor - sucesso", 0, create_professor(&p1));
    test_suite_expect(&suite, "create_professor - duplicado", 1, create_professor(&p1));
    test_suite_expect(&suite, "create_professor - parâmetro inválido", 2, create_professor(NULL));

    test_suite_expect(&suite, "read_professor - parâmetro inválido", 2, read_professor(NULL, &leitura));
    test_suite_expect(&suite, "read_professor - não encontrado", 1, read_professor("000", &leitura));
    test_suite_expect(&suite, "read_professor - sucesso", 0, read_professor(p1.cpf, &leitura));

    tpProfessor atualizacao = create_instancia_professor(p1.cpf, "Prof. Atualizado");
    test_suite_expect(&suite, "update_professor - parâmetro inválido", 2, update_professor(NULL, &atualizacao));
    test_suite_expect(&suite, "update_professor - não encontrado", 1, update_professor("000", &atualizacao));
    test_suite_expect(&suite, "update_professor - sucesso", 0, update_professor(p1.cpf, &atualizacao));

    test_suite_expect(&suite, "delete_professor - parâmetro inválido", 2, delete_professor(NULL));
    test_suite_expect(&suite, "delete_professor - sucesso", 0, delete_professor(p1.cpf));
    test_suite_expect(&suite, "delete_professor - não encontrado", 1, delete_professor(p1.cpf));

    tpProfessor *listaProfessores = NULL;
    int quantidadeProfessores = 0;
    test_suite_expect(&suite, "get_all_professores - parâmetro inválido", 2, get_all_professores(NULL, &quantidadeProfessores));
    test_suite_expect(&suite, "get_all_professores - vazio", 1, get_all_professores(&listaProfessores, &quantidadeProfessores));
    free(listaProfessores);
    listaProfessores = NULL;
    quantidadeProfessores = 0;
    
    tpProfessor p2 = create_instancia_professor("98765432100", "Prof. 2");
    create_professor(&p2);
    test_suite_expect(&suite, "get_all_professores - sucesso", 0, get_all_professores(&listaProfessores, &quantidadeProfessores));
    free(listaProfessores);

    tpProfessor *estadoTestes = NULL;
    int qtdTestes = 0;
    professor_detach_state(&estadoTestes, &qtdTestes);
    professor_free_state(estadoTestes);
    professor_attach_state(estadoOriginal, qtdOriginal);

    test_suite_finish(&suite);
}

