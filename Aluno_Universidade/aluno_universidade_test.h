#ifndef ALUNO_UNIVERSIDADE_TEST_H
#define ALUNO_UNIVERSIDADE_TEST_H

/**
 * @brief Executa todos os testes do módulo Aluno x Universidade
 * 
 * Aplica os seguintes casos de teste:
 * - link_aluno_universidade: parâmetro inválido, aluno inexistente, sucesso
 * - get_universidade_aluno: parâmetro inválido, aluno sem vínculo, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo e dos módulos relacionados
 * (Aluno e Universidade) antes e após a execução.
 */
void run_tests_aluno_universidade(void);

#endif

