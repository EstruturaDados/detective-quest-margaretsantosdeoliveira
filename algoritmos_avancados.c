#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura 
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; 
    struct Sala *direita;  
} Sala;

/**
 * @brief Cria uma nova sala 
 * @param nome nome da sala.
 * @return 
 */
Sala *criarSala(char *nome) {
    Sala *novaSala = (Sala *)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        
        strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
        novaSala->nome[sizeof(novaSala->nome) - 1] = '\0'; 
        // Inicializa os ponteiros dos filhos como NULL
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    } else {
        perror("Erro na alocação de memória para a sala");
    }
    return novaSala;
}

/**
 * @brief Permite a navegação do jogador pela mansão 
 *
 
 *
 * @param salaAtual ponteiro para a sala onde o jogador está
 */
void explorarSalas(Sala *salaAtual) {
    char escolha;

    // exploração continua
    while (salaAtual != NULL) {
        printf("\nVocê está em: **%s**\n", salaAtual->nome);

        
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Você chegou a um beco sem saida. Sua exploração terminou.\n");
            break; // Sai do loop
        }

        printf("Escolha o próximo caminho:\n");
        // caminhos disponíveis
        if (salaAtual->esquerda != NULL) {
            printf("  [**e**] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [**d**] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [**s**] Sair da exploração\n");
        printf("Sua escolha (e/d/s): ");

        // escolha do usuário
        if (scanf(" %c", &escolha) != 1) {
            
            break;
        }

        // Processa a escolha do jogador
        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("Não tem caminho a esquerda. Escolha novamente.\n");
                }
                break;
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("Não tem caminho a direita. Escolha novamente.\n");
                }
                break;
            case 's':
            case 'S':
                printf("Saindo da exploração. Nos vemos na próxima!\n");
                salaAtual = NULL; // Termina o loop
                break;
            default:
                printf("Opção inválida. Tente 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
                // Permanece na mesma sala e depois solicita nova escolha
        }
    }
}

/**
 * @brief Função principal para montar o mapa da mansão e iniciar a exploração
 */
int main() {
    printf("Seja bem-vindo ao Detective Quest!\n");
    printf("O mapa da mansão está sendo carregado. Aguarde...\n\n");

    

    // Nível 0 
    Sala *hallEntrada = criarSala("Hall de entrada");

    // Nível 1
    hallEntrada->esquerda = criarSala("Sala de estar");
    hallEntrada->direita = criarSala("Cozinha");

    // Nível 2
    Sala *salaEstar = hallEntrada->esquerda;
    salaEstar->esquerda = criarSala("Biblioteca");
    salaEstar->direita = criarSala("Sala de jantar");

    Sala *cozinha = hallEntrada->direita;
    cozinha->esquerda = criarSala("Dispensa");
    cozinha->direita = criarSala("Jardim");

    // Nível 3 
    Sala *salaJantar = salaEstar->direita;
    salaJantar->esquerda = criarSala("Quarto principal"); 
  

    printf("Mapa carregado com sucesso. Começando a exploração no hall de entrada.\n");
    
    // Iniciar a navegação 
    explorarSalas(hallEntrada);

    
    // liberação da árvore:
    if (salaJantar->esquerda) free(salaJantar->esquerda); // quarto principal
    if (salaEstar->esquerda) free(salaEstar->esquerda);   // biblioteca
    if (salaEstar->direita) free(salaEstar->direita);     // sala de jantar
    if (cozinha->esquerda) free(cozinha->esquerda);       // dispensa
    if (cozinha->direita) free(cozinha->direita);         // jardim
    if (hallEntrada->esquerda) free(hallEntrada->esquerda); // sala de estar
    if (hallEntrada->direita) free(hallEntrada->direita);    // cozinha
    if (hallEntrada) free(hallEntrada);                      // hall de entrada

    printf("\nProcesso encerrado. Memória (das salas) liberada.\n");

    return 0;
}