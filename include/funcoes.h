//
// Created by ACER on 27/05/2025.
//

#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdbool.h>

typedef struct{
    int codigo;
    int quantidade;
    char nome[50];
    float valor;
} Produto;
void mostrarMenu();
void cadastrarProduto();
void consultarProduto();
void atualizarEstoque();
void listarProdutos();
void removerProduto();
//funções auxiliares
#define MAX_PRODUTOS  100
int carregarProdutos(Produto lista[], int maxTam);
void salvarProdutos(Produto lista[], int qtd);
bool buscarProdutoPorCodigo(int codigo, char *linhaEncontrada);

#endif //FUNCOES_H
