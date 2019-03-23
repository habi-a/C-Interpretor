#ifndef             _TOKEN_H_
# define            _TOKEN_H_

# include           <variables.h>
# include            <stdio.h>

typedef enum        e_token_type
{
                    TOK_NUMBER,
                    TOK_CHAR,
                    TOK_STRING,
                    TOK_BOOL,
                    TOK_PLUS,
                    TOK_MINUS,
                    TOK_MUL,
                    TOK_DIV,
                    TOK_MOD,
                    TOK_LEFT_PAREN,
                    TOK_RIGHT_PAREN,
                    TOK_AFFECTATION,
                    TOK_DECLARATION,
                    TOK_COMMA,
                    TOK_FUNC_CALL,
                    TOK_VARIABLE,
                    TOK_END_TEXT,
                    TOK_ERROR
}                   t_token_type;

typedef struct      s_token
{
    t_token_type    token_type;
    const char      *var_name;
    t_var_type      var_type;
    bool            value_bool;
    int             value_int;
    float           value_float;
    char            value_char;
    const char      *value_string;
    FILE            *value_file;
    char            value_symbol;
}                   t_token;

void                init_token(t_token *token);

#endif              /* _TOKEN_H_ */
