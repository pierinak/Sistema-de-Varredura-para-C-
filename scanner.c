

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 256

/* Tipos de tokens */
typedef enum {
    /* Palavras reservadas */
    ELSE, IF, INT, RETURN, VOID, WHILE,
    
    /* Símbolos especiais */
    PLUS, MINUS, TIMES, OVER,
    LT, LE, GT, GE, EQ, NEQ,
    ASSIGN, SEMI, COMMA,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,
    
    /* Outros */
    ID, NUM,
    ERROR, ENDFILE
} TokenType;

/* Estrutura do token */
typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_LEN];
    int line;
} Token;

/* Variáveis globais */
FILE *source;
int line_num = 1;
char current_char = ' ';

/* Protótipos */
void get_char(void);
void unget_char(void);
Token get_token(void);
void print_token(Token token);
const char* token_type_to_string(TokenType type);

/* Lê o próximo caractere do arquivo */
void get_char(void) {
    current_char = fgetc(source);
    if (current_char == '\n')
        line_num++;
}

/* Devolve o caractere ao buffer */
void unget_char(void) {
    ungetc(current_char, source);
    if (current_char == '\n')
        line_num--;
}

/* Verifica se é palavra reservada */
TokenType check_reserved(char *str) {
    if (strcmp(str, "else") == 0) return ELSE;
    if (strcmp(str, "if") == 0) return IF;
    if (strcmp(str, "int") == 0) return INT;
    if (strcmp(str, "return") == 0) return RETURN;
    if (strcmp(str, "void") == 0) return VOID;
    if (strcmp(str, "while") == 0) return WHILE;
    return ID;
}

/* Obtém o próximo token */
Token get_token(void) {
    Token token;
    int idx = 0;
    TokenType current_token;
    
    memset(token.lexeme, 0, MAX_TOKEN_LEN);
    token.line = line_num;
    
    /* Pula espaços em branco */
    while (isspace(current_char)) {
        get_char();
    }
    
    /* Verifica comentários */
    if (current_char == '/') {
        get_char();
        if (current_char == '*') {
            /* Comentário de bloco */
            get_char();
            while (1) {
                if (current_char == EOF) {
                    token.type = ERROR;
                    strcpy(token.lexeme, "EOF in comment");
                    return token;
                }
                if (current_char == '*') {
                    get_char();
                    if (current_char == '/') {
                        get_char();
                        break;
                    }
                } else {
                    get_char();
                }
            }
            return get_token(); /* Recursão para pegar o próximo token */
        } else {
            /* É o operador de divisão */
            unget_char();
            current_char = '/';
        }
    }
    
    /* Identifica o tipo de token */
    if (isalpha(current_char)) {
        /* Identificador ou palavra reservada */
        while (isalnum(current_char) && idx < MAX_TOKEN_LEN - 1) {
            token.lexeme[idx++] = current_char;
            get_char();
        }
        token.lexeme[idx] = '\0';
        token.type = check_reserved(token.lexeme);
    }
    else if (isdigit(current_char)) {
        /* Número */
        while (isdigit(current_char) && idx < MAX_TOKEN_LEN - 1) {
            token.lexeme[idx++] = current_char;
            get_char();
        }
        token.lexeme[idx] = '\0';
        token.type = NUM;
    }
    else {
        /* Símbolos especiais e operadores */
        switch (current_char) {
            case EOF:
                token.type = ENDFILE;
                strcpy(token.lexeme, "EOF");
                break;
            case '+':
                token.type = PLUS;
                token.lexeme[0] = '+';
                get_char();
                break;
            case '-':
                token.type = MINUS;
                token.lexeme[0] = '-';
                get_char();
                break;
            case '*':
                token.type = TIMES;
                token.lexeme[0] = '*';
                get_char();
                break;
            case '/':
                token.type = OVER;
                token.lexeme[0] = '/';
                get_char();
                break;
            case '<':
                token.lexeme[0] = '<';
                get_char();
                if (current_char == '=') {
                    token.type = LE;
                    token.lexeme[1] = '=';
                    get_char();
                } else {
                    token.type = LT;
                }
                break;
            case '>':
                token.lexeme[0] = '>';
                get_char();
                if (current_char == '=') {
                    token.type = GE;
                    token.lexeme[1] = '=';
                    get_char();
                } else {
                    token.type = GT;
                }
                break;
            case '=':
                token.lexeme[0] = '=';
                get_char();
                if (current_char == '=') {
                    token.type = EQ;
                    token.lexeme[1] = '=';
                    get_char();
                } else {
                    token.type = ASSIGN;
                }
                break;
            case '!':
                token.lexeme[0] = '!';
                get_char();
                if (current_char == '=') {
                    token.type = NEQ;
                    token.lexeme[1] = '=';
                    get_char();
                } else {
                    token.type = ERROR;
                    strcpy(token.lexeme, "!");
                }
                break;
            case ';':
                token.type = SEMI;
                token.lexeme[0] = ';';
                get_char();
                break;
            case ',':
                token.type = COMMA;
                token.lexeme[0] = ',';
                get_char();
                break;
            case '(':
                token.type = LPAREN;
                token.lexeme[0] = '(';
                get_char();
                break;
            case ')':
                token.type = RPAREN;
                token.lexeme[0] = ')';
                get_char();
                break;
            case '[':
                token.type = LBRACKET;
                token.lexeme[0] = '[';
                get_char();
                break;
            case ']':
                token.type = RBRACKET;
                token.lexeme[0] = ']';
                get_char();
                break;
            case '{':
                token.type = LBRACE;
                token.lexeme[0] = '{';
                get_char();
                break;
            case '}':
                token.type = RBRACE;
                token.lexeme[0] = '}';
                get_char();
                break;
            default:
                token.type = ERROR;
                token.lexeme[0] = current_char;
                token.lexeme[1] = '\0';
                get_char();
                break;
        }
    }
    
    return token;
}

/* Converte tipo de token para string */
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case ELSE: return "ELSE";
        case IF: return "IF";
        case INT: return "INT";
        case RETURN: return "RETURN";
        case VOID: return "VOID";
        case WHILE: return "WHILE";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case TIMES: return "TIMES";
        case OVER: return "OVER";
        case LT: return "LT";
        case LE: return "LE";
        case GT: return "GT";
        case GE: return "GE";
        case EQ: return "EQ";
        case NEQ: return "NEQ";
        case ASSIGN: return "ASSIGN";
        case SEMI: return "SEMI";
        case COMMA: return "COMMA";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case ID: return "ID";
        case NUM: return "NUM";
        case ERROR: return "ERROR";
        case ENDFILE: return "ENDFILE";
        default: return "UNKNOWN";
    }
}

/* Imprime o token */
void print_token(Token token) {
    printf("Linha %d: %-12s -> \"%s\"\n", 
           token.line, 
           token_type_to_string(token.type), 
           token.lexeme);
}

/* Função principal */
int main(int argc, char *argv[]) {
    Token token;
    
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_fonte>\n", argv[0]);
        return 1;
    }
    
    source = fopen(argv[1], "r");
    if (source == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }
    
    printf("=== Scanner para C- ===\n");
    printf("Arquivo: %s\n\n", argv[1]);
    
    /* Varredura principal */
    do {
        token = get_token();
        print_token(token);
    } while (token.type != ENDFILE);
    
    fclose(source);
    printf("\n=== Varredura concluída ===\n");
    
    return 0;
}