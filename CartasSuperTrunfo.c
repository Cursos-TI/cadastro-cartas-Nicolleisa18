#include <stdio.h>
#include <string.h>

#define MAX_CIDADES 5

struct Cidade {
    char estado[50];
    int codigo;
    char nome[50];
    int populacao;
    double pib;
    double area;
    int pontos_turisticos;
    double densidade_populacional;
    double pib_per_capita;
};

double calcular_densidade(double populacao, double area) {
    return populacao / area;
}

double calcular_pib_per_capita(double pib, int populacao) {
    return pib / populacao;
}

void registrar_cidade(struct Cidade* cidade) {
    printf("Digite o código da cidade: ");
    scanf("%d", &cidade->codigo);
    getchar();

    printf("Digite o nome da cidade: ");
    fgets(cidade->nome, 50, stdin);
    cidade->nome[strcspn(cidade->nome, "\n")] = 0;

    printf("Digite o estado da cidade: ");
    fgets(cidade->estado, 50, stdin);
    cidade->estado[strcspn(cidade->estado, "\n")] = 0;

    printf("Digite a população da cidade: ");
    scanf("%d", &cidade->populacao);

    printf("Digite o PIB da cidade (em bilhões): ");
    scanf("%lf", &cidade->pib);

    printf("Digite a área da cidade (em km²): ");
    scanf("%lf", &cidade->area);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);

    cidade->densidade_populacional = calcular_densidade(cidade->populacao, cidade->area);
    cidade->pib_per_capita = calcular_pib_per_capita(cidade->pib, cidade->populacao);
}

void exibir_informacoes(struct Cidade cidade) {
    printf("\nCidade: %s (Código: %d)\n", cidade.nome, cidade.codigo);
    printf("Estado: %s\n", cidade.estado);
    printf("População: %d\n", cidade.populacao);
    printf("PIB: R$ %.2f bilhões\n", cidade.pib);
    printf("Área: %.2f km²\n", cidade.area);
    printf("Pontos Turísticos: %d\n", cidade.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", cidade.densidade_populacional);
    printf("PIB per capita: R$ %.2f\n", cidade.pib_per_capita);
}

void salvar_em_arquivo(struct Cidade cidade, FILE *arquivo) {
    fprintf(arquivo, "Código: %d\n", cidade.codigo);
    fprintf(arquivo, "Nome: %s\n", cidade.nome);
    fprintf(arquivo, "Estado: %s\n", cidade.estado);
    fprintf(arquivo, "População: %d\n", cidade.populacao);
    fprintf(arquivo, "PIB: R$ %.2f bilhões\n", cidade.pib);
    fprintf(arquivo, "Área: %.2f km²\n", cidade.area);
    fprintf(arquivo, "Pontos Turísticos: %d\n", cidade.pontos_turisticos);
    fprintf(arquivo, "Densidade Populacional: %.2f hab/km²\n", cidade.densidade_populacional);
    fprintf(arquivo, "PIB per capita: R$ %.2f\n", cidade.pib_per_capita);
    fprintf(arquivo, "------------------------------\n");
}

int main() {
    struct Cidade cidades[MAX_CIDADES];
    FILE *arquivo = fopen("cidades.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    for (int i = 0; i < MAX_CIDADES; i++) {
        printf("\nCadastro da cidade %d:\n", i + 1);
        registrar_cidade(&cidades[i]);
        exibir_informacoes(cidades[i]);
        salvar_em_arquivo(cidades[i], arquivo);
    }

    fclose(arquivo);
    printf("\nAs informações foram salvas no arquivo 'cidades.txt'.\n");
    return 0;
}
