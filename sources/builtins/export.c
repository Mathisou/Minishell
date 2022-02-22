/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:46 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 11:02:06 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_line_to_export(char *line)
{
    int i;

    i = -1;
    while (line[++i] && line[i] != '=')
        if (!((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122) || line[i] == 95))
            return (1);
    if (line[i])
        return (0);
    else
        return (1);
}

void    export(t_env **lst, char *to_export)
{
    if (check_line_to_export(to_export) == 0)
        add_node_back(lst, to_export);
}