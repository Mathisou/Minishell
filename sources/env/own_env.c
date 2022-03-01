/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:15:49 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 14:46:07 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env2(char **env, t_env **envi, t_takee *nrm)
{
	while (env[++nrm->i])
	{
		if (ft_strncmp(env[nrm->i], "PWD=", 4) == 0)
			nrm->exist[1]++;
		if (ft_strncmp(env[nrm->i], "SHLVL=", 6) == 0)
		{
			nrm->rtn_itoa = ft_itoa(ft_atoi(&env[nrm->i][6]) + 1);
			nrm->new_shlvl = strcats("SHLVL=", nrm->rtn_itoa);
			add_node_back(envi, nrm->new_shlvl);
			free(nrm->new_shlvl);
			free(nrm->rtn_itoa);
			nrm->exist[0]++;
		}
		else
			add_node_back(envi, env[nrm->i]);
	}
}

void	take_env(char **env, t_env **envi)
{
	t_takee	nrm;

	nrm.i = -1;
	nrm.new_shlvl = NULL;
	nrm.exist[0] = 0;
	nrm.exist[1] = 0;
	take_env2(env, envi, &nrm);
	if (!nrm.exist[0])
		add_node_back(envi, "SHLVL=1");
	if (!nrm.exist[1])
	{
		nrm.new_shlvl = getcwd(NULL, 4096 + 1);
		nrm.rtn_itoa = strcats("PWD=", nrm.new_shlvl);
		add_node_back(envi, nrm.rtn_itoa);
		free(nrm.new_shlvl);
		free(nrm.rtn_itoa);
	}
}

char	**convert_env(t_env **lst)
{
	t_env	*tmp;
	char	**big;
	int		i;
	int		size;

	i = 0;
	tmp = *lst;
	size = lst_size(lst);
	if (size == 0)
		return (NULL);
	big = malloc(sizeof(*big) * (size + 1));
	if (!big)
		return (NULL);
	while (tmp)
	{
		big[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	big[i] = NULL;
	return (big);
}
