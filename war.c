// Jogo de WAR - Nível Aventureiro (com ataque e alocação dinâmica)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);  

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== LISTA DE TERRITÓRIOS =====\n");
    for (int i = 0; i < n; i++) {
        printf("\n[%d] Nome: %s\n", i, mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função para simular ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Você não pode atacar territórios do mesmo exército!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\n[ERRO] O atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s (%s) atacou %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">> O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);      // muda de dono
        defensor->tropas = atacante->tropas / 2;   // metade das tropas vão
        atacante->tropas = atacante->tropas / 2;   // metade fica
    } else {
        printf(">> O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // aleatoriedade para dados

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int opcao, atq, def;
    do {
        printf("\n--- MENU ---\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                exibirTerritorios(mapa, n);
                break;
            case 2:
                exibirTerritorios(mapa, n);
                printf("Escolha o índice do território atacante: ");
                scanf("%d", &atq);
                printf("Escolha o índice do território defensor: ");
                scanf("%d", &def);

                if (atq >= 0 && atq < n && def >= 0 && def < n) {
                    atacar(&mapa[atq], &mapa[def]);
                } else {
                    printf("\n[ERRO] Índices inválidos!\n");
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
