#ifndef             _PARSER_H_
# define            _PARSER_H_

# include            <ast.h>
# include            <stdbool.h>
# include            <stddef.h>
# include            <token.h>
# include            <variables.h>

typedef struct      s_parse_utils
{
    t_var_type      decla_type;
    size_t          index;
    size_t          nb_token;
    const char      *line;
    t_token         current_token;
}                   t_parse_utils;

t_ast_node          *affectation(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);
void                expect(char expected, t_parse_utils *parse_utils, bool *is_comment);
t_ast_node          *expression(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);
t_ast_node          *expression1(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);
t_ast_node          *factor(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);
void                get_number(t_parse_utils *parse_utils);
char                get_char(t_parse_utils *parse_utils);
const char          *get_string(t_parse_utils *parse_utils);
const char          *get_variable_name(t_parse_utils *parse_utils);
void                init_parse_utils(t_parse_utils *parse_utils, const char *line);
bool                is_affectation(const char *line);
bool                is_white_line(const char *line, bool *is_comment);
t_ast_node          *parse(const char *line, t_var_list *var_list, bool *is_comment);
void                pop_line(t_parse_utils *parse_utils, bool *is_comment);
void                pop_line_until_endcomment(t_parse_utils *parse_utils, bool *is_comment);
void                pop_token(t_parse_utils *parse_utils, bool *is_comment);
bool                set_token(t_parse_utils *parse_utils, bool *is_comment);
void                skip_space(t_parse_utils *parse_utils);
t_ast_node          *term(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);
t_ast_node          *term1(t_parse_utils *parse_utils, t_var_list *var_list, bool *is_comment);

#endif              /* _PARSER_H_ */
