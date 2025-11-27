#ifndef DISCIPLINA_TEST_H
#define DISCIPLINA_TEST_H

/**
 * @brief Executa todos os testes do módulo Disciplina
 * 
 * Aplica os seguintes casos de teste:
 * - create_disciplina: sucesso, duplicada, parâmetro inválido
 * - read_disciplina: parâmetro inválido, não encontrada, sucesso
 * - update_disciplina: parâmetro inválido, não encontrada, sucesso
 * - delete_disciplina: parâmetro inválido, sucesso, não encontrada
 * - get_all_disciplinas: parâmetro inválido, vazio, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo antes e após a execução.
 */
void run_tests_disciplina(void);

#endif

