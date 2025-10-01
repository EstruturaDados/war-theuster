#include <stdio.h>
#include <string.h>


// Definição da struct Territorio
typedef struct {
    char nome[30];  
    char cor[10];   
    int tropas;     
} Territorio;

int main(){
//vetor para armazenar 5 Territorio
    Territorio territorios[5];
    int i;

    printf("=== Cadastro de Territorios ===\n");
    // Entrada dos dados
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        scanf("%29s", territorios[i].nome);

        printf("Cor do exército: ");
        scanf("%9s", territorios[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    //Exibição dos dados
    printf("\n--- Territorios cadastrados ---\n");
    for (i = 0; i < 5; i++) {
        printf(" Territorio %d:\n", i + 1);
        printf("  Nome  : %s\n", territorios[i].nome);
        printf("  Cor   : %s\n", territorios[i].cor);
        printf("  Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
