#include <ast.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <variables.h>

t_ast_node          *affectation(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    t_ast_node      *fact_ast_node;
    t_ast_node      *expr_ast_node;


    fact_ast_node = factor(parse_utils, var_list, is_comment);
    pop_token(parse_utils, is_comment);
    expr_ast_node = expression(parse_utils, var_list, is_comment);
    return (create_node_binary(AST_AFFECTATION, fact_ast_node, expr_ast_node));
}

t_ast_node            *expression(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    t_ast_node        *expr1_ast_node;
    t_ast_node        *term_ast_node;

    term_ast_node = term(parse_utils, var_list, is_comment);
    expr1_ast_node = expression1(parse_utils, var_list, is_comment);
    return (create_node_binary(AST_PLUS, term_ast_node, expr1_ast_node));
}

t_ast_node            *expression1(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    t_ast_node        *expr1_ast_node;
    t_ast_node        *term_ast_node;

    switch (parse_utils->current_token.token_type)
    {
        case TOK_PLUS:
            pop_token(parse_utils, is_comment);
            term_ast_node = term(parse_utils, var_list, is_comment);
            expr1_ast_node = expression1(parse_utils, var_list, is_comment);
            return (create_node_binary(AST_PLUS, expr1_ast_node, term_ast_node));
        case TOK_MINUS:
            pop_token(parse_utils, is_comment);
            term_ast_node = term(parse_utils, var_list, is_comment);
            expr1_ast_node = expression1(parse_utils, var_list, is_comment);
            return (create_node_binary(AST_MINUS, expr1_ast_node, term_ast_node));
        default:
            break;
    }
    return (create_node_number(T_INT, 0, 0));
}

t_ast_node              *term(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    bool               modulo_mode;
    t_ast_node        *fact_ast_node;
    t_ast_node        *term1_ast_node;

    modulo_mode = false;
    fact_ast_node = factor(parse_utils, var_list, is_comment);
    if (parse_utils->current_token.token_type == TOK_MOD)
        modulo_mode = true;
    term1_ast_node = term1(parse_utils, var_list, is_comment);
    if (modulo_mode)
        return (create_node_binary(AST_MOD, fact_ast_node, term1_ast_node));
    else
        return (create_node_binary(AST_MUL, fact_ast_node, term1_ast_node));
}

t_ast_node            *term1(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    t_ast_node        *fact_ast_node;
    t_ast_node        *term1_ast_node;

    switch (parse_utils->current_token.token_type)
    {
        case TOK_MUL:
            pop_token(parse_utils, is_comment);
            fact_ast_node = factor(parse_utils, var_list, is_comment);
            term1_ast_node = term1(parse_utils, var_list, is_comment);
            return (create_node_binary(AST_MUL, term1_ast_node, fact_ast_node));
        case TOK_DIV:
            pop_token(parse_utils, is_comment);
            fact_ast_node = factor(parse_utils, var_list, is_comment);
            term1_ast_node = term1(parse_utils, var_list, is_comment);
            return (create_node_binary(AST_DIV, term1_ast_node, fact_ast_node));
        case TOK_MOD:
            pop_token(parse_utils, is_comment);
            fact_ast_node = factor(parse_utils, var_list, is_comment);
            term1_ast_node = term1(parse_utils, var_list, is_comment);
            return (create_node_binary(AST_MUL, term1_ast_node, fact_ast_node));
       default:
            break;
    }
    return (create_node_number(T_INT, 1, 1));
}

