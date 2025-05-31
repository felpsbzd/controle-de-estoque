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
void ordenarLista (Produto lista[], int tamanho) {
    bool trocou;
    int i;
    int j;
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
    ordenarLista(lista, count);
    fclose(arquivo);
    printf("lista de produtos criada com sucesso.\n");
    printf("quantidade de produtos: %d\n", count);
    return count; // retorna quantos produtos foram lidos
}


    int buscarProdutoPorCodigo(int codigo, Produto lista[],int *tamanho) {
    return buscarProdutoBinario(codigo, lista, *tamanho);
    }
int buscarProdutoBinario(int codigo, Produto lista[], int tamanho) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2; // Evita overflow para grandes 'esquerda' e 'direita'

        // Verifica se o elemento do meio é o código procurado
        if (lista[meio].codigo == codigo) {
            return meio; // Produto encontrado, retorna o índice
        }

        // Se o código procurado for maior, ignore a metade esquerda
        if (lista[meio].codigo < codigo) {
            esquerda = meio + 1;
        }
        // Se o código procurado for menor, ignore a metade direita
        else {
            direita = meio - 1;
        }
    }

    return -1; // Produto não encontrado
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

    // --- Limpeza do buffer inicial (boa prática) ---
    while ((c = getchar()) != '\n' && c != EOF);

    do {
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);
        // Usamos buscarProdutoPorCodigo (que agora usa busca binaria)
        indiceExistente = buscarProdutoPorCodigo(codigo, lista, tamanho); // Passa o vetor e o ponteiro para o tamanho
        if (indiceExistente != -1) { // Se retornar um índice diferente de -1, o código já existe
             printf("Codigo do produto ja existe. Por favor, digite outro.\n");
        }
    } while (indiceExistente != -1);

    // --- Cria um novo produto temporário com os dados lidos ---
    Produto novoProduto;
    novoProduto.codigo = codigo;

    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);

    // Limpa o buffer do teclado novamente ANTES de ler a string com fgets
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Digite o valor do produto: ");
    scanf("%f", &novoProduto.valor);

    // --- Lógica para Inserção Ordenada ---
    // Encontra a posição correta para inserir o novo produto mantendo a ordem crescente por código
    int i = *tamanho - 1; // Começa do último elemento preenchido
    // Percorre a lista de trás para frente, enquanto o elemento atual for maior que o novo produto
    // e ainda estiver dentro dos limites do array
    while (i >= 0 && lista[i].codigo > novoProduto.codigo) {
        lista[i + 1] = lista[i]; // Desloca o elemento para a direita
        i--;
    }

    // Insere o novo produto na posição encontrada (i + 1)
    lista[i + 1] = novoProduto;

    // --- Incrementa o número de produtos após o cadastro bem-sucedido ---
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


void listarProdutos(Produto lista[], int tamanho) {
    printf("\n======= LISTA DE PRODUTOS ========\n");

    if (tamanho == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        printf("-----------------------------------------------------------\n");
        return;
    }




    printf("Codigo | Nome                     | Quantidade | Preco \n");
    printf("-----------------------------------------------------------\n");

    //Imprimir a CÓPIA ORDENADA
    for (int i = 0; i < tamanho; i++) {

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
    int c; // Variável para a limpeza do buffer

    // 1. Verifica se há produtos na lista
    if (*tamanho == 0) {
        printf("Nenhum produto cadastrado para remover.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja remover: ");
    // 2. Limpa o buffer antes de ler o código
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%d", &codigoBusca);

    // 3. Busca o produto pelo código
    indiceRemover = buscarProdutoPorCodigo(codigoBusca, lista, tamanho);

    // 4. Verifica se o produto foi encontrado
    if (indiceRemover == -1) {
        printf("Erro: Produto com codigo %d nao encontrado.\n", codigoBusca);
        return;
    }

    // 5. Confirmação do usuário
    printf("Tem certeza que deseja remover o produto '%s' (Codigo: %d)? (s/n): ", lista[indiceRemover].nome, codigoBusca);
    char confirmacao;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer antes de ler a confirmação
    scanf(" %c", &confirmacao); // O espaço antes de %c ignora qualquer whitespace (como newlines)

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remocao cancelada.\n");
        return;
    }

    // 6. Lógica de Remoção: Desloca os elementos posteriores uma posição para trás
    // Percorre do índice do produto a ser removido até o penúltimo elemento
    for (int i = indiceRemover; i < (*tamanho - 1); i++) {
        lista[i] = lista[i + 1]; // Move o elemento seguinte para a posição atual
    }

    // 7. Diminui o tamanho lógico do vetor
    (*tamanho)--;

    printf("Produto %d removido da memoria.\n", codigoBusca);

    // 8. Salva o estado atualizado no arquivo
    // CORREÇÃO CRÍTICA AQUI: Use *tamanho (o novo tamanho)
    salvarProdutosNoArquivo(lista, *tamanho); // <-- CORRIGIDO!
    printf("Alteracoes salvas no arquivo.\n");
}