#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "../Disciplina/disciplina.h"
#include "../Professor/professor.h"
#include "professor_disciplina.h"

static tpDisciplina criarDisciplina(const char *codigo) {
    tpDisciplina disciplina;
    memset(&disciplina, 0, sizeof(tpDisciplina));
    snprintf(disciplina.codigo, sizeof(disciplina.codigo), "%s", codigo);
    snprintf(disciplina.nome, sizeof(disciplina.nome), "%s", "Disciplina PD");
    return disciplina;
}

static tpProfessor criarProfessor(const char *cpf) {
    tpProfessor professor;
    memset(&professor, 0, sizeof(tpProfessor));
    snprintf(professor.cpf, sizeof(professor.cpf), "%s", cpf);
    snprintf(professor.nome, sizeof(professor.nome), "%s", "Professor PD");
    snprintf(professor.area_de_atuacao, sizeof(professor.area_de_atuacao), "%s", "Redes");
    return professor;
}

void run_tests_professor_disciplina(void) {
    TestSuite suite;
    test_suite_init(&suite, "Professor x Disciplina");

    tpDisciplina *estadoDisciplinas = NULL;
    int qtdDisciplinas = 0;
    disciplina_detach_state(&estadoDisciplinas, &qtdDisciplinas);

    tpProfessor *estadoProfessores = NULL;
    int qtdProfessores = 0;
    professor_detach_state(&estadoProfessores, &qtdProfessores);

    tpProfessorDisciplinaRel *estadoRelacao = NULL;
    int qtdRelacao = 0;
    professor_disciplina_detach_state(&estadoRelacao, &qtdRelacao);

    tpDisciplina disciplina = criarDisciplina("DPD1");
    create_disciplina(&disciplina);
    tpProfessor professor = criarProfessor("99988877700");
    create_professor(&professor);

    tpDisciplina disciplinaInvalida = criarDisciplina("SEM");
    tpProfessor professorInvalido = criarProfessor("11122233344");

    test_suite_expect(&suite, "link - parâmetro inválido", 2, link_professor_disciplina(NULL, &professor));
    test_suite_expect(&suite, "link - disciplina ou professor inexistente", 1, link_professor_disciplina(&disciplinaInvalida, &professorInvalido));
    test_suite_expect(&suite, "link - sucesso", 0, link_professor_disciplina(&disciplina, &professor));
    professor_disciplina_set_forced_return(99);
    test_suite_expect(&suite, "link - exceção forçada", 99, link_professor_disciplina(&disciplina, &professor));

    tpProfessor *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get - parâmetro inválido", 2, get_professores_disciplina(NULL, &lista, &quantidade));
    test_suite_expect(&suite, "get - disciplina sem professores", 1, get_professores_disciplina(&disciplinaInvalida, &lista, &quantidade));
    test_suite_expect(&suite, "get - sucesso", 0, get_professores_disciplina(&disciplina, &lista, &quantidade));
    free(lista);
    professor_disciplina_set_forced_return(99);
    lista = NULL;
    quantidade = 0;
    test_suite_expect(&suite, "get - exceção forçada", 99, get_professores_disciplina(&disciplina, &lista, &quantidade));

    tpProfessorDisciplinaRel *estadoRelacaoTeste = NULL;
    int qtdRelacaoTeste = 0;
    professor_disciplina_detach_state(&estadoRelacaoTeste, &qtdRelacaoTeste);
    professor_disciplina_free_state(estadoRelacaoTeste);
    professor_disciplina_attach_state(estadoRelacao, qtdRelacao);

    tpDisciplina *estadoDisciplinasTeste = NULL;
    int qtdDisciplinasTeste = 0;
    disciplina_detach_state(&estadoDisciplinasTeste, &qtdDisciplinasTeste);
    disciplina_free_state(estadoDisciplinasTeste);
    disciplina_attach_state(estadoDisciplinas, qtdDisciplinas);

    tpProfessor *estadoProfessoresTeste = NULL;
    int qtdProfessoresTeste = 0;
    professor_detach_state(&estadoProfessoresTeste, &qtdProfessoresTeste);
    professor_free_state(estadoProfessoresTeste);
    professor_attach_state(estadoProfessores, qtdProfessores);

    test_suite_finish(&suite);
}

