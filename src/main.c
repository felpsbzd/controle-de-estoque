#include <stdio.h>
#include "funcoes.h"
#include <stdlib.h>

int main() {
    int opcao;
    do {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Cadastrar Produto...\n");
                cadastrarProduto();
                break;
            case 2:
                printf("Consultar Produto...\n");
                break;
            case 3:
                printf("Atualizar Estoque...\n");
                break;
            case 4:
                printf("Listar Produtos...\n");
                break;
            case 5:
                printf("Remover Produto...\n");
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 6);

    return 0;
}