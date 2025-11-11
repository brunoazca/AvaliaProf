#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tpDisciplina {
    char *codigo;
    char *nome;
} tpDisciplina; 

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
    return 0;
}

int create_Disciplina(tpDisciplina *tpDisciplina) {
    return 0;
}

int update_Disciplinas(char *codigo, tpDisciplina *tpDisciplina) {
    return 0;
}
