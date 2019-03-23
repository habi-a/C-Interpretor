#ifndef                 _FUNCTIONS_H_
# define                _FUNCTIONS_H_

# include               <ast.h>
# include               <stdbool.h>
# include               <stddef.h>
# include               <variables.h>

typedef void            (*t_ptr_built_in)(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);

typedef enum            e_func_type
{
                        FUNC_BUILT_IN,
                        FUNC_CUSTOM
}                       t_func_type;

typedef struct          s_func_node
{
    const char          *func_name;
    t_var_type          return_type;
    t_func_type         func_type;
    t_ptr_built_in      ptr_built_in;
    struct s_func_node  *next;
}                       t_func_node;

typedef struct          s_func_list
{
    size_t              size;
    t_func_node         *first;
    t_func_node         *last;

}                       t_func_list;

void				    init_list_functions(t_func_list *list);
t_func_node             *get_function(t_func_list *list, const char *func_name);
void                    push_back_function(t_func_list *list, const char *func_name, t_ptr_built_in function_b_in);
void                    fill_built_int_functions(t_func_list *list);
void	                free_list_functions(t_func_list *list);
void                    my_abs(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_min(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_max(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_pow(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_rand(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_at(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_len(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_int_to_string(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_float_to_string(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_string_to_int(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_string_to_float(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_print(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_putchar(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_putnbr(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_putnbr_float(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_putbool(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_scan(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_open(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_read(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_readline(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_write(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_close(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_is_open(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);
void                    my_br(t_ast_node *ast_node, t_ast_node *ast_node1, t_ast_node *ast_node2);

#endif                  /* _FUNCTIONS_H_ */
