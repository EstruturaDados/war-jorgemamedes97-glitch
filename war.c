// Criação do jogo de war nivel novato, implementando um sistema de cadastro de territórios com uso de structs. 

#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {
    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);  

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos territórios cadastrados
    printf("\n===== LISTA DE TERRITORIOS =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}