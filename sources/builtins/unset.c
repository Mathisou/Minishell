/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:49 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 11:25:24 by maroly           ###   ########.fr       */
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

void    unset(char *to_unset, t_env **lst)
{
    t_env *tmp;

    tmp = *lst;
    if (is_var(tmp->var, to_unset) == 0)
    {
        if (tmp->next)
            *lst = (*lst)->next;
        else
        {
            free(*lst);
            *lst = NULL;
        }
       // return ;
    }
    while (tmp->next && is_var(tmp->next->var, to_unset) == 1)
        tmp = tmp->next;
    if (tmp->next)
    {
        if (tmp->next->next)
        {
            //free(tmp->next);
            tmp->next = tmp->next->next;
        }
        else
        {
            //free(tmp->next);
            tmp->next = NULL;
        }
    }
}