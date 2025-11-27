#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tests/test_utils.h"
#include "aluno.h"
#include "aluno_test.h"
#include "../Universidade/universidade.h"
#include "../Aluno_Universidade/aluno_universidade.h"

void run_tests_aluno(void) {
    TestSuite suite;
    test_suite_init(&suite, "Aluno");

    tpAluno *estadoOriginal = NULL;
    int qtdOriginal = 0;
    aluno_detach_state(&estadoOriginal, &qtdOriginal);

    // Detach estados de universidade e relação para testes
    tpUniversidade *estadoUnivOriginal = NULL;
    int qtdUnivOriginal = 0;
    universidade_detach_state(&estadoUnivOriginal, &qtdUnivOriginal);

    void *estadoRelOriginal = NULL;
    int qtdRelOriginal = 0;
    aluno_universidade_detach_state(&estadoRelOriginal, &qtdRelOriginal);

    // Criar universidade para testes
    tpUniversidade universidade = create_instancia_universidade("12.345.678/0001-90", "Universidade Teste");
    create_universidade(&universidade);

    tpAluno alunoBase = create_instancia_aluno("00011122233", "Aluno Teste", "teste@aluno.com");

    test_suite_expect(&suite, "registrar - sucesso", 0, registrar(&alunoBase));
    test_suite_expect(&suite, "registrar - duplicado", 1, registrar(&alunoBase));
    test_suite_expect(&suite, "registrar - parâmetro inválido", 2, registrar(NULL));
    
    // Teste com outro aluno
    tpAluno alunoComUniv = create_instancia_aluno("00011122244", "Aluno Com Univ", "comuniv@aluno.com");
    test_suite_expect(&suite, "registrar - sucesso com outro aluno", 0, registrar(&alunoComUniv));

    tpAluno alunoLido;
    test_suite_expect(&suite, "read_aluno - parâmetro inválido", 2, read_aluno(NULL, &alunoLido));
    test_suite_expect(&suite, "read_aluno - não encontrado", 1, read_aluno("CPF_INEXISTENTE", &alunoLido));
    test_suite_expect(&suite, "read_aluno - sucesso", 0, read_aluno(alunoBase.cpf, &alunoLido));

    test_suite_expect(&suite, "login - parâmetro inválido", 2, login(NULL, NULL));
    test_suite_expect(&suite, "login - credenciais inválidas", 1, login(alunoBase.cpf, "senha_errada"));
    test_suite_expect(&suite, "login - sucesso", 0, login(alunoBase.cpf, alunoBase.senha));

    test_suite_expect(&suite, "delete_aluno - parâmetro inválido", 2, delete_aluno(NULL));
    test_suite_expect(&suite, "delete_aluno - sucesso", 0, delete_aluno(alunoBase.cpf));
    test_suite_expect(&suite, "delete_aluno - não encontrado", 1, delete_aluno(alunoBase.cpf));
    
    // Deletar alunoComUniv para testar lista vazia
    delete_aluno(alunoComUniv.cpf);

    tpAluno *listaAlunos = NULL;
    int quantidadeAlunos = 0;
    test_suite_expect(&suite, "get_all_alunos - parâmetro inválido", 2, get_all_alunos(NULL, &quantidadeAlunos));
    test_suite_expect(&suite, "get_all_alunos - vazio", 1, get_all_alunos(&listaAlunos, &quantidadeAlunos));
    free(listaAlunos);
    listaAlunos = NULL;
    quantidadeAlunos = 0;
    
    tpAluno aluno2 = create_instancia_aluno("11122233344", "Aluno 2", "aluno2@test.com");
    registrar(&aluno2);
    test_suite_expect(&suite, "get_all_alunos - sucesso", 0, get_all_alunos(&listaAlunos, &quantidadeAlunos));
    free(listaAlunos);

    // Restaurar estados
    tpAluno *estadoTestes = NULL;
    int qtdTestes = 0;
    aluno_detach_state(&estadoTestes, &qtdTestes);
    aluno_free_state(estadoTestes);
    aluno_attach_state(estadoOriginal, qtdOriginal);

    void *estadoRelTeste = NULL;
    int qtdRelTeste = 0;
    aluno_universidade_detach_state(&estadoRelTeste, &qtdRelTeste);
    aluno_universidade_free_state(estadoRelTeste);
    aluno_universidade_attach_state(estadoRelOriginal, qtdRelOriginal);

    universidade_free_state(estadoUnivOriginal);
    universidade_attach_state(estadoUnivOriginal, qtdUnivOriginal);

    test_suite_finish(&suite);
}

