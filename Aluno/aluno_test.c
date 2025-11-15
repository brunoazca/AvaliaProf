#include <stdio.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "aluno.h"

static tpAluno criarAluno(const char *cpf, const char *nome, const char *email) {
    tpAluno aluno;
    memset(&aluno, 0, sizeof(tpAluno));
    snprintf(aluno.cpf, sizeof(aluno.cpf), "%s", cpf);
    snprintf(aluno.nome, sizeof(aluno.nome), "%s", nome);
    snprintf(aluno.email, sizeof(aluno.email), "%s", email);
    snprintf(aluno.senha, sizeof(aluno.senha), "%s", "123456");
    snprintf(aluno.curso, sizeof(aluno.curso), "%s", "Computação");
    snprintf(aluno.universidade, sizeof(aluno.universidade), "%s", "UFTestes");
    return aluno;
}

void run_tests_aluno(void) {
    TestSuite suite;
    test_suite_init(&suite, "Aluno");

    tpAluno *estadoOriginal = NULL;
    int qtdOriginal = 0;
    aluno_detach_state(&estadoOriginal, &qtdOriginal);

    tpAluno alunoBase = criarAluno("00011122233", "Aluno Teste", "teste@aluno.com");
    tpAluno alunoAux = criarAluno("44455566677", "Aluno Aux", "aux@aluno.com");

    test_suite_expect(&suite, "registrar - sucesso", 0, registrar(&alunoBase));
    test_suite_expect(&suite, "registrar - duplicado", 1, registrar(&alunoBase));
    test_suite_expect(&suite, "registrar - parâmetro inválido", 2, registrar(NULL));
    aluno_set_forced_return(99);
    test_suite_expect(&suite, "registrar - exceção forçada", 99, registrar(&alunoAux));

    tpAluno alunoLido;
    test_suite_expect(&suite, "read_aluno - parâmetro inválido", 2, read_aluno(NULL, &alunoLido));
    test_suite_expect(&suite, "read_aluno - não encontrado", 1, read_aluno("CPF_INEXISTENTE", &alunoLido));
    test_suite_expect(&suite, "read_aluno - sucesso", 0, read_aluno(alunoBase.cpf, &alunoLido));
    aluno_set_forced_return(99);
    test_suite_expect(&suite, "read_aluno - exceção forçada", 99, read_aluno(alunoBase.cpf, &alunoLido));

    test_suite_expect(&suite, "login - parâmetro inválido", 2, login(NULL, NULL));
    test_suite_expect(&suite, "login - credenciais inválidas", 1, login(alunoBase.email, "senha_errada"));
    test_suite_expect(&suite, "login - sucesso", 0, login(alunoBase.email, alunoBase.senha));
    aluno_set_forced_return(99);
    test_suite_expect(&suite, "login - exceção forçada", 99, login(alunoBase.email, alunoBase.senha));

    test_suite_expect(&suite, "delete_aluno - parâmetro inválido", 2, delete_aluno(NULL));
    test_suite_expect(&suite, "delete_aluno - sucesso", 0, delete_aluno(alunoBase.cpf));
    test_suite_expect(&suite, "delete_aluno - não encontrado", 1, delete_aluno(alunoBase.cpf));
    aluno_set_forced_return(99);
    test_suite_expect(&suite, "delete_aluno - exceção forçada", 99, delete_aluno(alunoBase.cpf));

    tpAluno *estadoTestes = NULL;
    int qtdTestes = 0;
    aluno_detach_state(&estadoTestes, &qtdTestes);
    aluno_free_state(estadoTestes);
    aluno_attach_state(estadoOriginal, qtdOriginal);

    test_suite_finish(&suite);
}

