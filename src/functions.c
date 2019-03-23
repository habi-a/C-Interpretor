#include <functions.h>
#include <stdlib.h>
#include <string.h>

void			init_list_functions(t_func_list *list)
{
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
}

t_func_node      *get_function(t_func_list *list, const char *func_name)
{
    t_func_node  *tmp;

    tmp = list->first;
    while (tmp)
    {
        if (!strcmp(tmp->func_name, func_name))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

void            push_back_function(t_func_list *list, const char *func_name, t_ptr_built_in function_b_in)
{
    t_func_node *new_element;

    new_element = malloc(sizeof(t_func_node));
    if (new_element == NULL)
        return ;
    new_element->func_name = func_name;
    new_element->func_type = FUNC_BUILT_IN;
    new_element->ptr_built_in = function_b_in;
    new_element->next = NULL;
    list->size++;
    if (list->last != NULL)
        list->last->next = new_element;
    else
        list->first = new_element;
    list->last = new_element;
}

void            fill_built_int_functions(t_func_list *list)
{
    push_back_function(list, strdup("abs"), &my_abs);
    push_back_function(list, strdup("min"), &my_min);
    push_back_function(list, strdup("max"), &my_max);
    push_back_function(list, strdup("pow"), &my_pow);
    push_back_function(list, strdup("rand"), &my_rand);
    push_back_function(list, strdup("at"), &my_at);
    push_back_function(list, strdup("len"), &my_len);
    push_back_function(list, strdup("int_to_string"), &my_int_to_string);
    push_back_function(list, strdup("float_to_string"), &my_float_to_string);
    push_back_function(list, strdup("string_to_int"), &my_string_to_int);
    push_back_function(list, strdup("string_to_float"), &my_string_to_float);
    push_back_function(list, strdup("print"), &my_print);
    push_back_function(list, strdup("putchar"), &my_putchar);
    push_back_function(list, strdup("putnbr"), &my_putnbr);
    push_back_function(list, strdup("putnbr_float"), &my_putnbr_float);
    push_back_function(list, strdup("putbool"), &my_putbool);
    push_back_function(list, strdup("scan"), &my_scan);
    push_back_function(list, strdup("open"), &my_open);
    push_back_function(list, strdup("read"), &my_read);
    push_back_function(list, strdup("readline"), &my_readline);
    push_back_function(list, strdup("write"), &my_write);
    push_back_function(list, strdup("close"), &my_close);
    push_back_function(list, strdup("is_open"), &my_is_open);
    push_back_function(list, strdup("br"), &my_br);
}

void			free_list_functions(t_func_list *list)
{
    t_func_node	*tmp;
    t_func_node	*p_elem;

    if (list == NULL)
        return ;
    p_elem = list->first;
    while (p_elem != NULL)
    {
        tmp = p_elem;
        p_elem = p_elem->next;
        free((char *)tmp->func_name);
        free(tmp);
    }
    list->first = NULL;
    list->last = NULL;
}
