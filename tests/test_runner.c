#include <stdio.h>
#include "test_utils.h"
#include "test_runner.h"

void run_tests_aluno(void);
void run_tests_universidade(void);
void run_tests_disciplina(void);
void run_tests_professor(void);
void run_tests_avaliacao(void);
void run_tests_aluno_universidade(void);
void run_tests_disciplina_universidade(void);
void run_tests_professor_disciplina(void);

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

