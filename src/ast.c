#include <ast.h>
#include <stdlib.h>
#include <string.h>

t_ast_node*     create_node_binary(t_ast_nodetype type, t_ast_node *left, t_ast_node *right)
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = type;
    ast_node->var_name = NULL;
    ast_node->var_type = T_UNDEFINED;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = '\0';
    ast_node->value_string = NULL;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = left;
    ast_node->ast_node_r = right;
    return (ast_node);
}

t_ast_node*     create_node_unary(t_ast_node* left)
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_UNARY_MIN;
    ast_node->var_name = NULL;
    ast_node->var_type = T_UNDEFINED;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = '\0';
    ast_node->value_string = NULL;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = left;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node*     create_node_number(t_var_type var_type, int value_int, float value_float)
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_NUMBER;
    ast_node->var_name = NULL;
    ast_node->var_type = var_type;
    ast_node->value_int = value_int;
    ast_node->value_float = value_float;
    ast_node->value_char = (char)value_int;
    ast_node->value_string = NULL;
    ast_node->value_bool = false;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node*     create_node_char(char value_char)
{
    t_ast_node *ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_CHAR;
    ast_node->var_name = NULL;
    ast_node->var_type = T_CHAR;
    ast_node->value_int = value_char;
    ast_node->value_float = value_char;
    ast_node->value_char = value_char;
    ast_node->value_string = NULL;
    ast_node->value_bool = false;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node      *create_node_bool(bool value_bool)
{
    t_ast_node  *ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_BOOL;
    ast_node->var_name = NULL;
    ast_node->var_type = T_BOOL;
    ast_node->value_int = value_bool;
    ast_node->value_float = value_bool;
    ast_node->value_char = (char)value_bool;
    ast_node->value_string = NULL;
    ast_node->value_bool = value_bool;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node      *create_node_string(const char *value_string)
{
    t_ast_node  *ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_STRING;
    ast_node->var_name = NULL;
    ast_node->var_type = T_STRING;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = '\0';
    ast_node->value_string = strdup(value_string);
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node      *create_node_variable(const char *var_name, t_var_type var_type)
{
    t_ast_node  *ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_VARIABLE;
    ast_node->var_name = strdup(var_name);
    ast_node->var_type = var_type;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = '\0';
    ast_node->value_string = NULL;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node*     create_node_e_variable(t_var_node *var_node)
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_VARIABLE;
    ast_node->var_name = strdup(var_node->var_name);
    ast_node->var_type = var_node->var_type;
    ast_node->value_bool = var_node->value_bool;
    ast_node->value_int = var_node->value_int;
    ast_node->value_float = var_node->value_float;
    ast_node->value_char = var_node->value_char;
    if (var_node->var_type == T_STRING && var_node->value_string != NULL)
        ast_node->value_string = strdup(var_node->value_string);
    else
        ast_node->value_string = NULL;
    ast_node->value_file = var_node->value_file;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

t_ast_node      *create_node_call_func(const char *var_name, t_ast_node *ast_node1, t_ast_node *ast_node2)
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_CALL_FUNC;
    ast_node->var_name = strdup(var_name);
    ast_node->var_type = T_VOID;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = 0;
    ast_node->value_string = NULL;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = ast_node1;
    ast_node->ast_node_r = ast_node2;
    return (ast_node);
}

t_ast_node      *create_node_null()
{
    t_ast_node* ast_node;

    ast_node = malloc(sizeof(t_ast_node));
    if (ast_node == NULL)
        return (NULL);
    ast_node->node_type = AST_NULL;
    ast_node->var_name = NULL;
    ast_node->var_type = T_NULL;
    ast_node->value_bool = false;
    ast_node->value_int = 0;
    ast_node->value_float = 0;
    ast_node->value_char = 0;
    ast_node->value_string = NULL;
    ast_node->value_file = NULL;
    ast_node->ast_node_l = NULL;
    ast_node->ast_node_r = NULL;
    return (ast_node);
}

void    destruct_astnode(t_ast_node *ast_node)
{
    if (ast_node == NULL)
        return ;
    if (ast_node->var_name != NULL)
        free((char *)ast_node->var_name);
    if (ast_node->value_string != NULL)
        free((char *)ast_node->value_string);
    if (ast_node->ast_node_l != NULL)
        destruct_astnode(ast_node->ast_node_l);
    if (ast_node->ast_node_r != NULL)
        destruct_astnode(ast_node->ast_node_r);
    free(ast_node);
}
