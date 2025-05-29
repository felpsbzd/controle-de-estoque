#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>

int carregarProdutos(Produto lista[], int maxTam) {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    int count = 0;
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    while (fscanf(arquivo, "%d;%d;%[^;];%f\n",
                  &lista[count].codigo,
                  &lista[count].quantidade,
                  lista[count].nome,
                  &lista[count].valor) == 4) {
        count++;
        if (count >= maxTam) break;
                  }
    fclose(arquivo);
    printf("Produto criado com sucesso.\n");
    printf("quantidade de produtos: %d\n", count);
    return count; // retorna quantos produtos foram lidos
}


bool buscarProdutoPorCodigo(int codigo, char *linhaEncontrada) {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    char linha[100];
    char codigoStr[20];
    sprintf(codigoStr, "%d", codigo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        char linhaCopia[100];
        strcpy(linhaCopia, linha);
        linhaCopia[strcspn(linhaCopia, "\n")] = '\0';

        char *token = strtok(linhaCopia, ";");
        if (token && strcmp(token, codigoStr) == 0) {
            strcpy(linhaEncontrada, linha);
            fclose(arquivo);
            return true;
        }
    }

    fclose(arquivo);
    return false;
}


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
    FILE *arquivo = fopen("../data/produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
int codigo,quantidade;
    float valor;
    char nome[50];
    char linha[50];
    bool existe = false;
do {
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    existe = buscarProdutoPorCodigo(codigo,linha);
    if (existe == true) {
         printf("Codigo do produto ja existe\n");
    }
}while (existe == true);
    printf("Digite o quantidade do produto: ");
    scanf("%d", &quantidade);
    printf("Digite o nome do produto: ");
    scanf("%s", nome);
    printf("Digite o valor do produto: ");
    scanf("%f", &valor);

    fprintf(arquivo, "%d;%d;%s;%.2f\n", codigo, quantidade,nome,valor);
    fclose(arquivo);
}
void consultarProduto() {
    int codigo;
    char linhaOriginal[100];
    char linha[100];
    int cod, qtd;
    float preco;
    char nome[50];

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    if (buscarProdutoPorCodigo(codigo, linhaOriginal)) {
        strcpy(linha, linhaOriginal); // Copia para não modificar o original

        if (sscanf(linha, "%d;%d;%[^;];%f", &cod, &qtd, nome, &preco) == 4) {
            printf("\n=== Produto Encontrado ===\n");
            printf("Codigo: %d\n", cod);
            printf("Quantidade: %d\n", qtd);
            printf("Nome: %s\n", nome);
            printf("Preco: %.2f\n", preco);
        } else {
            printf("Erro ao interpretar os dados do produto.\n");
        }
    } else {
        printf("Produto nao encontrado.\n");
    }
}









