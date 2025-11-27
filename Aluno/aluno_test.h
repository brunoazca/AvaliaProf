#ifndef ALUNO_TEST_H
#define ALUNO_TEST_H

/**
 * @brief Executa todos os testes do módulo Aluno
 * 
 * Aplica os seguintes casos de teste:
 * - registrar: sucesso, duplicado, parâmetro inválido
 * - read_aluno: parâmetro inválido, não encontrado, sucesso
 * - login: parâmetro inválido, credenciais inválidas, sucesso
 * - delete_aluno: parâmetro inválido, sucesso, não encontrado
 * - get_all_alunos: parâmetro inválido, vazio, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo antes e após a execução.
 */
void run_tests_aluno(void);

#endif

