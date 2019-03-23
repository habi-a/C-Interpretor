#ifndef _INTERPRETER_H
# define    _INTERPRETER_H

# include   <ast.h>
# include   <functions.h>
# include   <variables.h>

t_ast_node  *interpret(t_ast_node *ast, t_var_list *var_list, t_func_list *func_list);

#endif      /* _INTERPRETER_H_ */
