#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum CommandType {
    EMPTY,
    NEWVAR,
    ASSIGN,
    PRINT
};

enum OpType {
    NONE,
    PLUS,
    MINUS,
    MULT,
    DIV,
    GT,
    LT,
    EQ,
    NEQ
};

const char operations[][3] = {
    "",
    "+",
    "-",
    "*",
    "/",
    ">",
    "<",
    "==",
    "!="
};

enum {VAR_LEN = 33};

struct Token {
    char name[VAR_LEN];
    float value;
};

struct Expr {
    struct Token op1;
    enum OpType op;
    struct Token op2;
};

struct Command {
    enum CommandType type;
    char newVarName[VAR_LEN];
    struct Expr newVarExpr;
    struct Expr printExpr;
    char assignVarName[VAR_LEN];
    struct Expr assignVarExpr;
};

struct Var {
    char name[VAR_LEN];
    float value;
};

struct Memory {
    struct Var vars[100];
    int count;  
};

int skipSpaces(char * input) {
    int n = 0;
    while (isspace(*input)) {
        input++;
        n++;
    }
    return n;
}

int readName(char * input, char * buf, int bufLen) {
    int n = 0;
    while (*input == '_' || isalnum(*input)) {
        buf[n] = *input;
        input++;
        n++;
        if (n == bufLen - 1) break;
    }
    buf[n] = '\0';
    return n;
}

int readToken(char * input, struct Token * token) {
    int n = 0;
    token->name[0] = '\0';
    sscanf(input, "%f%n", &token->value, &n);
    if (n == 0) n = readName(input, token->name, VAR_LEN);
    return n;
}

enum OpType readOperation(char * input) {
    for (int i = 1; i < sizeof(operations) / sizeof(operations[0]); i++) {
        const char * operation = operations[i];
        if (strstr(input, operation) == input) {
            return (enum OpType)i;
        }
    }
    return NONE;
}

int readExpr(char * input, struct Expr * expr) {
    char * origin = input;
    input += skipSpaces(input);
    int n = readToken(input, &expr->op1);
    if (n == 0) return 0;
    input += n;
    input += skipSpaces(input);
    expr->op = readOperation(input);
    if (expr->op == NONE) return input - origin;
    input += strlen(operations[expr->op]);
    input += skipSpaces(input);
    n = readToken(input, &expr->op2);
    if (n == 0) return 0;
    input += n;
    return input - origin;
}

void printToken(struct Token * token) {
    if (token->name[0] == '\0') {
        printf("%f", token->value);
    } else {
        printf("%s", token->name);
    }
}

void printExpr(struct Expr * expr) {
    printToken(&expr->op1);
    if (expr->op != NONE) {
        printf(" %s ", operations[expr->op]);
        printToken(&expr->op2);
    }
}

void printCommand(struct Command * command) {
    switch(command->type) {
        case NEWVAR: {
            printf("new var: '%s' ", command->newVarName);
            printExpr(&command->newVarExpr);
            break;
        }
        case ASSIGN: {
            printf("assign: '%s' ", command->assignVarName);
            printExpr(&command->assignVarExpr);
            break;
        }
        case PRINT: {
            printf("print: ");
            printExpr(&command->printExpr);
            break;
        }
        default: break;
    }
    puts("");
}

bool parseCommand(char * input, struct Command * command) {
    input += skipSpaces(input);
    if (input[0] == '\0') {
        command->type = EMPTY;
        return true;
    }
    enum {BUF_LEN = 100};
    char buf[BUF_LEN] = "";
    int n = readName(input, buf, BUF_LEN);
    if (n == 0) return false;
    input += n;
    input += skipSpaces(input);
    if (0 == strcmp(buf, "create")) {
        command->type = NEWVAR;
        n = readName(input, command->newVarName, VAR_LEN);
        if (n == 0) return false;
        input += n;
        input += skipSpaces(input);
        if (*input != ':') return false;
        input += 1;
        n = readExpr(input, &command->newVarExpr);
        if (n == 0) return false;
        input += n;
    } else if (0 == strcmp(buf, "output")) {
        command->type = PRINT;
        if (*input != '(') return false;
        input += 1;
        n = readExpr(input, &command->printExpr);
        if (n == 0) return false;
        input += n;
        input += skipSpaces(input);
        if (*input != ')') return false;
        input += 1;
    } else {
        command->type = ASSIGN;
        strcpy(command->assignVarName, buf);
        if (*input != ':') return false;
        if (*(input + 1) != '=') return false;
        input += 2;
        input += skipSpaces(input);
        n = readExpr(input, &command->assignVarExpr);
        if (n == 0) return false;
        input += n;
    }
    input += skipSpaces(input);
    return input[0] == '\0';
}

