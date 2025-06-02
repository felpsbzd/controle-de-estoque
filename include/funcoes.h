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
void cadastrarProduto(Produto lista[], int *tamanho);
void consultarProduto(Produto lista[], int *tamanho);
void atualizarEstoque(Produto lista[], int *tamanho);;
void listarProdutos(Produto lista[], int tamanho);
void removerProduto(Produto lista[], int *tamanho);

//funções auxiliares
#define MAX_PRODUTOS  100
int carregarProdutos(Produto lista[], int maxTam);
void salvarProdutosNoArquivo(Produto lista[], int tamanho);
int buscarProdutoPorCodigo(int codigo, Produto lista[], int *tamanho);
int buscarProdutoBinario(int codigo, Produto lista[], int tamanho);
void ordenarLista (Produto lista[], int tamanho);
#endif //FUNCOES_H
