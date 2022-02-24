/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:15:49 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/24 16:46:26 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env(char   **env, t_env **envi)
{
	int		i;
	char	*new_shlvl;

	i = -1;
	new_shlvl = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			new_shlvl = strcats("SHLVL=", ft_itoa(ft_atoi(&env[i][6]) + 1));
			add_node_back(envi, new_shlvl);
			free(new_shlvl);
		}
		else
			add_node_back(envi, env[i]);
	}
}

char **convert_env(t_env **lst)
{
	t_env	*tmp;
	char	**big;
	int		i;
	int		size;

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
