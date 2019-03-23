#include <variables.h>
#include <stdlib.h>
#include <string.h>

void			init_list_variables(int argc, char **argv, t_var_list *list)
{
    t_var_node  *new_element;

    (void) argv;
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    new_element = malloc(sizeof(t_var_node));
    if (new_element == NULL)
        return ;
    new_element->var_name = strdup("argc");
    if (new_element->var_name == NULL)
        return ;
    new_element->var_type = T_INT;
    new_element->value_float = argc;
    new_element->value_int = argc;
    new_element->value_bool = (bool)argc;
    new_element->value_char = (char)argc;
    new_element->value_string = NULL;
    new_element->value_file = NULL;
    new_element->next = NULL;
    list->size++;
    if (list->last != NULL)
        list->last->next = new_element;
    else
        list->first = new_element;
    list->last = new_element;
}

t_var_node      *get_variable(t_var_list *list, const char *var_name)
{
    t_var_node  *tmp;

    tmp = list->first;
    while (tmp)
    {
        if (!strcmp(tmp->var_name, var_name))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}


void			free_list_variables(t_var_list *list)
{
    t_var_node	*tmp;
    t_var_node	*p_elem;

    if (list == NULL)
        return ;
    p_elem = list->first;
    while (p_elem != NULL)
    {
        tmp = p_elem;
        p_elem = p_elem->next;
        free((char *)tmp->var_name);
        if (tmp->var_type == T_STRING && tmp->value_string != NULL)
            free(tmp->value_string);
        free(tmp);
    }
    list->first = NULL;
    list->last = NULL;
}