struct Var * getVar(struct Memory * mem, char * name) {
    for (int i = 0; i < mem->count; i++) {
        struct Var * var = &mem->vars[i];
        if (0 == strcmp(var->name, name)) return var;
    }
    return NULL;
}

bool addVar(struct Memory * mem, struct Var * var) {
    if (getVar(mem, var->name) != NULL) return false;
    mem->vars[mem->count] = *var;
    mem->count ++;
    return true;
}

bool evalToken(struct Token * token, float * res, struct Memory * mem) {
    if (token->name[0] == '\0') {
        *res = token->value;
        return true;
    } else {
        struct Var * var = getVar(mem, token->name);
        if (var == NULL) return false;
        *res = var->value;
        return true;
    }
}

bool evalExpr(struct Expr * expr, float * result, struct Memory * mem) {
    float v1 = 0;
    if (!evalToken(&expr->op1, &v1, mem)) return false;
    if (expr->op == NONE) {
        *result = v1;
        return true;
    }
    float v2 = 0;
    if (!evalToken(&expr->op2, &v2, mem)) return false;
    switch (expr->op) {
        case PLUS: *result = v1 + v2; return true;
        case MINUS: *result = v1 - v2; return true;
        case MULT: *result = v1 * v2; return true;
        case DIV: *result = v1 / v2; return true;
        case GT: *result = v1 > v2; return true;
        case LT: *result = v1 < v2; return true;
        case EQ: *result = v1 == v2; return true;
        case NEQ: *result = v1 != v2; return true;
        default:  return false;
    }
}

bool runCommand(struct Command * command, struct Memory * mem) {
    switch(command->type) {
        case NEWVAR: {
            struct Var var = {0};
            strcpy(var.name, command->newVarName);
            if (!evalExpr(&command->newVarExpr, &var.value, mem)) return false;
            if (!addVar(mem, &var)) {
                return false;
            }
            break;
        }
        case ASSIGN: {
            struct Var * var = getVar(mem, command->assignVarName);
            if (var == NULL) return false;
            float value = 0;
            if (!evalExpr(&command->assignVarExpr, &value, mem)) return false;
            var->value = value;
            break;
        }
        case PRINT: {
            float value = 0;
            if (!evalExpr(&command->printExpr, &value, mem)) return false;
            printf("%.2f\n", value);
            break;
        }
        default: break;
    }
    return true;
}

bool checkExt(char * fileName, char * ext) {
    int nameLen = strlen(fileName);
    int extlen = strlen(ext);
    if (nameLen < extlen) return false;
    char * findstart = fileName + nameLen - extlen;
    return 0 == strcmp(findstart, ext);
}

int main(int argc, char * argv[]) {
    if (argc != 2) return EXIT_FAILURE;
    char * fileName = argv[1];
    if (!checkExt(fileName, ".dopka")) return EXIT_FAILURE;
    FILE * in = fopen(fileName, "r");
    if (in == NULL) return EXIT_FAILURE;
    puts("# DichInCube interpreter:\n-----------------------------");
    struct Memory memory = {0};
    char * pline = NULL;
    enum {BUF_LEN=100};
    char buf[BUF_LEN] = "";
    struct Command command = {0};
    while (true) {
        pline = fgets(buf, BUF_LEN, in);
        if (pline == NULL) break;
        if (!parseCommand(pline, &command)) {
            printf("Error at parse: %s", pline);
            fclose(in);
            return EXIT_FAILURE;
        }
        if (command.type == EMPTY) continue;
        printf("> ");
        printCommand(&command);
        if (!runCommand(&command, &memory)) {
            printf("Error at run: ");
            printCommand(&command);
            fclose(in);
            return EXIT_FAILURE;
        }
    }
    fclose(in);
    return 0;
}
