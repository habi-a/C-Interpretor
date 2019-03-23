#include <ast.h>
#include <functions.h>
#include <interpreter.h>
#include <parser.h>
#include <repl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <variables.h>

static void     ante(const char *cin, t_var_list *var_list, t_func_list *func_list, bool *is_comment)
{
    t_ast_node  *ast_node;

    ast_node = parse(cin, var_list, is_comment);
    interpret(ast_node, var_list, func_list);
    destruct_astnode(ast_node);
}

static void     loop_repl(t_var_list *var_list, t_func_list *func_list, bool *is_comment)
{
    char        *cin;
    bool        repl_exit;
    size_t      size_cin;

    cin = NULL;
    size_cin = 0;
    repl_exit = false;
    printf("> ");
    while (getline(&cin, &size_cin, stdin) != -1 && cin && !repl_exit)
    {
        cin[strlen(cin) - 1] = '\0';
        if (!strcmp(cin, "exit"))
            repl_exit = true;
        else if (!is_white_line(cin, is_comment))
            ante(cin, var_list, func_list, is_comment);
        free(cin);
        cin = NULL;
        size_cin = 0;
	if (!repl_exit)
	    printf("\n> ");
	else
	    break;
    }
    free(cin);
}

void            launch_repl(int argc, char **argv)
{
    bool        is_comment;
    t_var_list  var_list;
    t_func_list func_list;

    is_comment = false;
    init_list_variables(argc, argv, &var_list);
    init_list_functions(&func_list);
    fill_built_int_functions(&func_list);
    puts("Welcome to the C-Interpetor by habi-a");
    loop_repl(&var_list, &func_list, &is_comment);
    free_list_variables(&var_list);
    free_list_functions(&func_list);
}
