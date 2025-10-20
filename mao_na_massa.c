#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio t[5]; // Vetor para armazenar 5 territórios
    int i;

    // Introdução do programa
    printf("=================================\n");
    printf("SISTEMA DE CADASTRO DE TERRITORIOS\n");
    printf("=================================\n\n");
    printf("Vamos cadastrar 5 territorios que farao parte do nosso mundo.\n\n");

    for (i = 0; i < 5; i++) {
        printf("=== Cadastrando Territorio %d ===\n\n", i + 1);

        // Entrada do nome do território
        printf("Nome do Territorio: ");
        scanf("%s", t[i].nome);

        // Entrada da cor do exército
        printf("Cor do Exercito: ");
        scanf("%s", t[i].cor);

        // Entrada do número de tropas
        printf("Numero de Tropas: ");
        scanf("%d", &t[i].tropas);

        // Exibe resumo imediatamente após o cadastro
        printf("\n--- Territorio %d Cadastrado com Sucesso ---\n", i + 1);
        printf("Nome do Territorio: %s\n", t[i].nome);
        printf("Cor do Exercito: %s\n", t[i].cor);
        printf("Numero de Tropas: %d\n", t[i].tropas);
        printf("-------------------------------------------\n\n");
    }

    /*
        Exibição final
        --------------
        Após o término do cadastro, o sistema exibe todos os territórios
        registrados de forma organizada.
    */
    printf("=================================\n");
    printf("RESUMO FINAL DOS TERRITORIOS\n");
    printf("=================================\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", t[i].nome);
        printf("  Cor do Exercito: %s\n", t[i].cor);
        printf("  Numero de Tropas: %d\n\n", t[i].tropas);
    }

    printf("Cadastro concluido com sucesso!\n");
    return 0;
}
