/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/24 13:42:49 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_var(char *var, char *to_unset)
{
    int i;
    char *str;

    i = -1;
    str = ft_strdup(var);
    if (!str)
        return (2); // a securiser
    while (str[++i] && str[i] != '=')
        ;
    str[i] = '\0';
    if (ft_strcmp(str, to_unset) == 0)
    {
        free(str);
        return (0);
    }
    else
    {
        free(str);
        return (1);
    }
}

void    unset(char **to_unset, t_env **lst)
{
    int i;
    t_env *tmp;
    t_env *save;

    tmp = *lst;
    i = 0;
    while (to_unset[++i])
    {
        if (is_var(tmp->var, to_unset[i]) == 0)
        {
            if (tmp->next)
            {
                //free(*lst);
                *lst = (*lst)->next; // a free
            }
            else
            {
                free(*lst);
                *lst = NULL;
            }
        }
        while (tmp->next && is_var(tmp->next->var, to_unset[i]) == 1)
            tmp = tmp->next;
        if (tmp->next)
        {
            if (tmp->next->next)
            {
                save = tmp->next;
                tmp->next = tmp->next->next;
                free(save->var);
                free(save);
                save = NULL;
            }
            else
            {
                free(tmp->next->var);
                free(tmp->next);
                tmp->next = NULL;
            }
        }
    }
}