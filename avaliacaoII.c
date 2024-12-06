#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Aluno: Ruan David da Silva
Ra: 22051922
Professor: Fábio Oliveira Guimarães
Matéria: Algoritmos de Alta Performance
*/

#define TAMANHO_TABELA 10
#define PRIMO 7 // Numero primo p segundo hash.

typedef struct {
	int ip;
	bool ocupado;
} EntradaHash;

EntradaHash tabela_hash[TAMANHO_TABELA];

// Inicializa a tabela hash
void inicializar_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash[i].ip = -1;  // Marca como vazio
        tabela_hash[i].ocupado = false;
    }
}

// Primeira função hash
int hash1(int ip) {
    return ip % TAMANHO_TABELA;
}

// Segunda função hash
int hash2(int ip) {
    return PRIMO - (ip % PRIMO);
}

// Insere um IP na tabela hash
void inserir(int ip) {
    int indice = hash1(ip);
    int passo = hash2(ip);
    int colisoes = 0;

    while (tabela_hash[indice].ocupado) {
        colisoes++;
        indice = (indice + passo) % TAMANHO_TABELA;

        if (colisoes >= TAMANHO_TABELA) {
            printf("Erro: Tabela cheia. Não é possível inserir o IP %d.\n", ip);
            return;
        }
    }

    tabela_hash[indice].ip = ip;
    tabela_hash[indice].ocupado = true;
    printf("IP %d inserido no índice %d após %d colisões.\n", ip, indice, colisoes);
}

// Busca um IP na tabela hash
void buscar(int ip) {
    int indice = hash1(ip);
    int passo = hash2(ip);
    int colisoes = 0;

    while (tabela_hash[indice].ocupado && tabela_hash[indice].ip != ip) {
        colisoes++;
        indice = (indice + passo) % TAMANHO_TABELA;

        if (colisoes >= TAMANHO_TABELA) {
            printf("IP %d não encontrado.\n", ip);
            return;
        }
    }

    if (tabela_hash[indice].ocupado && tabela_hash[indice].ip == ip) {
        printf("IP %d encontrado no índice %d após %d passos.\n", ip, indice, colisoes);
    } else {
        printf("IP %d não encontrado.\n", ip);
    }
}

// Exibe a tabela hash
void exibir_tabela() {
    printf("\nTabela Hash:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        if (tabela_hash[i].ocupado) {
            printf("Índice %d: IP %d\n", i, tabela_hash[i].ip);
        } else {
            printf("Índice %d: Vazio\n", i);
        }
    }
}

int main() {
    inicializar_tabela();

    int opcao, ip;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir IP\n");
        printf("2. Buscar IP\n");
        printf("3. Exibir Tabela\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o IP (como inteiro): ");
                scanf("%d", &ip);
                inserir(ip);
                break;

            case 2:
                printf("Digite o IP para buscar: ");
                scanf("%d", &ip);
                buscar(ip);
                break;

            case 3:
                exibir_tabela();
                break;

            case 4:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}
