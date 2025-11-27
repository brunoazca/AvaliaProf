#ifndef PROFESSOR_TEST_H
#define PROFESSOR_TEST_H

/**
 * @brief Executa todos os testes do módulo Professor
 * 
 * Aplica os seguintes casos de teste:
 * - create_professor: sucesso, duplicado, parâmetro inválido
 * - read_professor: parâmetro inválido, não encontrado, sucesso
 * - update_professor: parâmetro inválido, não encontrado, sucesso
 * - delete_professor: parâmetro inválido, sucesso, não encontrado
 * - get_all_professores: parâmetro inválido, vazio, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo antes e após a execução.
 */
void run_tests_professor(void);

#endif

