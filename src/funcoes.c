#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>



void mostrarMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Consultar Produto\n");
    printf("3. Atualizar Estoque\n");
    printf("4. Listar Produtos\n");
    printf("5. Remover Produto\n");
    printf("6. Sair\n");
}
bool validarCodigoProduto(int codigo) {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    char linha[50];
    char *token;
    bool existe = false;
    char codigoProduto[50];
    sprintf(codigoProduto, "%d", codigo);
    while (fgets(linha, 50, arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        token = strtok(linha, ";");
        if(token!=NULL) {
            if(strcmp(token, codigoProduto)==0) {
                existe = true;
                fclose(arquivo);
                return existe;
            }
        }




    }
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
    bool existe = false;
do {
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    existe = validarCodigoProduto(codigo);
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

    fprintf(arquivo, "%d;%d;%s;%2.f\n", codigo, quantidade,nome,valor);
    fclose(arquivo);
}
void consultarProduto () {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    int codigo;
    char linha[50];
    char *token;
    bool existe = false;
    char codigoProduto[50];
    char linha_copia[50];
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    sprintf(codigoProduto, "%d", codigo);

    while (fgets(linha, 50, arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(linha_copia, linha);
        token = strtok(linha_copia, ";");
        if(token!=NULL) {
            if(strcmp(token, codigoProduto)==0) {
                existe = true;
                printf("Produto encontrado!\n");
                printf("Aqui esta as informacoes dele: %s\n", linha);
                fclose(arquivo);
                return;
            }

        }

    }
    printf("produto nao existe\n");
    fclose(arquivo);
    }






