#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "../Disciplina/disciplina.h"
#include "../Universidade/universidade.h"
#include "disciplina_universidade.h"

static tpDisciplina criarDisciplina(const char *codigo) {
    tpDisciplina disciplina;
    memset(&disciplina, 0, sizeof(tpDisciplina));
    snprintf(disciplina.codigo, sizeof(disciplina.codigo), "%s", codigo);
    snprintf(disciplina.nome, sizeof(disciplina.nome), "%s", "Disciplina Rel");
    return disciplina;
}

static tpUniversidade criarUniversidade(const char *cnpj) {
    tpUniversidade universidade;
    memset(&universidade, 0, sizeof(tpUniversidade));
    snprintf(universidade.cnpj, sizeof(universidade.cnpj), "%s", cnpj);
    snprintf(universidade.nome, sizeof(universidade.nome), "%s", "Uni Rel");
    snprintf(universidade.descricao, sizeof(universidade.descricao), "%s", "Desc");
    return universidade;
}

void run_tests_disciplina_universidade(void) {
    TestSuite suite;
    test_suite_init(&suite, "Disciplina x Universidade");

    tpDisciplina *estadoDisciplinas = NULL;
    int qtdDisciplinas = 0;
    disciplina_detach_state(&estadoDisciplinas, &qtdDisciplinas);

    tpUniversidade *estadoUniversidades = NULL;
    int qtdUniversidades = 0;
    universidade_detach_state(&estadoUniversidades, &qtdUniversidades);

    void *estadoRelacao = NULL;
    int qtdRelacao = 0;
    disciplina_universidade_detach_state(&estadoRelacao, &qtdRelacao);

    tpDisciplina disciplina = criarDisciplina("DREL1");
    tpUniversidade universidade = criarUniversidade("33.333.333/0001-33");
    create_disciplina(&disciplina);
    create_universidade(&universidade);

    tpUniversidade universidadeSemDisciplina = criarUniversidade("44.444.444/0001-44");
    create_universidade(&universidadeSemDisciplina);

    tpDisciplina disciplinaSemCadastro = criarDisciplina("NAOEXISTE");

    test_suite_expect(&suite, "link - parâmetro inválido", 2, link_disciplina_universidade(NULL, &universidade));
    test_suite_expect(&suite, "link - disciplina inexistente", 1, link_disciplina_universidade(&disciplinaSemCadastro, &universidade));
    test_suite_expect(&suite, "link - sucesso", 0, link_disciplina_universidade(&disciplina, &universidade));

    tpDisciplina *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get - parâmetro inválido", 2, get_disciplinas_universidade(NULL, &lista, &quantidade));
    test_suite_expect(&suite, "get - nenhuma disciplina", 1, get_disciplinas_universidade(&universidadeSemDisciplina, &lista, &quantidade));
    test_suite_expect(&suite, "get - sucesso", 0, get_disciplinas_universidade(&universidade, &lista, &quantidade));
    free(lista);
    lista = NULL;
    quantidade = 0;

    void *estadoRelacaoTeste = NULL;
    int qtdRelacaoTeste = 0;
    disciplina_universidade_detach_state(&estadoRelacaoTeste, &qtdRelacaoTeste);
    disciplina_universidade_free_state(estadoRelacaoTeste);
    disciplina_universidade_attach_state(estadoRelacao, qtdRelacao);

    tpDisciplina *estadoDisciplinasTeste = NULL;
    int qtdDisciplinasTeste = 0;
    disciplina_detach_state(&estadoDisciplinasTeste, &qtdDisciplinasTeste);
    disciplina_free_state(estadoDisciplinasTeste);
    disciplina_attach_state(estadoDisciplinas, qtdDisciplinas);

    tpUniversidade *estadoUniversidadesTeste = NULL;
    int qtdUniversidadesTeste = 0;
    universidade_detach_state(&estadoUniversidadesTeste, &qtdUniversidadesTeste);
    universidade_free_state(estadoUniversidadesTeste);
    universidade_attach_state(estadoUniversidades, qtdUniversidades);

    test_suite_finish(&suite);
}

