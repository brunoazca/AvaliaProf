#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "../Disciplina/disciplina.h"
#include "../Professor/professor.h"
#include "professor_disciplina.h"
#include "professor_disciplina_test.h"

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

    tpDisciplina disciplina = create_instancia_disciplina("DPD1", "Disciplina PD");
    create_disciplina(&disciplina);
    tpProfessor professor = create_instancia_professor("99988877700", "Professor PD");
    create_professor(&professor);

    tpDisciplina disciplinaInvalida = create_instancia_disciplina("SEM", "Disciplina PD");
    tpProfessor professorInvalido = create_instancia_professor("11122233344", "Professor PD");

    test_suite_expect(&suite, "link - parâmetro inválido", 2, link_professor_disciplina(NULL, &professor));
    test_suite_expect(&suite, "link - disciplina ou professor inexistente", 1, link_professor_disciplina(&disciplinaInvalida, &professorInvalido));
    test_suite_expect(&suite, "link - sucesso", 0, link_professor_disciplina(&disciplina, &professor));

    tpProfessor *lista = NULL;
    int quantidade = 0;
    test_suite_expect(&suite, "get - parâmetro inválido", 2, get_professores_disciplina(NULL, &lista, &quantidade));
    test_suite_expect(&suite, "get - disciplina sem professores", 1, get_professores_disciplina(&disciplinaInvalida, &lista, &quantidade));
    test_suite_expect(&suite, "get - sucesso", 0, get_professores_disciplina(&disciplina, &lista, &quantidade));
    free(lista);
    lista = NULL;
    quantidade = 0;

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

