#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdbool.h>

void salvarProdutosNoArquivo(Produto lista[], int tamanho) {
    // abre o arquivo e verifica se ele está vazio
    FILE *arquivo = fopen("../data/produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os produtos no arquivo! Verifique o caminho ou permissoes.\n");
        return;
    }

    //escreve no arquivo as informações coletadas do vetor listaDeProdutos
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d;%d;%s;%.2f\n",
                lista[i].codigo,
                lista[i].quantidade,
                lista[i].nome,
                lista[i].valor);
    }

    fclose(arquivo);
}
void ordenarLista (Produto lista[], int tamanho) {
    bool trocou;
    int i;
    int j;
    //ordena a lista em ordem Crescente com base no código do Produto
    for (i = 0; i < tamanho - 1; i++) {
        trocou = false;
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (lista[j].codigo > lista[j + 1].codigo) {
                Produto temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = true;
            }
        }
        if (!trocou) {
            break;
        }
    }
}
int carregarProdutos(Produto lista[], int maxTam) {
    FILE *arquivo = fopen("../data/produtos.txt", "r"); //le o arquivo
    int count = 0;
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    //escreve no vetor de produtos, os itens lidos do arquivo .txt
    while (fscanf(arquivo, "%d;%d;%[^;];%f\n",
                  &lista[count].codigo,
                  &lista[count].quantidade,
                  lista[count].nome,
                  &lista[count].valor) == 4) {
        count++;
        if (count >= maxTam) break;
                  }
    ordenarLista(lista, count);
    fclose(arquivo);
    printf("lista de produtos criada com sucesso.\n");
    printf("quantidade de produtos: %d\n", count);
    return count; // retorna quantos produtos foram lidos
}


    int buscarProdutoPorCodigo(int codigo, Produto lista[],int *tamanho) { //busca um produto pelo seu código, utilizando uma função auxiliar(buscarProdutoBinario)
    return buscarProdutoBinario(codigo, lista, *tamanho);
    }
//Essa função divide o vetor encontrando o elemento central. Depois disso, ela faz uma comparação com o elemento central do vetor. Se o codigo
//que procuro for igual ao do elemento central do vetor, ele retorna meio(indice do elemento central). Se for maior do que o codigo do elemento do meio, o algoritmo
//descarta os elementos à esquerda do meio e o proprio meio, continuando a busca com a metade direita. Se for menor ele descarta todos os elementos
//à direita do meio, incluindo o meio, continuando a busca apenas com a metade esquerda. O processo se repete até sobrar somente um elemento para ser comparado.
//Caso, este elemento não seja o que estou procurando, retorna -1 e a função encerra
int buscarProdutoBinario(int codigo, Produto lista[], int tamanho) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;


        if (lista[meio].codigo == codigo) {
            return meio;
        }


        if (lista[meio].codigo < codigo) {
            esquerda = meio + 1;
        }

        else {
            direita = meio - 1;
        }
    }

    return -1;
}

void mostrarMenu() { //função que apenas mostra as opções do menu
    printf("\n=== MENU ===\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Consultar Produto\n");
    printf("3. Atualizar Estoque\n");
    printf("4. Listar Produtos\n");
    printf("5. Remover Produto\n");
    printf("6. Sair\n");
}



