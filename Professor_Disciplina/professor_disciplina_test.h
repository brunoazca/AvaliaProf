#ifndef PROFESSOR_DISCIPLINA_TEST_H
#define PROFESSOR_DISCIPLINA_TEST_H

/**
 * @brief Executa todos os testes do módulo Professor x Disciplina
 * 
 * Aplica os seguintes casos de teste:
 * - link_professor_disciplina: parâmetro inválido, disciplina ou professor inexistente, sucesso
 * - get_professores_disciplina: parâmetro inválido, disciplina sem professores, sucesso
 * 
 * Os testes preservam e restauram o estado original do módulo e dos módulos relacionados
 * (Disciplina e Professor) antes e após a execução.
 */
void run_tests_professor_disciplina(void);

#endif

