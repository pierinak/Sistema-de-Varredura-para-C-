# Scanner para Linguagem C-

Analisador léxico (scanner) para a linguagem C-, implementado em C.

## Descrição

Este programa realiza a análise léxica de código fonte escrito na linguagem C-, identificando e classificando cada token encontrado. O scanner reconhece:

- **Palavras reservadas**: `else`, `if`, `int`, `return`, `void`, `while`
- **Operadores aritméticos**: `+`, `-`, `*`, `/`
- **Operadores relacionais**: `<`, `<=`, `>`, `>=`, `==`, `!=`
- **Símbolos especiais**: `=`, `;`, `,`, `(`, `)`, `[`, `]`, `{`, `}`
- **Identificadores**: sequências de letras e dígitos começando com letra
- **Números**: sequências de dígitos
- **Comentários**: `/* ... */` (são ignorados)

## Estrutura do Projeto

```
c-minus-scanner/
├── scanner.c          # Código fonte do scanner
├── README.md          # Este arquivo
├── exemplos/          # Pasta com exemplos de código C-
│   ├── exemplo1.cm
│   ├── exemplo2.cm
│   └── exemplo3.cm

```

## Como Compilar

### Usando GCC diretamente:

```bash
gcc scanner.c -o scanner
```

### Usando o Makefile (opcional):

Crie um arquivo `Makefile`:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

scanner: scanner.c
	$(CC) $(CFLAGS) scanner.c -o scanner

clean:
	rm -f scanner
```

Compile com:
```bash
make
```

## Como Executar

O programa recebe o arquivo fonte C- como argumento de linha de comando:

```bash
./scanner <arquivo_fonte.cm>
```

### Exemplo:

```bash
./scanner exemplo1.cm
```

## Formato de Saída

Para cada token encontrado, o programa exibe:
- **Número da linha** onde o token foi encontrado
- **Tipo do token** (palavra reservada, operador, identificador, etc.)
- **Lexema** (a cadeia de caracteres que representa o token)

### Exemplo de saída:

```
=== Scanner para C- ===
Arquivo: exemplo1.cm

Linha 1: INT          -> "int"
Linha 1: ID           -> "main"
Linha 1: LPAREN       -> "("
Linha 1: VOID         -> "void"
Linha 1: RPAREN       -> ")"
Linha 2: LBRACE       -> "{"
Linha 3: INT          -> "int"
Linha 3: ID           -> "x"
Linha 3: SEMI         -> ";"
Linha 4: ID           -> "x"
Linha 4: ASSIGN       -> "="
Linha 4: NUM          -> "10"
Linha 4: SEMI         -> ";"
Linha 5: RETURN       -> "return"
Linha 5: ID           -> "x"
Linha 5: SEMI         -> ";"
Linha 6: RBRACE       -> "}"
Linha 7: ENDFILE      -> "EOF"

=== Varredura concluída ===
```

## Exemplos de Código C-

### exemplo1.cm - Programa simples

```c
int main(void) {
    int x;
    x = 10;
    return x;
}
```

### exemplo2.cm - Estruturas de controle

```c
int fatorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * fatorial(n - 1);
}
```

### exemplo3.cm - Array e loop

```c
int soma(int arr[], int tam) {
    int i;
    int total;
    total = 0;
    i = 0;
    while (i < tam) {
        total = total + arr[i];
        i = i + 1;
    }
    return total;
}
```

## Tipos de Tokens Reconhecidos

| Categoria | Tokens |
|-----------|--------|
| Palavras Reservadas | `else`, `if`, `int`, `return`, `void`, `while` |
| Operadores Aritméticos | `+`, `-`, `*`, `/` |
| Operadores Relacionais | `<`, `<=`, `>`, `>=`, `==`, `!=` |
| Atribuição | `=` |
| Delimitadores | `;`, `,` |
| Parênteses | `(`, `)` |
| Colchetes | `[`, `]` |
| Chaves | `{`, `}` |
| Identificadores | Sequências alfanuméricas começando com letra |
| Números | Sequências de dígitos |
| Comentários | `/* ... */` (ignorados pelo scanner) |

## Tratamento de Erros

O scanner identifica os seguintes tipos de erro:
- Caracteres inválidos
- Comentários não fechados (EOF dentro de comentário)
- Operador `!` isolado (deve ser seguido de `=` para formar `!=`)

## Observações

- O scanner diferencia maiúsculas de minúsculas
- Espaços em branco, tabulações e quebras de linha são ignorados
- Comentários são ignorados e não geram tokens
- O programa mantém contagem de linhas para facilitar a depuração

## Autor

Scanner desenvolvido como projeto acadêmico para a disciplina de Compiladores.
