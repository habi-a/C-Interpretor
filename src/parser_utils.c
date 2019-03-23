#include <ctype.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>

void        init_parse_utils(t_parse_utils *parse_utils, const char *line)
{
    parse_utils->index = 0;
    parse_utils->line = line;
    parse_utils->nb_token = 0;
    parse_utils->decla_type = T_UNDEFINED;
}

bool        is_affectation(const char *line)
{
    size_t  i;
    bool    is_comment_tmp;
    bool    is_string;
    bool    is_char;

    i = 0;
    is_comment_tmp = false;
    is_string = false;
    is_char = false;
    while (line[i] != '\0')
    {
        if (line[i] == '/' && line[i + 1] == '*' && !is_comment_tmp && !is_string)
        {
            is_comment_tmp = true;
            i++;
        }
        else if (line[i] == '*' && line[i + 1] == '/' && is_comment_tmp && !is_string)
        {
            is_comment_tmp = false;
            i++;
        }
        else if (line[i] == '/' && line[i + 1] == '/' && !is_comment_tmp && !is_string)
            break;
        else if (line[i] == '"' && !is_comment_tmp && !is_string && !is_char)
            is_string = true;
        else if (line[i] == '"' && !is_comment_tmp && !is_char)
            is_string = false;
        else if (line[i] == '\'' && !is_comment_tmp && !is_string && !is_char)
            is_char = true;
        else if (line[i] == '\'' && !is_comment_tmp && !is_string)
            is_char = false;
        else if (line[i] == '=' && !is_comment_tmp && !is_string && !is_char)
            return (true);
        i++;
    }
    return (false);
}

bool        is_white_line(const char *line, bool *is_comment)
{
    size_t  i;
    bool    is_comment_tmp;

    i = 0;
    is_comment_tmp = *is_comment;
    while (line[i] != '\0')
    {
        if (line[i] == '/' && line[i + 1] == '*' && !is_comment_tmp)
        {
            is_comment_tmp = true;
            i++;
        }
        else if (line[i] == '*' && line[i + 1] == '/' && is_comment_tmp)
        {
            is_comment_tmp = false;
            i++;
        }
        else if (line[i] == '/' && line[i + 1] == '/' && !is_comment_tmp)
            break;
        else if (!isspace(line[i]) && !is_comment_tmp)
            return (false);
        i++;
    }
    *is_comment = is_comment_tmp;
    return (true);
}

void        skip_space(t_parse_utils *parse_utils)
{
    while (isspace(parse_utils->line[parse_utils->index]))
        parse_utils->index++;
}

void        get_number(t_parse_utils *parse_utils)
{
    int     result_int;
    float   result_float;
    char    result_buffer[32] = {0};
    size_t  old_index;

    skip_space(parse_utils);
    old_index = parse_utils->index;
    while (isdigit(parse_utils->line[parse_utils->index]))
        parse_utils->index++;
    if (parse_utils->line[parse_utils->index] == '.')
    {
        parse_utils->current_token.var_type = T_FLOAT;
        parse_utils->index++;
        while (isdigit(parse_utils->line[parse_utils->index]))
            parse_utils->index++;
    }
    else
        parse_utils->current_token.var_type = T_INT;
    if (parse_utils->index - old_index == 0)
    {
        fprintf(stderr, "Parse Error: Expected number at position %lu\n", old_index);
        exit(0);
    }
    strncpy(result_buffer, parse_utils->line + old_index, parse_utils->index - old_index);
    if (parse_utils->current_token.var_type == T_INT)
    {
        result_int = atoi(result_buffer);
        parse_utils->current_token.value_int = result_int;
        parse_utils->current_token.value_float = result_int;
    }
    else
    {
        result_float = (float)atof(result_buffer);
        parse_utils->current_token.value_float = result_float;
        parse_utils->current_token.value_int = (int)result_float;
    }
}

void            pop_line(t_parse_utils *parse_utils, bool *is_comment)
{
    while (parse_utils->line[parse_utils->index] != '\0')
        parse_utils->index++;
    pop_token(parse_utils, is_comment);
}

