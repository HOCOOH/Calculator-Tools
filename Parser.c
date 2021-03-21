#include "Parser.h"

Token* look = NULL;
extern int line;
extern IdTable ids;

/*----------------------------------------------------------------
program → decls stmts .
----------------------------------------------------------------*/
void Parser() {
    Scan();
    decls();
    stmts();
    match('.');
}
/* ----------------------------------------------------------------
decls → decls decl | ε
decl → type id ; | type id = expr ;
---------------------------------------------------------------- */
void decls() {
    while (look->tag == INT || look->tag == FLOAT) {
        int flag = look->tag;
        Scan();
        if (look->isID == false) {
            fprintf(stderr, "ERROR(line %d): expected identifier after type declaration", line);
            exit(1);
        }
        if (flag == INT)
            look->tag = NUM;
        else
            look->tag = REAL;
        Token* left = look;
        Scan();
        if (look->tag == '=')
            Assign(left);
        else
            match(';');
    }
}
/* ----------------------------------------------------------------
stmts → stmts stmt | ε
stmt → id = expr ; | write ( expr ) ;
---------------------------------------------------------------- */
void stmts() {
    while (look->isID == true || look->tag == WRITE) {
        // write(id);
        if (look->tag == WRITE) {
            Scan();
            match('(');
            Token tmp = expr();
            if (tmp.tag == NUM)
                printf("%d\n", tmp.value);
            else
                printf("%f\n", tmp.valueReal);
            match(')');
            match(';');
            continue;
        }
        // assign
        if (look->tag != NUM && look->tag != REAL) {
            fprintf(stderr, "ERROR(line %d): identifier \'%s\' is undeclared", line, look->lexeme);
            exit(1);
        }
        Token* left = look;
        Scan();
        Assign(left);
    }
}
/* ----------------------------------------------------------------
expr → expr + term | expr - term | term
---------------------------------------------------------------- */
Token expr() {
    Token left = term();
    while (true) {
        if (look->tag == '+') {
            match('+');
            Token right = term();
            if (left.tag == right.tag) {
                left.value += right.value;
                left.valueReal += right.valueReal;
            }
            else if (left.tag == NUM)  {
                double tmp = (double)left.value;
                left = (Token){REAL, 0, tmp + right.valueReal, NULL, false, false};
            }
            else
                left.valueReal += (double)right.value;
        }
        else if (look->tag == '-') {
            match('-');
            Token right = term();
            if (left.tag == right.tag) {
                left.value -= right.value;
                left.valueReal -= right.valueReal;
            }
            else if (left.tag == NUM)  {
                double tmp = (double)left.value;
                left = (Token){REAL, 0, tmp - right.valueReal, NULL, false, false};
            }
            else
                left.valueReal -= (double)right.value;
        }
        else return left;
    }
}
/* ----------------------------------------------------------------
term → term * factor | term / factor | factor
---------------------------------------------------------------- */
Token term() {
    Token left = factor();
    while (true) {
        if (look->tag == '*') {
            match('*');
            Token right = factor();
            if (left.tag == right.tag) {
                left.value *= right.value;
                left.valueReal *= right.valueReal;
            }
            else if (left.tag == NUM)  {
                double tmp = (double)left.value;
                left = (Token){REAL, 0, tmp * right.valueReal, NULL, false, false};
            }
            else
                left.valueReal *= (double)right.value;
        }
        else if (look->tag == '/') {
            match('/');
            Token right = factor();
            if ((right.tag == NUM && right.value == 0) || (right.tag == REAL && fabs(right.valueReal) < 0.0001)) {
                fprintf(stderr, "ERROR(line %d): the divisor is zero", line);
                exit(1);
            }
            if (left.tag == right.tag) {
                left.value /= right.value;
                left.valueReal /= right.valueReal;
            }
            else if (left.tag == NUM)  {
                double tmp = (double)left.value;
                left = (Token){REAL, 0, tmp / right.valueReal, NULL, false, false};
            }
            else
                left.valueReal /= (double)right.value;
        }
        else return left;
    }
}
/* ----------------------------------------------------------------
factor → (expr) | num | real | id
---------------------------------------------------------------- */
Token factor() {
    if (look->tag == '(') {
        match('(');
        Token left = expr();
        match(')');
        return left;
    }
    if (look->isID == true && look->tag != NUM && look->tag != REAL) {
        fprintf(stderr, "ERROR(line %d): identifier \'%s\' is undeclared", line, look->lexeme);
        exit(1);
    }
    if (look->isID == true && look->isAssigned == false) {
        fprintf(stderr, "ERROR(line %d): identifier \'%s\' is unassigned", line, look->lexeme);
        exit(1);
    }
    Token tmp = (Token){look->tag, look->value, look->valueReal, NULL, false, false};
    Scan();
    return tmp;
}
// 匹配一个单字符Token
void match(int tar) {
    if (tar == look->tag) {
        Scan();
    }
    else {
        fprintf(stderr, "ERROR(line %d): expected \'%c\'", line, (char)tar);
        exit(1);
    }
}

// left = expr ;
void Assign(Token* left) {
    match('=');
    Token tmp = expr();
    if (left->tag == tmp.tag) {
        left->value = tmp.value;
        left->valueReal = tmp.valueReal;
    }
    else if (left->tag = NUM)  // 左式和右式不是同一类型
        left->value = (int)tmp.valueReal;
    else
        left->valueReal = (double)tmp.value;
    left->isAssigned = true;
    match(';');
}