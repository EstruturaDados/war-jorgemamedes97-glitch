// Jogo de WAR - Nível Mestre ( Implementando a funcionalidade de missão estratégica)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        do {
            printf("Digite a quantidade de tropas: ");
            scanf("%d", &mapa[i].tropas);
        } while (mapa[i].tropas < 1);
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== LISTA DE TERRITÓRIOS =====\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Você não pode atacar territórios do mesmo exército!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\n[ERRO] O atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n%s (%s) atacou %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq > dadoDef) {
        printf(">> O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        int tropasParaMover = atacante->tropas / 2;
        if (tropasParaMover < 1) tropasParaMover = 1;
        defensor->tropas = tropasParaMover;
        atacante->tropas -= tropasParaMover;
    } else {
        printf(">> O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Função para atribuir missão ao jogador
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *destino = (char*) malloc(strlen(missoes[indice]) + 1);
    strcpy(*destino, missoes[indice]);
}

// Função para exibir missão (passagem por valor)
void exibirMissao(char* missao) {
    printf("\nSua missão é: %s\n", missao);
}

// Função simples de verificação de missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo: missão "Conquistar território vermelho"
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") != 0) {
                return 0; // Ainda não conquistou todos os vermelhos
            }
        }
        return 1; // Missão cumprida
    }
    // Para outras missões, adicionar lógica específica
    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// Main
int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Vetor de missões
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminate todas as tropas da cor vermelha",
        "Ter 5 tropas em um único território",
        "Conquistar território azul e verde",
        "Controlar todos os territórios do jogador adversário"
    };
    int totalMissoes = 5;

    char* missaoJogador;
    atribuirMissao(&missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    int opcao, atq, def;
    do {
        printf("\n--- MENU ---\n1 - Exibir territórios\n2 - Atacar\n0 - Sair\nEscolha: ");
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

                if (verificarMissao(missaoJogador, mapa, n)) {
                    printf("\nPARABÉNS! Você cumpriu sua missão!\n");
                    opcao = 0; // encerra o jogo
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
