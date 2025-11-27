#include <stdio.h>
#include "test_utils.h"
#include "test_runner.h"
#include "../Aluno/aluno_test.h"
#include "../Universidade/universidade_test.h"
#include "../Disciplina/disciplina_test.h"
#include "../Professor/professor_test.h"
#include "../Avaliacao/avaliacao_test.h"
#include "../Aluno_Universidade/aluno_universidade_test.h"
#include "../Disciplina_Universidade/disciplina_universidade_test.h"
#include "../Professor_Disciplina/professor_disciplina_test.h"

void run_all_tests(void) {
    test_utils_reset_overall();

    run_tests_aluno();
    run_tests_universidade();
    run_tests_disciplina();
    run_tests_professor();
    run_tests_avaliacao();
    run_tests_aluno_universidade();
    run_tests_disciplina_universidade();
    run_tests_professor_disciplina();

    int total, passed;
    test_utils_get_overall(&total, &passed);
    printf("\n=== RESUMO GERAL DOS TESTES ===\n");
    printf("Casos aprovados: %d/%d\n", passed, total);
    printf("===============================\n");
}

