# Controle de Estoque para Pequenos Negócios

[Link para o Repositório no GitHub](https://github.com/felpsbzd/controle-de-estoque.git)

Este projeto é um sistema simples de controle de estoque desenvolvido em linguagem C, focado em demonstrar conceitos de estruturas de dados (vetores ordenados), algoritmos de busca (busca binária) e manipulação de arquivos para persistência de dados. [cite: 2]

## Funcionalidades

O sistema oferece as seguintes funcionalidades para gerenciamento de produtos: [cite: 3]

* **Cadastro de Produtos**: Adiciona novos produtos ao estoque.
* **Consulta de Produtos**: Busca e exibe detalhes de um produto existente.
* **Atualização de Estoque**: Permite adicionar ou remover unidades de um produto.
* **Listagem de Produtos**: Exibe todos os produtos cadastrados no estoque.
* **Remoção de Produtos**: Exclui um produto do estoque.
* **Armazenamento em Arquivo Texto**: Todos os dados são persistidos em um arquivo de texto (`produtos.txt`).

## Como Compilar e Executar

Para compilar e executar o programa, siga os passos abaixo:

1.  **Pré-requisitos**: Certifique-se de ter um compilador C (como o GCC) instalado em seu sistema.

2.  **Navegar até o diretório do projeto**:
    Abra o terminal ou prompt de comando e navegue até a pasta raiz do projeto onde os arquivos `main.c`, `funcoes.c`, `funcoes.h` estão localizados (ou onde você os extraiu, se baixou de um repositório). Assumindo a estrutura de pastas `src/` e `data/`:

    ```bash
    cd seu_diretorio_do_projeto
    ```

3.  **Compilar o código**:
    Utilize o compilador GCC para compilar os arquivos fonte. [cite: 3]

    ```bash
    gcc src/main.c src/funcoes.c -o controle
    ```
    * `src/main.c`: Contém a função principal do programa.
    * `src/funcoes.c`: Contém a implementação das funções de manipulação do estoque.
    * `-o controle`: Define o nome do arquivo executável de saída como `controle`.

4.  **Executar o programa**:
    Após a compilação bem-sucedida, você pode executar o programa:

    ```bash
    ./controle
    ```

## Guia de Uso das Funcionalidades

Ao executar o programa, um menu principal será exibido. Você pode escolher uma opção digitando o número correspondente e pressionando `Enter`.

### Fluxo Geral

1.  Ao iniciar, o programa tenta carregar os produtos do arquivo `data/produtos.txt` para a memória. Se o arquivo não existir ou estiver vazio, o estoque começará vazio.
2.  Todas as operações são realizadas em um vetor de produtos mantido em memória.
3.  Após cada operação de modificação (Cadastro, Atualização de Estoque, Remoção), o estado atualizado do estoque em memória é **salvo automaticamente** de volta no arquivo `data/produtos.txt`.
4.  Ao escolher a opção "Sair", o programa também garante que o estoque final seja salvo no arquivo antes de encerrar.

### Detalhes das Opções do Menu

1.  **Cadastrar Produto**
    * Solicita: Código do produto (inteiro), Quantidade (inteiro), Nome (string, pode conter espaços), Valor (número decimal).
    * **Validação**: O sistema verifica se o código do produto já existe. Se sim, ele pedirá um novo código até que seja único.
    * **Ordenação**: O novo produto é inserido na lista de forma ordenada crescente pelo código, mantendo a eficiência da busca binária.
    * **Persistência**: O estoque é salvo no arquivo após o cadastro.

2.  **Consultar Produto**
    * Solicita: Código do produto a ser consultado.
    * **Busca Eficiente**: Utiliza busca binária para localizar o produto rapidamente no vetor ordenado.
    * Exibe: Código, Quantidade, Nome e Preço do produto, se encontrado. Caso contrário, informa que o produto não foi encontrado.

3.  **Atualizar Estoque**
    * Solicita: Código do produto a ser atualizado.
    * Solicita: Quantidade a adicionar (valor positivo) ou remover (valor negativo).
    * **Lógica**: A quantidade informada é somada/subtraída da quantidade atual do produto.
    * **Validação**: Evita que a quantidade do estoque fique negativa, ajustando para 0 se o resultado for menor que zero.
    * **Persistência**: O estoque é salvo no arquivo após a atualização.

4.  **Listar Produtos**
    * Exibe: Uma lista formatada de todos os produtos atualmente no estoque.
    * **Ordenação**: Os produtos são exibidos em ordem crescente de código, pois a lista é mantida ordenada.
    * Informa se não há produtos cadastrados.

5.  **Remover Produto**
    * Solicita: Código do produto a ser removido.
    * **Confirmação**: Solicita uma confirmação (s/n) antes de prosseguir com a remoção.
    * **Lógica**: Se confirmado, o produto é removido do vetor e os produtos seguintes são deslocados para preencher o espaço.
    * **Persistência**: O estoque é salvo no arquivo após a remoção.

6.  **Sair**
    * Exibe a mensagem "Saindo...".
    * **Persistência**: Garante que o estado final do estoque seja salvo no arquivo `data/produtos.txt` antes de encerrar o programa.

## Estrutura de Arquivos Relevantes

* `src/main.c`: Ponto de entrada do programa, contém o menu principal e o loop de interação.
* `src/funcoes.c`: Implementa todas as funções de gerenciamento de produtos (cadastro, consulta, atualização, listagem, remoção, ordenação e manipulação de arquivos).
* `include/funcoes.h`: Contém as declarações das funções e a definição da `struct Produto`.
* `data/produtos.txt`: Arquivo de texto utilizado para armazenar os dados dos produtos de forma persistente.

---
## Apoie o Projeto! Contribua com o Desenvolvimento! 🚀✨

Se você gostou deste projeto e ele te foi útil, considere apoiar seu desenvolvimento contínuo. Sua contribuição é um grande incentivo e me ajuda a dedicar mais tempo para aprimorá-lo!

Você pode apoiar o projeto através da minha chave Pix:

**Chave Pix:** `86981849385` 🙏💖

<img src="https://c.tenor.com/pyJra-hS6WQAAAAd/tenor.gif" alt="Pica-Pau pedindo doação" width="250"/>

---
