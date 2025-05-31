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


void atualizarEstoque(Produto lista[], int *tamanho) {
    printf("\n--- Atualizar Estoque ---\n");

    int codigoBusca;
    int quantidadeAtualizar;
    int indiceEncontrado;
    int c; // Para limpeza de buffer

    if (*tamanho == 0) {
        printf("Nenhum produto cadastrado para atualizar.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja atualizar: ");
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
    scanf("%d", &codigoBusca);

    printf("Digite a quantidade a adicionar (+) ou remover (-): ");
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
    scanf("%d", &quantidadeAtualizar);

    indiceEncontrado = buscarProdutoPorCodigo(codigoBusca, lista, tamanho); // Usa a nova busca

    if (indiceEncontrado == -1) {
        printf("Erro: Produto com codigo %d nao encontrado.\n", codigoBusca);
        return;
    }

    // Atualiza no vetor
    int quantidadeAtual = lista[indiceEncontrado].quantidade;
    int novaQuantidade = quantidadeAtual + quantidadeAtualizar;

    if (novaQuantidade < 0) {
        printf("\nAviso: Operacao deixaria o estoque negativo (ficaria %d). Ajustando para 0.\n", novaQuantidade);
        novaQuantidade = 0;
    }

    lista[indiceEncontrado].quantidade = novaQuantidade;
    printf("Estoque em memoria atualizado para %d unidades.\n", novaQuantidade);

    // Salva no arquivo
    salvarProdutosNoArquivo(lista, *tamanho);
    printf("Estoque do produto %d atualizado com sucesso no arquivo!\n", codigoBusca);
}


void listarProdutos(Produto lista[], int tamanho) { // Recebe tamanho por valor, não ponteiro
    printf("\n======= LISTA DE PRODUTOS =========\n");

    if (tamanho == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        printf("---------------------------------------------\n");
        return;
    }

    printf("Codigo | Nome           | Quantidade | Preco \n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%-6d | %-14s | %-10d | R$%.2f\n",
               lista[i].codigo,
               lista[i].nome,
               lista[i].quantidade,
               lista[i].valor);
    }
    printf("---------------------------------------------\n");
}


void removerProduto(Produto lista[], int *tamanho) {
    printf("\n--- Remover Produto ---\n");

    int codigoBusca;
    int indiceRemover;
    int c;

    if (*tamanho == 0) {
        printf("Nenhum produto cadastrado para remover.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja remover: ");
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
    scanf("%d", &codigoBusca);

    indiceRemover = buscarProdutoPorCodigo(codigoBusca, lista, tamanho);

    if (indiceRemover == -1) {
        printf("Erro: Produto com codigo %d nao encontrado.\n", codigoBusca);
        return;
    }

    // Confirmação (Opcional, mas recomendado)
    printf("Tem certeza que deseja remover o produto '%s' (Codigo: %d)? (s/n): ", lista[indiceRemover].nome, codigoBusca);
    char confirmacao;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
    scanf(" %c", &confirmacao); // Espaço antes de %c ignora espaços/newlines

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remocao cancelada.\n");
        return;
    }

    // Lógica de Remoção: Desloca os elementos posteriores uma posição para trás
    for (int i = indiceRemover; i < (*tamanho - 1); i++) {
        lista[i] = lista[i + 1];


    }

    // Diminui o tamanho lógico do vetor
    (*tamanho)--;

    printf("Produto %d removido da memoria.\n", codigoBusca);

    // Salva o estado atualizado no arquivo
    salvarProdutosNoArquivo(lista, *tamanho =+ 1);
    printf("Alteracoes salvas no arquivo.\n");
}