#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =============================
// Estrutura principal do território
// =============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// =============================
// Função para cadastrar territórios
// =============================
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastrando Territorio %d ===\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do Exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n--- Territorio %d Cadastrado com Sucesso ---\n", i + 1);
        printf("Nome: %s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// =============================
// Exibição dos territórios
// =============================
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=================================\n");
    printf("  ESTADO ATUAL DOS TERRITORIOS  \n");
    printf("=================================\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exercito: %s\n", mapa[i].cor);
        printf("  Numero de Tropas: %d\n", mapa[i].tropas);
    }
    printf("\n");
}

// =============================
// Função que simula o ataque
// =============================
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n>>> Ataque de %s (%s) contra %s (%s) <<<\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("Erro: O territorio atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    // Simulando dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= 1;
    } else {
        printf("Resultado: O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }

    printf("\n--- Estado apos o ataque ---\n");
    printf("Atacante: %s (%s) - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}

// =============================
// Função para atribuir uma missão aleatória
// =============================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// =============================
// Função para exibir a missão de um jogador
// =============================
void exibirMissao(char* missao, int jogador) {
    printf("\nMissao do Jogador %d: %s\n", jogador, missao);
}

// =============================
// Função para verificar se a missão foi cumprida
// =============================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de verificação simples:
    // Se o jogador possui mais da metade dos territórios da mesma cor, ele vence.
    int contagem = 0;
    char corVencedora[10] = "Verde"; // Exemplo de cor da missão

    if (strstr(missao, "Conquistar") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corVencedora) == 0) {
                contagem++;
            }
        }
        if (contagem >= tamanho / 2) return 1;
    }

    // Outra lógica simples: eliminar todas as tropas de uma cor
    if (strstr(missao, "Eliminar") != NULL) {
        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) return 1;
    }

    return 0; // Não cumpriu
}

// =============================
// Liberação da memória
// =============================
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
    printf("\nMemoria liberada com sucesso!\n");
}

// =============================
// Função principal
// =============================
int main() {
    srand(time(NULL));
    int n;

    printf("=================================\n");
    printf("   SISTEMA DE TERRITORIOS WAR   \n");
    printf("=================================\n");

    printf("Digite o numero de territorios: ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar metade do mapa",
        "Manter todos os seus territorios por 3 turnos",
        "Conquistar o territorio Asia"
    };
    int totalMissoes = 5;

    // Alocação dinâmica para missões dos jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibe missões apenas no início
    printf("\n--- Missoes Atribuidas ---\n");
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // Loop de jogo
    int opcao, a, d;
    do {
        printf("\nDeseja realizar um ataque? (1 - Sim | 0 - Nao): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\nEscolha o territorio atacante (1-%d): ", n);
            scanf("%d", &a);
            printf("Escolha o territorio defensor (1-%d): ", n);
            scanf("%d", &d);

            if (a < 1 || a > n || d < 1 || d > n || a == d) {
                printf("Escolha invalida!\n");
                continue;
            }

            atacar(&mapa[a - 1], &mapa[d - 1]);
            exibirTerritorios(mapa, n);

            // Verificação de missões
            if (verificarMissao(missaoJogador1, mapa, n)) {
                printf("\n🎉 O Jogador 1 venceu a partida cumprindo sua missao: %s!\n", missaoJogador1);
                break;
            }
            if (verificarMissao(missaoJogador2, mapa, n)) {
                printf("\n🎉 O Jogador 2 venceu a partida cumprindo sua missao: %s!\n", missaoJogador2);
                break;
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    printf("\nPrograma encerrado com sucesso!\n");
    return 0;
}
