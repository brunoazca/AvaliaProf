#ifndef DISCIPLINA_UNIVERSIDADE_TEST_H
#define DISCIPLINA_UNIVERSIDADE_TEST_H

/**
 * @brief Executa todos os testes do módulo Disciplina x Universidade
 * 
 * Aplica os seguintes casos de teste:
 * - link_disciplina_universidade: parâmetro inválido, disciplina inexistente, sucesso
 * - get_disciplinas_universidade: parâmetro inválido, nenhuma disciplina, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo e dos módulos relacionados
 * (Disciplina e Universidade) antes e após a execução.
 */
void run_tests_disciplina_universidade(void);

#endif

