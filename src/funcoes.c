#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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




void atualizarEstoque() {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    if  (arquivo == NULL) {
        printf("Erro: Nenhum produto encontrado.\n");
    }

    int codigo;
    printf("Digite o codigo do produto: \n");
    scanf("%d", &codigo);

    //armazenamento de dados
    char linhas[100][100]; //deve armazenar at]e 100 produtos com 100 caracteres!
    int totalLinhas = 0;
    int  encontrado = 0;
    int indiceAlvo = -1;
    int novaQuantidade = -1;
    char operacao;

    //leitura do arquivo
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; //remove newline
        strcpy(linhas[totalLinhas], linha);

        //extrair codigo da linha atual
        char *token = strtok(linha, ";");
        if (token != NULL) {
            int codAtual = atoi(token);

            //verifica se realmente eh o produto procurado
            if (codAtual == codigo) {
                encontrado = 1;
                indiceAlvo = totalLinhas;

                //obter a quantidade atual do produto
                token = strtok(NULL, ";");
                int quantAtual = atoi(token);

                //solicitar operacao
                printf("Operacao: Escolha A= Adicionar / R= Remover");
                scanf("%c", &operacao);

                int quantidade;
                printf("Quantidade: ");
                scanf("%d", &quantidade);

                //processar operacao
                if (operacao == 'A' || operacao == 'R') {
                    novaQuantidade = quantAtual + quantidade;
                    printf("Adicionadas %d unidades. Novo estoque: %d\n", quantidade, novaQuantidade);
                }
                else if (operacao == 'R' || operacao == 'r') {
                    if (quantidade > quantAtual) {
                        printf("Erro: Estoque insuficiente! Estoque atual: %d\n", quantAtual);
                        fclose(arquivo);
                    }
                    novaQuantidade = quantAtual - quantidade;
                    printf("Retiradas %d unidades. Novo estoque: %d\n", quantidade, novaQuantidade);
                }
                else {
                    printf("Operacao invalida!\n");
                    fclose(arquivo);
                }
            }
        }
        fclose(arquivo);

        if (!encontrado) {
            printf("Produto nao encontrado!\n");
        }

        //Atualizar a linha do roduto
        if (indiceAlvo != -1 && novaQuantidade >= 0) {
            char *token = strtok(linhas[indiceAlvo], ";");
            char codStr[20], nome[50], valorStr[20];

            strcpy(codStr, token);
            token = strtok(NULL,)
        }
    }
}

void listarProdutos() {
    FILE *arquivo = fopen("../data/produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado ainda.\n");
    }

    printf("\n======= LISTA DE PRODUTOS =========\n");
    printf("Codigo | Nome  |  Quantidade | Preco \n");
    printf("-------------------------------------\n");

    int codigo, quantidade;
    char nome[50];
    float valor;
    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        linha [strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%d;%d;%[^;];%f", &codigo, &quantidade, nome, &valor);

        printf("%-6d | %-12s | %-10d | R$%.2f\n", codigo, nome, quantidade, valor);
    }
    printf("------------------------------------\n");
    fclose(arquivo);
}





