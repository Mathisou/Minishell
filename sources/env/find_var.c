/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:17:59 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/17 14:41:06 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_var(char **env, char *var)
{
    int i;
    int j;

    i = -1;
    while (env[++i])
    {     
        j = -1;
        while (env[i][++j] && var[j])
            if (env[i][j] != var[j])
                break ;
        if (var[j] == 0)
            return ((ft_strdup(env[i] + ft_strlen(var))));
    }
	return (NULL); // \n quand pas trouver
}
