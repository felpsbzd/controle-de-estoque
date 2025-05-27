import requests

# =============================
# CONFIGURAÇÕES DO REPOSITÓRIO
# =============================
usuario = "felpsbzd"
repositorio = "controle-de-estoque"
token = "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"  # Substituir pelo token correto

# =============================
# CONFIGURAÇÕES DA API
# =============================
url = f"https://api.github.com/repos/{usuario}/{repositorio}/issues"
headers = {
    "Authorization": f"Bearer {token}",
    "Accept": "application/vnd.github+json"
}

# =============================
# LISTA DE ISSUES
# =============================
issues = [
    {
        "title": "Criar Estrutura Inicial do Repositório",
        "body": "Responsável: Felipe\n- Criar README.md com a descrição inicial do projeto.\n- Adicionar .gitignore configurado para projetos em C."
    },
    {
        "title": "Configurar Pastas e Arquivos Base",
        "body": "Responsável: Marcus\n- Criar arquivos main.c, funcoes.c e funcoes.h.\n- Organizar pastas: /docs, /src, /data (se necessário)."
    },
    {
        "title": "Implementar Menu Principal",
        "body": "Responsável: Felipe\n- Menu interativo com switch case.\n- Opções: Cadastrar Produto, Consultar Produto, Atualizar Estoque, Listar Produtos, Remover Produto, Sair."
    },
    {
        "title": "Cadastro de Produtos",
        "body": "Responsável: Felipe\n- Entrada de Código, Nome, Quantidade e Preço.\n- Validar código único.\n- Salvar em produtos.txt."
    },
    {
        "title": "Consulta de Produto",
        "body": "Responsável: Felipe\n- Consultar produto pelo código.\n- Exibir todas as informações do produto."
    },
    {
        "title": "Atualização de Estoque",
        "body": "Responsável: Marcus\n- Entrada: adicionar unidades.\n- Saída: retirar unidades.\n- Atualizar corretamente no arquivo produtos.txt."
    },
    {
        "title": "Listagem de Produtos",
        "body": "Responsável: Marcus\n- Listar todos os produtos mostrando Código, Nome, Quantidade, Preço."
    },
    {
        "title": "Remoção de Produto",
        "body": "Responsável: Marcus\n- Remover produto a partir do código.\n- Atualizar o arquivo produtos.txt."
    },
    {
        "title": "Leitura e Escrita no Arquivo produtos.txt",
        "body": "Responsável: Ambos (Felipe e Marcus)\n- Implementar função que lê os dados na inicialização.\n- Implementar função que salva dados após cada alteração."
    },
    {
        "title": "Testes Gerais",
        "body": "Responsável: Ambos (Felipe e Marcus)\n- Testar todas as funcionalidades do sistema.\n- Corrigir eventuais bugs encontrados."
    },
    {
        "title": "Criar README Detalhado",
        "body": "Responsável: Marcus\n- Explicar como compilar e executar o programa.\n- Documentar todas as funcionalidades."
    },
    {
        "title": "Criar Fluxograma da Funcionalidade Principal",
        "body": "Responsável: Felipe\n- Criar um fluxograma que represente o funcionamento principal do sistema.\n- Salvar na pasta /docs."
    },
    {
        "title": "Revisão Final e Preparação para Entrega",
        "body": "Responsável: Ambos (Felipe e Marcus)\n- Revisar código, organização, comentários e arquivos.\n- Gerar arquivo .RAR para entrega conforme solicitado pelo professor."
    }
]

# =============================
# CRIANDO AS ISSUES
# =============================
for issue in issues:
    response = requests.post(url, json=issue, headers=headers)
    if response.status_code == 201:
        print(f"Issue criada: {issue['title']}")
    else:
        print(f"Erro ao criar issue '{issue['title']}': {response.status_code} - {response.content.decode()}")