void            pop_line_until_endcomment(t_parse_utils *parse_utils, bool *is_comment)
{
    while (parse_utils->line[parse_utils->index] != '\0')
    {
        if (parse_utils->line[parse_utils->index] == '*' && parse_utils->line[parse_utils->index + 1] == '/')
        {
            *is_comment = false;
            parse_utils->index += 2;
            break;
        }
        parse_utils->index++;
    }
    pop_token(parse_utils, is_comment);
}

const char      *get_string(t_parse_utils *parse_utils)
{
    char        *result_buffer;
    size_t      old_index;

    parse_utils->index++;
    old_index = parse_utils->index;
    while (parse_utils->line[parse_utils->index] != '"')
        parse_utils->index++;
    if (parse_utils->index - old_index == 0)
    {
        fprintf(stderr, "Parse Error: Expected string at position %lu\n", old_index);
        exit(0);
    }
    result_buffer = malloc((parse_utils->index - old_index + 1) * (sizeof(char)));
    strncpy(result_buffer, parse_utils->line + old_index, parse_utils->index - old_index);
    result_buffer[parse_utils->index - old_index] = '\0';
    parse_utils->index++;
    return (result_buffer);
}

char            get_char(t_parse_utils *parse_utils)
{
    char        result;

    parse_utils->index++;
    result = parse_utils->line[parse_utils->index];
    parse_utils->index++;
    if (parse_utils->line[parse_utils->index] != '\'')
    {
        fprintf(stderr, "Parse Error: Expected ' at position %lu\n", parse_utils->index);
        exit(0);
    }
    parse_utils->index++;
    return (result);
}

static bool     type_exist_and_set(t_parse_utils *parse_utils, const char *type)
{
    size_t      i;
    bool        t_exist;
    const char  *available_type[5];

    if ((available_type[0] = strdup("bool")) == NULL)
        return (false);
    if ((available_type[1] = strdup("char")) == NULL)
        return (false);
    if ((available_type[2] = strdup("int")) == NULL)
        return (false);
    if ((available_type[3] = strdup("float")) == NULL)
        return (false);
    if ((available_type[4] = strdup("string")) == NULL)
        return (false);
    if ((available_type[5] = strdup("file")) == NULL)
        return (false);
    i = 0;
    t_exist = false;
    while (i < 6)
    {
        if (!strcmp(type, available_type[i]))
        {
            t_exist = true;
            parse_utils->current_token.var_type = (t_var_type)(i + 1);
        }
        free((char *)available_type[i]);
        i++;
    }
    return (t_exist);
}

const char  *get_variable_name(t_parse_utils *parse_utils)
{
    char    *result_buffer;
    size_t  old_index;

    skip_space(parse_utils);
    old_index = parse_utils->index;
    while (isalnum(parse_utils->line[parse_utils->index])
            || parse_utils->line[parse_utils->index] == '_')
        parse_utils->index++;
    if (parse_utils->index - old_index == 0)
    {
        fprintf(stderr, "Parse Error: Expected variable name at position %lu\n", old_index);
        exit(0);
    }
    result_buffer = malloc((parse_utils->index - old_index + 1) * (sizeof(char)));
    strncpy(result_buffer, parse_utils->line + old_index, parse_utils->index - old_index);
    result_buffer[parse_utils->index - old_index] = '\0';
    if (parse_utils->line[parse_utils->index] == '(')
        parse_utils->current_token.token_type = TOK_FUNC_CALL;
    else if (type_exist_and_set(parse_utils, result_buffer))
        parse_utils->current_token.token_type = TOK_DECLARATION;
    else if (!strcmp(result_buffer, "true"))
    {
        parse_utils->current_token.token_type = TOK_BOOL;
        parse_utils->current_token.var_type = T_BOOL;
        parse_utils->current_token.value_bool = true;
    }
    else if (!strcmp(result_buffer, "false"))
    {
        parse_utils->current_token.token_type = TOK_BOOL;
        parse_utils->current_token.var_type = T_BOOL;
        parse_utils->current_token.value_bool = false;
    }
    return (result_buffer);
}

void        expect(char expected, t_parse_utils *parse_utils, bool *is_comment)
{
    if (parse_utils->line[parse_utils->index - 1] == expected)
        pop_token(parse_utils, is_comment);
    else
    {
       fprintf(stderr, "Parse Error: Expected token '%c' at position %lu\n",
           expected, parse_utils->index);
       exit(0);
    }
}
