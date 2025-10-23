#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================
// ESTRUTURA PRINCIPAL
// ==========================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ==========================
// PROTÓTIPOS DAS FUNÇÕES
// ==========================
void inserirItem(Item mochila[], int *quantidadeAtual);
void removerItem(Item mochila[], int *quantidadeAtual);
void listarItens(Item mochila[], int quantidadeAtual);
void buscarItem(Item mochila[], int quantidadeAtual);

// ==========================
// FUNÇÃO PRINCIPAL
// ==========================
int main() {
    Item mochila[10]; // Vetor com capacidade para até 10 itens
    int quantidadeAtual = 0;
    int opcao;

    printf("=====================================\n");
    printf("     SISTEMA DE MOCHILA DO JOGADOR  \n");
    printf("=====================================\n\n");

    do {
        printf("Menu de Opcoes:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &quantidadeAtual);
                break;
            case 2:
                removerItem(mochila, &quantidadeAtual);
                break;
            case 3:
                listarItens(mochila, quantidadeAtual);
                break;
            case 4:
                buscarItem(mochila, quantidadeAtual);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

// ==========================
// FUNÇÃO: INSERIR ITEM
// ==========================
void inserirItem(Item mochila[], int *quantidadeAtual) {
    if (*quantidadeAtual >= 10) {
        printf("\nA mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    // Adiciona o novo item ao vetor
    mochila[*quantidadeAtual] = novoItem;
    (*quantidadeAtual)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// ==========================
// FUNÇÃO: REMOVER ITEM
// ==========================
void removerItem(Item mochila[], int *quantidadeAtual) {
    if (*quantidadeAtual == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int i, encontrado = 0;

    for (i = 0; i < *quantidadeAtual; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;

            // Desloca os itens subsequentes para "fechar o buraco"
            for (int j = i; j < *quantidadeAtual - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*quantidadeAtual)--;

            printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila.\n");
    }
}

// ==========================
// FUNÇÃO: LISTAR ITENS
// ==========================
void listarItens(Item mochila[], int quantidadeAtual) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (quantidadeAtual == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < quantidadeAtual; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// ==========================
// FUNÇÃO: BUSCAR ITEM
// ==========================
void buscarItem(Item mochila[], int quantidadeAtual) {
    if (quantidadeAtual == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int i, encontrado = 0;

    for (i = 0; i < quantidadeAtual; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila.\n");
    }
}