void cadastrarProduto(Produto lista[], int *tamanho) {
    if (*tamanho >= MAX_PRODUTOS) {//Verifica se o estoque está cheio
        printf("Estoque cheio! Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    int codigo;
    int indiceExistente;
    int c;


    while ((c = getchar()) != '\n' && c != EOF); //Limpa o buffer do teclado

    do {//While repete até que o código seja válido, ou seja que não exista dentro da lista.
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);

        indiceExistente = buscarProdutoPorCodigo(codigo, lista, tamanho);
        if (indiceExistente != -1) {
             printf("Codigo do produto ja existe. Por favor, digite outro.\n");
        }
    } while (indiceExistente != -1);


    Produto novoProduto;
    novoProduto.codigo = codigo;

    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);


    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Digite o valor do produto: ");
    scanf("%f", &novoProduto.valor);


    int i = *tamanho - 1;

    while (i >= 0 && lista[i].codigo > novoProduto.codigo) {//Ele garante que o vetor se mantenha ordenado.
        lista[i + 1] = lista[i];
        i--;
    }


    lista[i + 1] = novoProduto;


    (*tamanho)++;

    printf("Produto cadastrado com sucesso e lista ordenada!\n");

    // Salva todo o vetor no arquivo (agora que ele está ordenado e atualizado)
    salvarProdutosNoArquivo(lista, *tamanho);
}
void consultarProduto(Produto lista[], int *tamanho) {
    int codigo;
    int indiceEncontrado;
    int c;
    printf("Digite o codigo do produto: ");


    while ((c = getchar()) != '\n' && c != EOF);

    scanf("%d", &codigo);


    indiceEncontrado = buscarProdutoPorCodigo(codigo, lista, tamanho);

    if (indiceEncontrado != -1) {

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
    int c;

    if (*tamanho == 0) {//Verifica se a lista está vazia
        printf("Nenhum produto cadastrado para atualizar.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja atualizar: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%d", &codigoBusca);

    printf("Digite a quantidade a adicionar (+) ou remover (-): ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%d", &quantidadeAtualizar);

    indiceEncontrado = buscarProdutoPorCodigo(codigoBusca, lista, tamanho);

    if (indiceEncontrado == -1) {
        printf("Erro: Produto com codigo %d nao encontrado.\n", codigoBusca);
        return;
    }


    int quantidadeAtual = lista[indiceEncontrado].quantidade;
    int novaQuantidade = quantidadeAtual + quantidadeAtualizar;

    if (novaQuantidade < 0) {
        printf("\nAviso: Operacao deixaria o estoque negativo (ficaria %d). Ajustando para 0.\n", novaQuantidade);
        novaQuantidade = 0;
    }

    lista[indiceEncontrado].quantidade = novaQuantidade;
    printf("Estoque em memoria atualizado para %d unidades.\n", novaQuantidade);


    salvarProdutosNoArquivo(lista, *tamanho);
    printf("Estoque do produto %d atualizado com sucesso no arquivo!\n", codigoBusca);
}


void listarProdutos(Produto lista[], int tamanho) {
    printf("\n======= LISTA DE PRODUTOS ========\n");

    if (tamanho == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        printf("-----------------------------------------------------------\n");
        return;
    }




    printf("Codigo | Nome                     | Quantidade | Preco \n");
    printf("-----------------------------------------------------------\n");


    for (int i = 0; i < tamanho; i++) { //imprime todos os produtos contidos na lista de produtos.

        printf("%-6d | %-25s | %-10d | R$%.2f\n",
               lista[i].codigo,
               lista[i].nome,
               lista[i].quantidade,
               lista[i].valor);
    }
    printf("-----------------------------------------------------------\n");
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

    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%d", &codigoBusca);


    indiceRemover = buscarProdutoPorCodigo(codigoBusca, lista, tamanho);


    if (indiceRemover == -1) {
        printf("Erro: Produto com codigo %d nao encontrado.\n", codigoBusca);
        return;
    }


    printf("Tem certeza que deseja remover o produto '%s' (Codigo: %d)? (s/n): ", lista[indiceRemover].nome, codigoBusca);
    char confirmacao;
    while ((c = getchar()) != '\n' && c != EOF);
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remocao cancelada.\n");
        return;
    }



    for (int i = indiceRemover; i < (*tamanho - 1); i++) { //Remove um produto e garante a ordenação
        lista[i] = lista[i + 1];
    }


    (*tamanho)--;

    printf("Produto %d removido da memoria.\n", codigoBusca);


    salvarProdutosNoArquivo(lista, *tamanho);
    printf("Alteracoes salvas no arquivo.\n");
}