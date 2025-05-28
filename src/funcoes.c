#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


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





