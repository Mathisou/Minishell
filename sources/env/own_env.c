/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:15:49 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/26 13:31:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env(char   **env, t_env **envi)
{
	int		i;
	char	*new_shlvl;
	char 	*rtn_itoa;
	int		exist[2];

	i = -1;
	new_shlvl = NULL;
	exist[0] = 0;
	exist[1] = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			exist[1]++;
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			rtn_itoa = ft_itoa(ft_atoi(&env[i][6]) + 1);
			new_shlvl = strcats("SHLVL=", rtn_itoa);
			add_node_back(envi, new_shlvl);
			free(new_shlvl);
			free(rtn_itoa);
			exist[0]++;
		}
		else
			add_node_back(envi, env[i]);
	}
	if (!exist[0])
		add_node_back(envi, "SHLVL=1");
	if (!exist[1])
	{
		new_shlvl = getcwd(NULL, 4096 + 1);
		rtn_itoa = strcats("PWD=", new_shlvl);
		add_node_back(envi, rtn_itoa);
		free(new_shlvl);
		free(rtn_itoa);
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
