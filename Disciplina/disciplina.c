#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"

tpDisciplina *listaDisciplinas = NULL;
int qtdDisciplinas = 0;

// definir qtd disciplinas, listadisciplinas

int read_Disciplina(char *codigo, tpDisciplina *tpDisciplina) {
    // Verifica parâmetros inválidos
    if (codigo == NULL || tpDisciplina || strlen(codigo)) {
        return 2; // Parâmetro inválido -> caso de teste 3
    }
    for(int i = 0; i < qtdDisciplinas; i++) {
        if(strcmp(listaDisciplinas[i].codigo, codigo) == 0) {
            *tpDisciplina = listaDisciplina[i]; // copia os dados para o ponteiro
            return 0; // Ok (Disciplina encontrada) -> caso de teste 1
        }
    
    return 1; // Disciplina não encontrada -> caso de teste 2
}

int delete_Disciplina(char *codigo){
    if(codigo == NULL || strlen(codigo) == 0) {
        return 2; // Parâmetro inválido -> caso de teste 7
    }

    if(qtdDisciplinas == 0) {
        return 1; // Falha ao deletar (lista vazia) -> caso de teste 6
    }

    for(int i = 0; i < qtdDisciplinas; i++) {
        if(strcmp(listaDisciplinas[i].codigo, codigo) == 0) {
            // Encontrou a disciplina, remover da lista
            for(int j = i; j < qtdDisciplinas - 1; j++) {
                listaDisciplinas[j] = listaDisciplinas[j+1];
            }
            qtdDisciplina--;

            // Reduz o tamanho do array
            tpDisciplina *tmp = realloc(listaDisciplinas, qtdDisciplinas * sizeof(tpDisciplina));
            if(tmp != NULL || qtdDisciplinas == 0) {
                listaDisciplinas = tmp;
            } else {
                return 99; // Cancelamento por exceção -> caso de teste 8
            }
            listarDisciplina();
            return 0; // Ok -> caso de teste 5
        }
    }

    return 1; // Disciplina não encontrada -> caso de teste 6
}

int create_Disciplina(tpDisciplina *tpDisciplina) {
    return 0;
}

int update_Disciplinas(char *codigo, tpDisciplina *tpDisciplina) {
    return 0;
}