t_ast_node            *factor(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment)
{
    int             tmp_value_int;
    char            tmp_value_char;
    bool            tmp_value_bool;
    float           tmp_value_float;
    t_var_type      tmp_var_type;
    const char      *tmp_value_string;
    const char      *tmp_var_name;
    t_ast_node      *ast_node;
    t_ast_node      *ast_node1;
    t_ast_node      *ast_node2;

    switch (parse_utils->current_token.token_type)
    {
        case TOK_LEFT_PAREN:
            pop_token(parse_utils, is_comment);
            ast_node = expression(parse_utils, var_list, is_comment);
            expect(')', parse_utils, is_comment);
            return (ast_node);
        case TOK_MINUS:
            pop_token(parse_utils, is_comment);
            ast_node = factor(parse_utils, var_list, is_comment);
            return (create_node_unary(ast_node));
        case TOK_NUMBER:
            tmp_var_type = parse_utils->current_token.var_type;
            tmp_value_int = parse_utils->current_token.value_int;
            tmp_value_float = parse_utils->current_token.value_float;
            pop_token(parse_utils, is_comment);
            return (create_node_number(tmp_var_type, tmp_value_int, tmp_value_float));
        case TOK_CHAR:
            tmp_value_char = parse_utils->current_token.value_char;
            pop_token(parse_utils, is_comment);
            return (create_node_char(tmp_value_char));
        case TOK_STRING:
            tmp_value_string = strdup(parse_utils->current_token.value_string);
            pop_token(parse_utils, is_comment);
            ast_node = create_node_string(tmp_value_string);
            free((char *)tmp_value_string);
            return (ast_node);
        case TOK_BOOL:
            tmp_value_bool = parse_utils->current_token.value_bool;
            pop_token(parse_utils, is_comment);
            return (create_node_bool(tmp_value_bool));
        case TOK_FUNC_CALL:
            tmp_var_name = strdup(parse_utils->current_token.var_name);
            pop_token(parse_utils, is_comment);
            pop_token(parse_utils, is_comment);
            if (parse_utils->current_token.token_type == TOK_RIGHT_PAREN)
            {
                ast_node1 = create_node_null();
                ast_node2 = create_node_null();
                pop_token(parse_utils, is_comment);
            }
            else
            {
                if (parse_utils->current_token.token_type == TOK_COMMA)
                {
                    fprintf(stderr, "Parse error, unexpected ',' at position %ld\n", parse_utils->index);
                    exit(0);
                }
                ast_node1 = expression(parse_utils, var_list, is_comment);
                if (parse_utils->current_token.token_type == TOK_COMMA)
                {
                    pop_token(parse_utils, is_comment);
                    ast_node2 = expression(parse_utils, var_list, is_comment);
                }
                else
                    ast_node2 = create_node_null();
                expect(')', parse_utils, is_comment);
            }
            ast_node = create_node_call_func(tmp_var_name, ast_node1, ast_node2);
            free((char *)tmp_var_name);
            return (ast_node);
        case TOK_VARIABLE:
            tmp_var_name = strdup(parse_utils->current_token.var_name);
            pop_token(parse_utils, is_comment);
            if (get_variable(var_list, tmp_var_name))
                ast_node = create_node_e_variable(get_variable(var_list, tmp_var_name));
            else if (parse_utils->nb_token == 3 && parse_utils->decla_type)
            {
                if (parse_utils->current_token.token_type != TOK_AFFECTATION)
                {
                    fprintf(stderr, "Parse Error: Declaration must be follow by an affectation\n");
                    exit(0);
                }
                ast_node = create_node_variable(tmp_var_name, parse_utils->decla_type);
            }
            else
            {
                fprintf(stderr, "Parse Error: Unknown variable '%s' at position %lu\n",
                        tmp_var_name, parse_utils->index);
                exit(0);
            }
            free((char *)tmp_var_name);
            return (ast_node);
        default:
        {
            fprintf(stderr, "Parse Error: Unexpected token '%c' at position %lu\n",
                parse_utils->current_token.value_symbol, parse_utils->index);
            exit(0);
        }
    }
}

t_ast_node            *parse(const char *line, t_var_list *var_list, bool *is_comment)
{
    t_parse_utils   parse_utils;

    init_parse_utils(&parse_utils, line);
    parse_utils.current_token.var_name = NULL;
    parse_utils.current_token.value_string = NULL;
    if (*is_comment)
        pop_line_until_endcomment(&parse_utils, is_comment);
    else
        pop_token(&parse_utils, is_comment);
    if (parse_utils.current_token.token_type == TOK_DECLARATION)
    {
        parse_utils.decla_type = parse_utils.current_token.var_type;
        pop_token(&parse_utils, is_comment);
    }
    if (is_affectation(line))
        return (affectation(&parse_utils, var_list, is_comment));
    else
        return (expression(&parse_utils, var_list, is_comment));
}
