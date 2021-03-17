# Calculator-Tools
Homework of course: Compilers Principles

## 一、计算器说明

计算器接受四则运算表达式为输入（如下图所示）。如果表达式语法正确，则输出计算结果，**否则报错，指出错误位置及原因**。

```c
Input 1:
float a; int b; 
a = (10.44*356+1.28) / 2 + 1024 * 1.6;
b = a * 2 – a/2;
write(b);
write(a).
Output 1:
   8743.4
   3497
```

```c
Input 2:
float a; 
int b; 
a = (10.44*356+1.28) / 2 + 1024 * 1.6;
b = a * 2 – c/2;
write(b).
Output 2:
   Error(line 4): undefined identifier . 
```

1. 支持浮点数和整数两种类型，浮点数可以转换成整数；整数不可以转换成浮点数；
2. 每个语句需要以“；”结束，以“.”表示全部输入的结束
3. 变量需要先声明再使用；
4. 变量名可以是由数字和字母组成，但首字符必须是字母。
5. 每个表达式中使用的变量需要在之前已经有赋值。
6. 输出语句使用write(a)，输出并换行，其中a为int类型或者float类型的变量名。

## 二、文法设计

program → decls stmts .

decls → decls decl | e

decl → **type** **id** ;

stmts → stmts stmt | e

stmt → **id** = expr ;

| **write( id )** ;

expr → expr + term | expr - term | term

term → term * factor | term / factor | factor

factor → (expr) | **num** | **real** |  **id**



