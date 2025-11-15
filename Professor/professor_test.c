#include <stdio.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "professor.h"

static tpProfessor criarProfessor(const char *cpf, const char *nome) {
    tpProfessor professor;
    memset(&professor, 0, sizeof(tpProfessor));
    snprintf(professor.cpf, sizeof(professor.cpf), "%s", cpf);
    snprintf(professor.nome, sizeof(professor.nome), "%s", nome);
    snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", "Algoritmos");
    return professor;
}

void run_tests_professor(void) {
    TestSuite suite;
    test_suite_init(&suite, "Professor");

    tpProfessor *estadoOriginal = NULL;
    int qtdOriginal = 0;
    professor_detach_state(&estadoOriginal, &qtdOriginal);

    tpProfessor p1 = criarProfessor("12345678900", "Prof. Teste");
    tpProfessor p2 = criarProfessor("98765432100", "Prof. Dois");
    tpProfessor leitura;

    test_suite_expect(&suite, "create_professor - sucesso", 0, create_professor(&p1));
    test_suite_expect(&suite, "create_professor - duplicado", 1, create_professor(&p1));
    test_suite_expect(&suite, "create_professor - parâmetro inválido", 2, create_professor(NULL));
    professor_set_forced_return(99);
    test_suite_expect(&suite, "create_professor - exceção forçada", 99, create_professor(&p2));

    test_suite_expect(&suite, "read_professor - parâmetro inválido", 2, read_professor(NULL, &leitura));
    test_suite_expect(&suite, "read_professor - não encontrado", 1, read_professor("000", &leitura));
    test_suite_expect(&suite, "read_professor - sucesso", 0, read_professor(p1.cpf, &leitura));
    professor_set_forced_return(99);
    test_suite_expect(&suite, "read_professor - exceção forçada", 99, read_professor(p1.cpf, &leitura));

    tpProfessor atualizacao = criarProfessor(p1.cpf, "Prof. Atualizado");
    test_suite_expect(&suite, "update_professor - parâmetro inválido", 2, update_professor(NULL, &atualizacao));
    test_suite_expect(&suite, "update_professor - não encontrado", 1, update_professor("000", &atualizacao));
    test_suite_expect(&suite, "update_professor - sucesso", 0, update_professor(p1.cpf, &atualizacao));
    professor_set_forced_return(99);
    test_suite_expect(&suite, "update_professor - exceção forçada", 99, update_professor(p1.cpf, &atualizacao));

    test_suite_expect(&suite, "delete_professor - parâmetro inválido", 2, delete_professor(NULL));
    test_suite_expect(&suite, "delete_professor - sucesso", 0, delete_professor(p1.cpf));
    test_suite_expect(&suite, "delete_professor - não encontrado", 1, delete_professor(p1.cpf));
    professor_set_forced_return(99);
    test_suite_expect(&suite, "delete_professor - exceção forçada", 99, delete_professor(p1.cpf));

    tpProfessor *estadoTestes = NULL;
    int qtdTestes = 0;
    professor_detach_state(&estadoTestes, &qtdTestes);
    professor_free_state(estadoTestes);
    professor_attach_state(estadoOriginal, qtdOriginal);

    test_suite_finish(&suite);
}

