#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Funções de ordenação
int bubbleSort(Componente *vetor, int n);
int insertionSort(Componente *vetor, int n);
int selectionSort(Componente *vetor, int n);

// Funções de busca e utilitárias
int buscaBinaria(Componente *vetor, int n, char *chave, int *comparacoes);
void listarComponentes(Componente *vetor, int n);
void cadastrarComponentes(Componente *vetor, int *n);
void limparBuffer();

// Função principal
int main() {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    clock_t inicio, fim;
    double tempo_exec;
    int comparacoes = 0;
    char chave[30];

    do {
        printf("\n=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave (Binária - por nome)\n");
        printf("6. Listar componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &total);
                break;

            case 2:
                inicio = clock();
                comparacoes = bubbleSort(componentes, total);
                fim = clock();
                tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
                printf("\nOrdenado por nome (Bubble Sort).\nComparações: %d | Tempo: %.5f s\n", comparacoes, tempo_exec);
                break;

            case 3:
                inicio = clock();
                comparacoes = insertionSort(componentes, total);
                fim = clock();
                tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
                printf("\nOrdenado por tipo (Insertion Sort).\nComparações: %d | Tempo: %.5f s\n", comparacoes, tempo_exec);
                break;

            case 4:
                inicio = clock();
                comparacoes = selectionSort(componentes, total);
                fim = clock();
                tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
                printf("\nOrdenado por prioridade (Selection Sort).\nComparações: %d | Tempo: %.5f s\n", comparacoes, tempo_exec);
                break;

            case 5:
                printf("\nDigite o nome do componente-chave a buscar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                int pos;
                comparacoes = 0;
                pos = buscaBinaria(componentes, total, chave, &comparacoes);

                if (pos != -1)
                    printf("Componente encontrado na posição %d! (Comparações: %d)\n", pos + 1, comparacoes);
                else
                    printf("Componente não encontrado. (Comparações: %d)\n", comparacoes);
                break;

            case 6:
                listarComponentes(componentes, total);
                break;

            case 0:
                printf("Encerrando sistema... Obrigado por jogar!\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ====== Funções Auxiliares ======

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarComponentes(Componente *vetor, int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite máximo de componentes atingido!\n");
        return;
    }

    printf("\nQuantos componentes deseja cadastrar? ");
    int qtd;
    scanf("%d", &qtd);
    limparBuffer();

    for (int i = 0; i < qtd && *n < MAX_COMPONENTES; i++) {
        printf("\n=== Componente %d ===\n", *n + 1);
        printf("Nome: ");
        fgets(vetor[*n].nome, sizeof(vetor[*n].nome), stdin);
        vetor[*n].nome[strcspn(vetor[*n].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(vetor[*n].tipo, sizeof(vetor[*n].tipo), stdin);
        vetor[*n].tipo[strcspn(vetor[*n].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &vetor[*n].prioridade);
        limparBuffer();

        (*n)++;
    }

    printf("\nCadastro concluído com sucesso!\n");
}

void listarComponentes(Componente *vetor, int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// ====== Algoritmos de Ordenação ======

int bubbleSort(Componente *vetor, int n) {
    int comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

int insertionSort(Componente *vetor, int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
            comparacoes++;
        }
        vetor[j + 1] = chave;
    }
    return comparacoes;
}

int selectionSort(Componente *vetor, int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }
        if (menor != i) {
            Componente temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
        }
    }
    return comparacoes;
}

// ====== Busca Binária ======

int buscaBinaria(Componente *vetor, int n, char *chave, int *comparacoes) {
    int inicio = 0, fim = n - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        (*comparacoes)++;

        int cmp = strcmp(chave, vetor[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}
