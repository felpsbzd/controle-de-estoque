#include <stdio.h>
#include "funcoes.h"

void mostrarMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Consultar Produto\n");
    printf("3. Atualizar Estoque\n");
    printf("4. Listar Produtos\n");
    printf("5. Remover Produto\n");
    printf("6. Sair\n");
}
void cadastrarProduto() {
    FILE *arquivo = fopen("../data/produto.txt", "a");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
int codigo,quantidade;
    float valor;
    char nome[50];

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    printf("Digite o quantidade do produto: ");
    scanf("%d", &quantidade);
    printf("Digite o nome do produto: ");
    scanf("%s", nome);
    printf("Digite o valor do produto: ");
    scanf("%f", &valor);

    fprintf(arquivo, "%d;%d;%s;%2.f\n", codigo, quantidade,nome, valor);
    fclose(arquivo);
}
