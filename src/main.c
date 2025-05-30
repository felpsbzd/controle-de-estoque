#include <stdio.h>
#include "funcoes.h"
#include <stdlib.h>
#include <string.h>


int main() {
    int opcao;
    Produto listaDeProdutos[MAX_PRODUTOS];
    int tamanho = carregarProdutos(listaDeProdutos, MAX_PRODUTOS);
    do {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Cadastrar Produto...\n");
                cadastrarProduto(listaDeProdutos, &tamanho);
                break;
            case 2:
                printf("Consultar Produto...\n");
                consultarProduto(listaDeProdutos,&tamanho);
                break;
            case 3:
                printf("Atualizar Estoque...\n");
                atualizarEstoque(listaDeProdutos, &tamanho);
                break;
            case 4:
                printf("Listar Produtos...\n");
                listarProdutos(listaDeProdutos, tamanho);
                break;
            case 5:
                printf("Remover Produto...\n");
                removerProduto(listaDeProdutos, &tamanho);
                break;
            case 6:
                printf("Saindo...\n");
                salvarProdutosNoArquivo(listaDeProdutos, tamanho);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 6);

    return 0;
}