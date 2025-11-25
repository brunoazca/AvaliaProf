#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "universidade.h"

void run_tests_universidade(void) {
    TestSuite suite;
    test_suite_init(&suite, "Universidade");

    tpUniversidade *estadoOriginal = NULL;
    int qtdOriginal = 0;
    universidade_detach_state(&estadoOriginal, &qtdOriginal);

    tpUniversidade uni = create_instancia_universidade("11.222.333/0001-44", "Universidade Teste");
    tpUniversidade leitura;

    tpUniversidade *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get_universidades - vazio", 1, get_universidades(&lista, &quantidade));
    free(lista);

    test_suite_expect(&suite, "create_universidade - sucesso", 0, create_universidade(&uni));
    test_suite_expect(&suite, "create_universidade - duplicada", 1, create_universidade(&uni));
    test_suite_expect(&suite, "create_universidade - parâmetro inválido", 2, create_universidade(NULL));

    test_suite_expect(&suite, "read_universidade - parâmetro inválido", 2, read_universidade(NULL, &leitura));
    test_suite_expect(&suite, "read_universidade - não encontrada", 1, read_universidade("00.000.000/0000-00", &leitura));
    test_suite_expect(&suite, "read_universidade - sucesso", 0, read_universidade(uni.cnpj, &leitura));

    lista = NULL;
    quantidade = 0;
    test_suite_expect(&suite, "get_universidades - sucesso", 0, get_universidades(&lista, &quantidade));
    free(lista);
    lista = NULL;
    quantidade = 0;

    test_suite_expect(&suite, "delete_universidade - parâmetro inválido", 2, delete_universidade(NULL));
    test_suite_expect(&suite, "delete_universidade - sucesso", 0, delete_universidade(uni.cnpj));
    test_suite_expect(&suite, "delete_universidade - não encontrada", 1, delete_universidade(uni.cnpj));

    tpUniversidade *estadoTestes = NULL;
    int qtdTestes = 0;
    universidade_detach_state(&estadoTestes, &qtdTestes);
    universidade_free_state(estadoTestes);
    universidade_attach_state(estadoOriginal, qtdOriginal);

    test_suite_finish(&suite);
}

