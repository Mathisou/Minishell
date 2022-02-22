/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:15:49 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/22 18:05:51 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env(char   **env, t_env **envi)
{
	int		i;

	i = -1;
	while (env[++i])
		add_node_back(envi, env[i]);
}

char **convert_env(t_env **lst)
{
	t_env *tmp;
	char **big;
	int i;
	int size;

	i = 0;
	tmp = *lst;
	size = lst_size(lst);
	if (size == 0)
		return (NULL); //a securiser
	big = malloc(sizeof(*big) * (size + 1));
	if (!big)
		return (NULL); // a securiser
	while (tmp)
	{
		big[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	big[i] = NULL;
	return (big);
}
