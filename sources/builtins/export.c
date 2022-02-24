/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:46 by maroly            #+#    #+#             */
/*   Updated: 2022/02/24 13:39:25 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    replace_line(t_env **lst, char *to_export)
{
    t_env *tmp;
    char *str_export;
    int i;

    tmp = *lst;
    i = -1;
    str_export = ft_strdup(to_export);
    while (str_export[++i] && str_export[i] != '=')
        ;
    str_export[i] = '\0';
    while (tmp && ft_strncmp(tmp->var, str_export, i))
        tmp =  tmp->next;
    free(str_export);
    free(tmp->var);
    tmp->var = ft_strdup(to_export);
}

int check_line_to_export(char *line, t_env **lst)
{
    t_env *tmp;
    int i;
    char *str;

    i = -1;
    tmp = *lst;
    str = NULL;
    while (line[++i] && line[i] != '=')
        if (!((line[i] >= 65 && line[i] <= 90)
            || (line[i] >= 97 && line[i] <= 122) || line[i] == 95))
            return (2);
    if (line[i])
    {
        str = ft_strdup(line);
        str[i] = '\0';
        while (tmp)
        {
            if (ft_strncmp(tmp->var, str, i) == 0)
            {
                free(str);
                return (1);
            }
            tmp = tmp->next;
        }
        free(str);
        return (0);
    }
    else
        return (2);
}

void    export(t_env **lst, char **to_export)
{
    int i;
    int rtn;

    i = 0;
    while (to_export[++i])
    {
        rtn = check_line_to_export(to_export[i], lst);
        if (rtn == 0)
            add_node_back(lst, to_export[i]);
        else if (rtn == 1)
            replace_line(lst, to_export[i]);
        else
            ft_putstr_fd("Syntax error!\n", 2);
    }
}