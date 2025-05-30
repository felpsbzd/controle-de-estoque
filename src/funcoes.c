#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>

void salvarProdutosNoArquivo(Produto lista[], int tamanho) {

    FILE *arquivo = fopen("../data/produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os produtos no arquivo! Verifique o caminho ou permissoes.\n");
        return;
    }


    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d;%d;%s;%.2f\n",
                lista[i].codigo,
                lista[i].quantidade,
                lista[i].nome,
                lista[i].valor);
    }

    fclose(arquivo);
}

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
    printf("lista de produtos criada com sucesso.\n");
    printf("quantidade de produtos: %d\n", count);
    return count; // retorna quantos produtos foram lidos
}


    int buscarProdutoPorCodigo(int codigo, Produto lista[],int *tamanho) {
        int indice;
    for (indice = 0; indice < *tamanho; indice++) {
        if (lista[indice].codigo == codigo) {
            return indice;
        }
    }

        return -1;
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



void cadastrarProduto(Produto lista[], int *tamanho) {
    if (*tamanho >= MAX_PRODUTOS) { // Verifica se há espaço no vetor
        printf("Estoque cheio! Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    int codigo;
    int indiceExistente;
    int c;

    do {
        printf("Digite o codigo do produto: ");
        // Limpa o buffer do teclado antes de ler o código
        // Isso é uma boa prática para evitar problemas com entradas anteriores.

        while ((c = getchar()) != '\n' && c != EOF); //

        scanf("%d", &codigo);
        indiceExistente = buscarProdutoPorCodigo(codigo, lista, tamanho);
        if (indiceExistente != -1) {
             printf("Codigo do produto ja existe. Por favor, digite outro.\n");
        }
    } while (indiceExistente != -1);


    lista[*tamanho].codigo = codigo;

    printf("Digite a quantidade do produto: ");
    // Correção: scanf precisa do endereço do membro da struct
    scanf("%d", &lista[*tamanho].quantidade);

    // Limpa o buffer do teclado novamente ANTES de ler a string com fgets
    // Crucial para que fgets leia o nome corretamente e não a quebra de linha do scanf anterior.
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome do produto: ");
    // Usar fgets para ler strings com espaços.
    // O sizeof garante que não haverá buffer overflow.
    fgets(lista[*tamanho].nome, sizeof(lista[*tamanho].nome), stdin);
    // Remove o '\n' que fgets pode ter lido (se couber no buffer)
    lista[*tamanho].nome[strcspn(lista[*tamanho].nome, "\n")] = '\0';

    printf("Digite o valor do produto: ");

    scanf("%f", &lista[*tamanho].valor);

    (*tamanho)++;

    printf("Produto cadastrado com sucesso!\n");

    salvarProdutosNoArquivo(lista, *tamanho);
}
void consultarProduto(Produto lista[], int *tamanho) {
    int codigo;
    int indiceEncontrado;
    int c;
    printf("Digite o codigo do produto: ");


    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer do teclado antes de ler o código

    scanf("%d", &codigo);


    indiceEncontrado = buscarProdutoPorCodigo(codigo, lista, tamanho);

    if (indiceEncontrado != -1) {
        // Acessa o produto diretamente no vetor usando o índice
        printf("\n=== Produto Encontrado ===\n");
        printf("Codigo: %d\n", lista[indiceEncontrado].codigo);
        printf("Quantidade: %d\n", lista[indiceEncontrado].quantidade);
        printf("Nome: %s\n", lista[indiceEncontrado].nome);
        printf("Preco: %.2f\n", lista[indiceEncontrado].valor);
    } else {
        printf("Produto nao encontrado.\n");
    }
}









