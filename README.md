# **Controle de Estoque**

Este é um sistema básico de controle de estoque desenvolvido em linguagem C. O programa foi originalmente criado para resolver uma problemática acadêmica da **Universidade de Pernambuco (UPE)**, com foco na organização, gerenciamento e autenticação de usuários para manipulação de itens de estoque.

O código é modular, utiliza arquivos para persistência de dados e fornece funcionalidades como login de usuários, cadastro de itens no estoque e relatórios detalhados.

---

## **Funcionalidades**

1. **Cadastro de Usuários**:
   - Criação de novos usuários com nome e senha.
   - Verificação se o usuário já existe no sistema.

2. **Login de Usuários**:
   - Sistema de autenticação para garantir acesso seguro.

3. **Cadastro de Entrada de Itens**:
   - Registro de itens no estoque, incluindo nome, quantidade e números de série.

4. **Cadastro de Saída de Itens**:
   - Registro da retirada de itens, permitindo informar números de série específicos.

5. **Relatórios do Estoque**:
   - **Relatório Simples**:
     - Exibe apenas os itens presentes no estoque e suas quantidades consolidadas.
   - **Relatório Completo**:
     - Exibe os itens no estoque, suas quantidades e os números de série disponíveis.

---

## **Estrutura de Arquivos**

O código foi dividido em vários arquivos para facilitar a organização e manutenção. Abaixo estão descritos cada um deles e suas funções:

### **1. `main.c`**
Arquivo principal que inicializa o programa e gerencia a navegação entre as opções. Ele fornece o menu principal com as seguintes opções:
- Cadastro de novos usuários.
- Login de usuários existentes.
- Menu de controle de estoque após o login (entrada, saída e relatórios).

### **2. `usuarios.c`**
Contém a implementação das funções relacionadas ao gerenciamento de usuários:
- `cadastrarUsuario()`: Registra novos usuários no sistema.
- `logarUsuario()`: Valida o login de usuários existentes.

Os dados de usuários são armazenados no arquivo `usuarios.txt`.

### **3. `usuarios.h`**
Cabeçalho correspondente ao `usuarios.c`. Declara as funções do módulo de usuários para que possam ser utilizadas em outros arquivos (como `main.c`).

### **4. `estoque.c`**
Contém a implementação das funções relacionadas ao gerenciamento de estoque:
- `cadastrarEntrada()`: Permite adicionar itens ao estoque com seus números de série.
- `cadastrarSaida()`: Registra a saída de itens e atualiza o estoque.
- `visualizarEstoque()`: Gera um relatório simples com os itens atualmente no estoque e suas quantidades.
- `relatorioCompleto()`: Gera um relatório detalhado com os itens e seus números de série presentes no estoque.

Os dados de estoque são armazenados no arquivo `estoque.txt`.

### **5. `estoque.h`**
Cabeçalho correspondente ao `estoque.c`. Declara as funções do módulo de estoque para que possam ser acessadas em outros arquivos.

### **6. `usuarios.txt`**
Banco de dados simples (arquivo texto) para armazenar os dados dos usuários cadastrados. O formato do arquivo é:

usuario senha admin admin123 joao 12345

### **7. `estoque.txt`**
Banco de dados simples (arquivo texto) que armazena o histórico de entradas e saídas de itens no estoque. O formato do arquivo é:

cadeira 4 Entrada 001,002,003,004 
cadeira 2 Saida 001,004 
mesa 3 Entrada 005,006,007

---

## **Como Compilar o Código**

Para compilar o código, é necessário ter um compilador C instalado (como GCC). Siga os passos:

1. Abra o terminal ou prompt de comando na pasta onde estão os arquivos do código.
2. Compile os arquivos juntos para gerar o executável:
   ```bash
   gcc -o controle_estoque main.c usuarios.c estoque.c

Execute o programa:

./controle_estoque

Exemplo de Uso
Passo 1: Cadastro de Usuário
Ao iniciar o programa, escolha a opção para cadastrar um novo usuário.
Insira um nome de usuário e senha.
Passo 2: Login
Faça login com o nome de usuário e senha cadastrados.
Passo 3: Gerenciar Estoque
Após o login, você terá acesso ao menu de controle de estoque:
Cadastrar entrada de itens: Forneça o nome do item, quantidade e números de série.
Cadastrar saída de itens: Forneça o nome do item, quantidade e números de série.
Visualizar relatórios:
Relatório Simples: Mostra os itens no estoque com suas quantidades.
Relatório Completo: Mostra os itens no estoque com números de série.

Relatórios

Relatório Simples
Apresenta os itens no estoque e suas quantidades consolidadas:

--- Itens no Estoque ---
Item: Cadeira, Quantidade: 2
Item: Mesa, Quantidade: 3

Relatório Completo
Exibe os itens no estoque, suas quantidades e os números de série disponíveis:

--- Relatório Completo ---
Item: Cadeira, Quantidade: 2, Números de Série: 002,003
Item: Mesa, Quantidade: 3, Números de Série: 005,006,007

Por Que Este Sistema Foi Criado?
Este programa foi desenvolvido como uma solução para uma problemática proposta pela Universidade de Pernambuco (UPE). A ideia era construir um sistema simples e eficiente que pudesse:

Gerenciar o acesso de usuários.
Controlar o fluxo de itens em um estoque.
Oferecer relatórios úteis para análise rápida.

Contribuição e Uso

Sinta-se à vontade para usar, modificar e expandir este código. Ele foi projetado para ser um ponto de partida simples e funcional. Se você tiver melhorias, contribuições ou ideias, sinta-se à vontade para compartilhar!