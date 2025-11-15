#include <stdio.h>
#include "test_utils.h"

static int overall_total = 0;
static int overall_passed = 0;

void test_utils_reset_overall(void) {
    overall_total = 0;
    overall_passed = 0;
}

void test_utils_get_overall(int *total, int *passed) {
    if (total != NULL) {
        *total = overall_total;
    }
    if (passed != NULL) {
        *passed = overall_passed;
    }
}

void test_suite_init(TestSuite *suite, const char *module) {
    if (suite == NULL) {
        return;
    }
    suite->module = module;
    suite->total = 0;
    suite->passed = 0;
    printf("\n--- Testes do módulo %s ---\n", module);
}

void test_suite_expect(TestSuite *suite, const char *case_name, int expected, int actual) {
    if (suite == NULL) {
        return;
    }

    suite->total++;
    overall_total++;

    if (expected == actual) {
        suite->passed++;
        overall_passed++;
        printf("[OK]   %s: esperado=%d obtido=%d\n", case_name, expected, actual);
    } else {
        printf("[FALHA] %s: esperado=%d obtido=%d\n", case_name, expected, actual);
    }
}

void test_suite_finish(TestSuite *suite) {
    if (suite == NULL) {
        return;
    }
    printf("Resumo módulo %s: %d/%d casos aprovados\n", suite->module, suite->passed, suite->total);
}

