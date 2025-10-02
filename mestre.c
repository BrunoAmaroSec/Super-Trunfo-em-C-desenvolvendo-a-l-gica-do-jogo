#include <stdio.h>
#include <string.h>

// Estrutura que representa uma carta de país
typedef struct {
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica;
    float pibPerCapita;
} Carta;

// Função auxiliar para exibir o menu
void exibirMenu(int excluir) {
    printf("Escolha um atributo:\n");
    if (excluir != 1) printf("1 - Populacao\n");
    if (excluir != 2) printf("2 - Area\n");
    if (excluir != 3) printf("3 - PIB\n");
    if (excluir != 4) printf("4 - Pontos Turisticos\n");
    if (excluir != 5) printf("5 - Densidade Demografica\n");
}

// Função que compara um atributo entre duas cartas
float compararAtributo(Carta c1, Carta c2, int atributo) {
    float valor1, valor2;

    switch(atributo) {
        case 1: // População
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            printf("Populacao -> %s: %d | %s: %d\n", c1.nome, c1.populacao, c2.nome, c2.populacao);
            break;
        case 2: // Área
            valor1 = c1.area;
            valor2 = c2.area;
            printf("Area -> %s: %.2f km² | %s: %.2f km²\n", c1.nome, c1.area, c2.nome, c2.area);
            break;
        case 3: // PIB
            valor1 = c1.pib;
            valor2 = c2.pib;
            printf("PIB -> %s: %.2f trilhoes | %s: %.2f trilhoes\n", 
                   c1.nome, c1.pib/1e12, c2.nome, c2.pib/1e12);
            break;
        case 4: // Pontos turísticos
            valor1 = c1.pontosTuristicos;
            valor2 = c2.pontosTuristicos;
            printf("Pontos Turisticos -> %s: %d | %s: %d\n", c1.nome, c1.pontosTuristicos, c2.nome, c2.pontosTuristicos);
            break;
        case 5: // Densidade (regra invertida)
            valor1 = c1.densidadeDemografica;
            valor2 = c2.densidadeDemografica;
            printf("Densidade Demografica -> %s: %.6f | %s: %.6f\n", c1.nome, valor1, c2.nome, valor2);
            // Inverte a lógica: menor vence -> retornamos valores "negativos" para alinhar à regra geral
            valor1 *= -1;
            valor2 *= -1;
            break;
        default:
            valor1 = valor2 = 0;
            break;
    }
    return valor1 + valor2; // retornamos os valores para soma final
}

int main() {
    // Cadastro de duas cartas
    Carta carta1 = {"Brasil", 214000000, 8515767.0, 2200000000000.0, 50, 0, 0};
    Carta carta2 = {"Argentina", 46000000, 2780400.0, 640000000000.0, 30, 0, 0};

    // Cálculo automático
    carta1.densidadeDemografica = carta1.populacao / carta1.area;
    carta1.pibPerCapita = carta1.pib / carta1.populacao;

    carta2.densidadeDemografica = carta2.populacao / carta2.area;
    carta2.pibPerCapita = carta2.pib / carta2.populacao;

    int escolha1, escolha2;

    printf("=== SUPER TRUNFO - Nivel Mestre ===\n");
    printf("Comparando cartas: %s x %s\n\n", carta1.nome, carta2.nome);

    // Escolha do primeiro atributo
    exibirMenu(0);
    printf("Digite a primeira opcao: ");
    scanf("%d", &escolha1);

    // Escolha do segundo atributo (dinâmico, sem repetir o primeiro)
    exibirMenu(escolha1);
    printf("Digite a segunda opcao: ");
    scanf("%d", &escolha2);

    // Evitar atributos iguais
    if (escolha1 == escolha2) {
        printf("Erro: Voce escolheu o mesmo atributo duas vezes!\n");
        return 1;
    }

    printf("\n=== Comparacao de Atributos ===\n");

    // Comparação dos dois atributos
    float resultado1 = 0, resultado2 = 0;
    float v1, v2;

    // Primeiro atributo
    switch(escolha1) {
        case 1: v1 = carta1.populacao; v2 = carta2.populacao; break;
        case 2: v1 = carta1.area; v2 = carta2.area; break;
        case 3: v1 = carta1.pib; v2 = carta2.pib; break;
        case 4: v1 = carta1.pontosTuristicos; v2 = carta2.pontosTuristicos; break;
        case 5: v1 = -carta1.densidadeDemografica; v2 = -carta2.densidadeDemografica; break;
    }
    resultado1 += v1;
    resultado2 += v2;

    // Mostrar valores do primeiro atributo
    compararAtributo(carta1, carta2, escolha1);

    // Segundo atributo
    switch(escolha2) {
        case 1: v1 = carta1.populacao; v2 = carta2.populacao; break;
        case 2: v1 = carta1.area; v2 = carta2.area; break;
        case 3: v1 = carta1.pib; v2 = carta2.pib; break;
        case 4: v1 = carta1.pontosTuristicos; v2 = carta2.pontosTuristicos; break;
        case 5: v1 = -carta1.densidadeDemografica; v2 = -carta2.densidadeDemografica; break;
    }
    resultado1 += v1;
    resultado2 += v2;

    // Mostrar valores do segundo atributo
    compararAtributo(carta1, carta2, escolha2);

    // Resultado final com operador ternário
    printf("\n=== Resultado Final ===\n");
    printf("Soma dos atributos -> %s: %.2f | %s: %.2f\n", carta1.nome, resultado1, carta2.nome, resultado2);

    (resultado1 > resultado2) 
        ? printf("Vencedor: %s!\n", carta1.nome)
        : (resultado2 > resultado1) 
            ? printf("Vencedor: %s!\n", carta2.nome)
            : printf("Empate!\n");

    return 0;
}
