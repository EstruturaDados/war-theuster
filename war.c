#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_MISSOES 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

void exibirMissao(char* missao) {
    printf("Sua missão: %s\n", missao);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) contador++;
            else contador = 0;
            if (contador >= 3) return 1;
        }
    } else if (strcmp(missao, "Eliminar todas as tropas vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Nao pode atacar territorio da mesma cor!\n");
        return;
    }
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("%s (A:%d) atacou %s (D:%d)\n", atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Ataque bem-sucedido!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Ataque falhou!\n");
        atacante->tropas--;
    }
}

void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < tamanho; i++)
        printf("%s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
}

void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {
    srand(time(NULL));

    char* missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Controlar todos os territorios azuis",
        "Manter ao menos 2 territorios com 5 tropas",
        "Conquistar o territorio Central"
    };

    Territorio* mapa = malloc(MAX_TERRITORIOS * sizeof(Territorio));

    strcpy(mapa[0].nome, "Norte");
    strcpy(mapa[0].cor, "azul");
    mapa[0].tropas = 3;

    strcpy(mapa[1].nome, "Sul");
    strcpy(mapa[1].cor, "vermelho");
    mapa[1].tropas = 2;

    strcpy(mapa[2].nome, "Leste");
    strcpy(mapa[2].cor, "azul");
    mapa[2].tropas = 4;

    strcpy(mapa[3].nome, "Oeste");
    strcpy(mapa[3].cor, "verde");
    mapa[3].tropas = 3;

    strcpy(mapa[4].nome, "Central");
    strcpy(mapa[4].cor, "vermelho");
    mapa[4].tropas = 5;

    char* missaoJogador = malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, MAX_MISSOES);
    exibirMissao(missaoJogador);

    int opcao;
    do {
        exibirMapa(mapa, MAX_TERRITORIOS);
        printf("\n1 - Atacar\n2 - Verificar Missao\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;
            printf("Escolha atacante (0-4): ");
            scanf("%d", &a);
            printf("Escolha defensor (0-4): ");
            scanf("%d", &d);
            atacar(&mapa[a], &mapa[d]);
        } else if (opcao == 2) {
            if (verificarMissao(missaoJogador, mapa, MAX_TERRITORIOS))
                printf("Missao cumprida! Voce venceu!\n");
            else
                printf("Missao ainda nao cumprida.\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
