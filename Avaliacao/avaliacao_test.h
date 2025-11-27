#ifndef AVALIACAO_TEST_H
#define AVALIACAO_TEST_H

/**
 * @brief Executa todos os testes do módulo Avaliação
 * 
 * Aplica os seguintes casos de teste:
 * - create_avaliacao: parâmetro inválido, sucesso, duplicada, nota inválida
 * - get_avaliacoes_professor: parâmetro inválido, sem registros, sucesso
 * - get_all_avaliacoes: parâmetro inválido, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo e dos módulos relacionados
 * (Aluno e Professor) antes e após a execução.
 */
void run_tests_avaliacao(void);

#endif

