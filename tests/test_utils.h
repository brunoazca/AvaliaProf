#ifndef TEST_UTILS_H
#define TEST_UTILS_H

typedef struct {
    const char *module;
    int total;
    int passed;
} TestSuite;

void test_utils_reset_overall(void);
void test_utils_get_overall(int *total, int *passed);

void test_suite_init(TestSuite *suite, const char *module);
void test_suite_expect(TestSuite *suite, const char *case_name, int expected, int actual);
void test_suite_finish(TestSuite *suite);

#endif

