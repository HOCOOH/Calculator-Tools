#include "Parser.h"

Token* look = NULL;
extern FILE* dest;
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
    while (look->tag == INT_DECL || look->tag == FLOAT_DECL) {
        int flag = look->tag;
        Scan();
        if (look->isID == false) {
            fprintf(dest, "ERROR(line %d): expected identifier after type declaration", line);
            exit(1);
        }
        if (flag == INT_DECL)
            look->tag = INT;
        else
            look->tag = FLOAT;
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
            if (tmp.tag == INT)
                fprintf(dest, "%d\n", tmp.value);
            else
                fprintf(dest, "%f\n", tmp.valueReal);
            match(')');
            match(';');
            continue;
        }
        // assign
        if (look->tag != INT && look->tag != FLOAT) {
            fprintf(dest, "ERROR(line %d): identifier \'%s\' is undeclared", line, look->lexeme);
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
            else if (left.tag == INT)  {
                double tmp = (double)left.value;
                left = (Token){FLOAT, 0, tmp + right.valueReal, NULL, false, false};
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
            else if (left.tag == INT)  {
                double tmp = (double)left.value;
                left = (Token){FLOAT, 0, tmp - right.valueReal, NULL, false, false};
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
    Token left = unary();
    while (true) {
        if (look->tag == '*') {
            match('*');
            Token right = unary();
            if (left.tag == right.tag) {
                left.value *= right.value;
                left.valueReal *= right.valueReal;
            }
            else if (left.tag == INT)  {
                double tmp = (double)left.value;
                left = (Token){FLOAT, 0, tmp * right.valueReal, NULL, false, false};
            }
            else
                left.valueReal *= (double)right.value;
        }
        else if (look->tag == '/') {
            match('/');
            Token right = unary();
            if ((right.tag == INT && right.value == 0) || (right.tag == FLOAT && fabs(right.valueReal) < 0.0001)) {
                fprintf(dest, "ERROR(line %d): the divisor is zero", line);
                exit(1);
            }
            if (left.tag == right.tag) {
                left.value /= right.value;
                left.valueReal /= right.valueReal;
            }
            else if (left.tag == INT)  {
                double tmp = (double)left.value;
                left = (Token){FLOAT, 0, tmp / right.valueReal, NULL, false, false};
            }
            else
                left.valueReal /= (double)right.value;
        }
        else return left;
    }
}
/* ----------------------------------------------------------------
unary → - unary | factor
---------------------------------------------------------------- */
Token unary() {
    int flag = 1;
    while (true) {
        if (look->tag == '-') {
            match('-');
            flag *= -1;
            continue;
        }
        Token tmp = factor();
        tmp.value *= flag;
        tmp.valueReal *= flag;
        return tmp;
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
    if (look->isID == true && look->tag != INT && look->tag != FLOAT) {
        fprintf(dest, "ERROR(line %d): identifier \'%s\' is undeclared", line, look->lexeme);
        exit(1);
    }
    if (look->isID == true && look->isAssigned == false) {
        fprintf(dest, "ERROR(line %d): identifier \'%s\' is unassigned", line, look->lexeme);
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
        fprintf(dest, "ERROR(line %d): expected \'%c\'", line, (char)tar);
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
    else if (left->tag = INT)  // 左式和右式不是同一类型
        left->value = (int)tmp.valueReal;
    else
        left->valueReal = (double)tmp.value;
    left->isAssigned = true;
    match(';');
}