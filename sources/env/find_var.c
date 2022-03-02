/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:17:59 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/02 17:03:55 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(t_env **lst, char *var)
{
	t_env	*tmp;
	int		j;

	tmp = *lst;
	while (tmp)
	{
		j = -1;
		while (tmp->var[++j] && var[j])
			if (tmp->var[j] != var[j])
				break ;
		if (var[j] == 0)
			return ((ft_strdup(tmp->var + ft_strlen(var) + 1)));
		tmp = tmp->next;
	}
	return (NULL);
}
