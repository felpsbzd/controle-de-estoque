cmake_minimum_required(VERSION 3.25)
project(controle_de_estoque C)

set(CMAKE_C_STANDARD 11)

# Inclui o diretório de headers
include_directories(include)

# Define os arquivos fonte do projeto
add_executable(controle_de_estoque
        src/main.c
        src/funcoes.c)
