#include <ctype.h>
#include <parser.h>
#include <stdlib.h>
#include <token.h>

void    init_token(t_token *token)
{
    if (token->var_name != NULL)
        free((char *)token->var_name);
    token->var_name = NULL;
    token->var_type = T_UNDEFINED;
    token->value_bool = false;
    if (token->value_string != NULL)
        free((char *)token->value_string);
    token->value_string = NULL;
    token->value_int = 0;
    token->value_float = 0;
    token->value_char = '\0';
    token->value_file = NULL;
    token->value_symbol = '\0';
}

bool    set_token(t_parse_utils *parse_utils, bool *is_comment)
{
    if (!parse_utils->line[parse_utils->index])
    {
        parse_utils->current_token.token_type = TOK_END_TEXT;
        return (true);
    }
    else if (isdigit(parse_utils->line[parse_utils->index]))
    {
        parse_utils->current_token.token_type = TOK_NUMBER;
        get_number(parse_utils);
        parse_utils->current_token.value_char = (char)parse_utils->current_token.value_int;
        return (true);
    }
    else if (isalpha(parse_utils->line[parse_utils->index]))
    {
        parse_utils->current_token.token_type = TOK_VARIABLE;
        parse_utils->current_token.var_name = get_variable_name(parse_utils);
        return (true);
    }
    else if (parse_utils->line[parse_utils->index] == '\'')
    {
        parse_utils->current_token.token_type = TOK_CHAR;
        parse_utils->current_token.var_type = T_CHAR;
        parse_utils->current_token.value_char = get_char(parse_utils);
        parse_utils->current_token.value_int = parse_utils->current_token.value_char;
        parse_utils->current_token.value_float = parse_utils->current_token.value_char;
        return (true);
    }
    else if (parse_utils->line[parse_utils->index] == '"')
    {
        parse_utils->current_token.token_type = TOK_STRING;
        parse_utils->current_token.var_type = T_STRING;
        parse_utils->current_token.value_string = get_string(parse_utils);
        return (true);
    }
    else if (parse_utils->line[parse_utils->index] == '/' && parse_utils->line[parse_utils->index + 1] == '/')
    {
        pop_line(parse_utils, is_comment);
        return (true);
    }
    else if (parse_utils->line[parse_utils->index] == '/' && parse_utils->line[parse_utils->index + 1] == '*')
    {
        *is_comment = true;
        pop_line_until_endcomment(parse_utils, is_comment);
        return (true);
    }
    switch (parse_utils->line[parse_utils->index])
    {
        case '+': parse_utils->current_token.token_type = TOK_PLUS;
            break;
        case '-': parse_utils->current_token.token_type = TOK_MINUS;
            break;
        case '*': parse_utils->current_token.token_type = TOK_MUL;
            break;
        case '/': parse_utils->current_token.token_type = TOK_DIV;
            break;
        case '%': parse_utils->current_token.token_type = TOK_MOD;
            break;
        case '(': parse_utils->current_token.token_type = TOK_LEFT_PAREN;
            break;
        case ')': parse_utils->current_token.token_type = TOK_RIGHT_PAREN;
            break;
        case '=': parse_utils->current_token.token_type = TOK_AFFECTATION;
            break;
        case ',': parse_utils->current_token.token_type = TOK_COMMA;
            break;
        default: parse_utils->current_token.token_type = TOK_ERROR;
            break;
    }
    return (false);
}

void    pop_token(t_parse_utils *parse_utils, bool *is_comment)
{
    skip_space(parse_utils);
    init_token(&parse_utils->current_token);
    parse_utils->nb_token++;
    if (set_token(parse_utils, is_comment))
        return ;
    if (parse_utils->current_token.token_type != TOK_ERROR)
    {
        parse_utils->current_token.value_symbol =
            parse_utils->line[parse_utils->index];
        parse_utils->index++;
    }
    else
    {
        fprintf(stderr, "Parse Error: Unexpected token '%c' at position %lu\n",
            parse_utils->line[parse_utils->index], parse_utils->index);
        exit(0);
    }
}
