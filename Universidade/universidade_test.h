#ifndef UNIVERSIDADE_TEST_H
#define UNIVERSIDADE_TEST_H

/**
 * @brief Executa todos os testes do módulo Universidade
 * 
 * Aplica os seguintes casos de teste:
 * - get_universidades: vazio, sucesso
 * - create_universidade: sucesso, duplicada, parâmetro inválido
 * - read_universidade: parâmetro inválido, não encontrada, sucesso
 * - delete_universidade: parâmetro inválido, sucesso, não encontrada
 * 
 * Os testes preservam e restauram o estado original do módulo antes e após a execução.
 */
void run_tests_universidade(void);

#endif

