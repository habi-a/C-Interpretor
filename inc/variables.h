#ifndef                 _VARIABLES_H_
# define                _VARIABLES_H_

# include               <stdbool.h>
# include               <stddef.h>
# include               <stdio.h>

typedef enum            e_var_type
{
                        T_UNDEFINED,
                        T_BOOL,
                        T_CHAR,
                        T_INT,
                        T_FLOAT,
                        T_STRING,
                        T_FILE,
                        T_VOID,
                        T_NULL
}                       t_var_type;

typedef struct          s_var_node
{
    const char          *var_name;
    t_var_type          var_type;
    bool                value_bool;
    int                 value_int;
    float               value_float;
    char                value_char;
    char                *value_string;
    FILE                *value_file;
    struct s_var_node   *next;
}                       t_var_node;

typedef struct          s_var_list
{
    size_t              size;
    t_var_node          *first;
    t_var_node          *last;
    
}                       t_var_list;

void				    init_list_variables(int argc, char **argv, t_var_list *list);
t_var_node              *get_variable(t_var_list *list, const char *var_name);
void	                free_list_variables(t_var_list *list);

#endif                  /* _VARIABLES_H_ */
