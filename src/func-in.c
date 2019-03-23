#include <functions.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    my_abs(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "abs(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "abs(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT)
    {
        fprintf(stderr, "abs(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = abs(ast_node1->value_int);
    ast_node->value_float = ast_node->value_int;
}

void    my_min(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "min(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT || ast_node2->var_type != T_INT)
    {
        fprintf(stderr, "min(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = (ast_node1->value_int < ast_node2->value_int) ? ast_node1->value_int : ast_node2->value_int;
    ast_node->value_float = ast_node->value_int;
}

void    my_max(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "max(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT || ast_node2->var_type != T_INT)
    {
        fprintf(stderr, "max(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = (ast_node1->value_int > ast_node2->value_int) ? ast_node1->value_int : ast_node2->value_int;
    ast_node->value_float = ast_node->value_int;
}

void    my_pow(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "pow(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT || ast_node2->var_type != T_INT)
    {
        fprintf(stderr, "pow(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = (int)pow(ast_node1->value_int, ast_node2->value_int);
    ast_node->value_float = ast_node->value_int;
}

void    my_rand(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type != AST_NULL || ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "rand(): too many arguments\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = rand();
    ast_node->value_float = ast_node->value_int;
}

void    my_at(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "at(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "at(): argument of type T_STRING expected\n");
        exit(0);
    }
    else if (ast_node2->var_type != T_INT)
    {
        fprintf(stderr, "at(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_CHAR;
    ast_node->value_char = ast_node1->value_string[ast_node2->value_int];
    ast_node->value_int = ast_node->value_char;
    ast_node->value_float = ast_node->value_char;
}

void    my_len(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "len(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "len(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "len(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = (int)strlen(ast_node1->value_string);
    ast_node->value_float = ast_node->value_int;
}

void    my_int_to_string(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "int_to_string(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "int_to_string(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT)
    {
        fprintf(stderr, "int_to_string(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    ast_node->value_string = malloc(50 * sizeof(char));
    sprintf((char *)ast_node->value_string, "%d", ast_node1->value_int);
}

void    my_float_to_string(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "float_to_string(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "float_to_string(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FLOAT)
    {
        fprintf(stderr, "float_to_string(): argument of type T_FLOAT expected\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    ast_node->value_string = malloc(50 * sizeof(char));
    sprintf((char *)ast_node->value_string, "%g", ast_node1->value_float);
}

void    my_string_to_int(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "string_to_int(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "string_to_int(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "string_to_int(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_INT;
    ast_node->value_int = atoi(ast_node1->value_string);
    ast_node->value_float = ast_node->value_int;
}

void    my_string_to_float(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "string_to_float(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "string_to_float(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "string_to_float(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_FLOAT;
    ast_node->value_float = (float)atof(ast_node1->value_string);
    ast_node->value_int = (int)ast_node->value_float;
}

void    my_print(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "print(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "print(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "print(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    printf("%s", ast_node1->value_string);
}

void    my_putchar(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "putchar(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "putchar(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_CHAR)
    {
        fprintf(stderr, "putchar(): argument of type T_CHAR expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    putchar(ast_node1->value_char);
}

void    my_putnbr(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "putnbr(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "putnbr(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_INT)
    {
        fprintf(stderr, "putnbr(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    printf("%d", ast_node1->value_int);
}

void    my_putnbr_float(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "putnbr_float(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "putnbr_float(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FLOAT)
    {
        fprintf(stderr, "putnbr_float(): argument of type T_FLOAT expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    printf("%g", ast_node1->value_float);
}

void    my_putbool(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "putbool(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "putbool(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_BOOL)
    {
        fprintf(stderr, "putbool(): argument of type T_BOOL expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    printf("%s", ast_node1->value_bool ? "true" : "false");
}

void        my_scan(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    size_t  size;

    size = 0;
    if (ast_node1->node_type != AST_NULL || ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "scan(): too many arguments\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    getline((char **)&ast_node->value_string, &size, stdin);
}

void    my_open(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "open(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "open(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_STRING)
    {
        fprintf(stderr, "open(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_FILE;
    ast_node->value_file = fopen(ast_node1->value_string, "r+");
    if (ast_node->value_file == NULL)
    {
        fprintf(stderr, "open(): cannot open file\n");
        exit(0);
    }
}

void    my_read(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "read(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FILE)
    {
        fprintf(stderr, "read(): argument of type T_FILE expected\n");
        exit(0);
    }
    else if (ast_node2->var_type != T_INT)
    {
        fprintf(stderr, "read(): argument of type T_INT expected\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    if (ast_node1->value_file == NULL)
    {
        fprintf(stderr, "read(): cannot read file\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    ast_node->value_string = calloc((unsigned)ast_node2->value_int + 1, sizeof(char));
    if (ast_node->value_string == NULL)
        return ;
    fread((char *)ast_node->value_string, (unsigned)ast_node2->value_int, 1, ast_node1->value_file);
}

void        my_readline(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    size_t  size;

    size = 0;
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "readline(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "readline(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FILE)
    {
        fprintf(stderr, "readline(): argument of type T_FILE expected\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    if (ast_node1->value_file == NULL)
    {
        fprintf(stderr, "read(): cannot read file\n");
        exit(0);
    }
    ast_node->var_type = T_STRING;
    getline((char **)&ast_node->value_string, &size, ast_node1->value_file);
}

void    my_write(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL || ast_node2->node_type == AST_NULL)
    {
        fprintf(stderr, "write(): too few arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FILE)
    {
        fprintf(stderr, "write(): argument of type T_FILE expected\n");
        exit(0);
    }
    else if (ast_node2->var_type != T_STRING)
    {
        fprintf(stderr, "write(): argument of type T_STRING expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    if (ast_node1->value_file == NULL)
    {
        fprintf(stderr, "read(): cannot write in file\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    fwrite(ast_node2->value_string, 1, strlen(ast_node2->value_string), ast_node1->value_file);
}

void        my_close(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "close(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "close(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FILE)
    {
        fprintf(stderr, "close(): argument of type T_FILE expected\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    if (ast_node1->value_file == NULL)
    {
        fprintf(stderr, "read(): cannot close file\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    fclose(ast_node1->value_file);
}

void        my_is_open(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type == AST_NULL)
    {
        fprintf(stderr, "is_open(): too few arguments\n");
        exit(0);
    }
    else if (ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "is_open(): too many arguments\n");
        exit(0);
    }
    else if (ast_node1->var_type != T_FILE)
    {
        fprintf(stderr, "is_open(): argument of type T_FILE expected\n");
        exit(0);
    }
    ast_node->var_type = T_BOOL;
    ast_node->value_bool = ast_node1 != NULL;
}

void        my_br(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    if (ast_node1->node_type != AST_NULL || ast_node2->node_type != AST_NULL)
    {
        fprintf(stderr, "br(): too many arguments\n");
        exit(0);
    }
    ast_node->var_type = T_VOID;
    printf("\n");
}