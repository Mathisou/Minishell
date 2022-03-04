/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:15:49 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/04 17:29:26 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env2(char **env, t_env **envi, t_takee *nrm, t_global *global)
{
	while (env[++nrm->i])
	{
		if (ft_strncmp(env[nrm->i], "_=", 2) == 0)
			nrm->exist[2]++;
		if (ft_strncmp(env[nrm->i], "PWD=", 4) == 0)
			nrm->exist[1]++;
		if (ft_strncmp(env[nrm->i], "SHLVL=", 6) == 0)
		{
			nrm->rtn_itoa = ft_itoa(ft_atoi(&env[nrm->i][6]) + 1);
			nrm->new_shlvl = strcats("SHLVL=", nrm->rtn_itoa);
			if (!nrm->new_shlvl)
			{
				free(nrm->rtn_itoa);
				free_n_exit(global);
			}
			add_node_back(envi, nrm->new_shlvl, global);
			free(nrm->new_shlvl);
			free(nrm->rtn_itoa);
			nrm->exist[0]++;
		}
		else
			add_node_back(envi, env[nrm->i], global);
	}
}

static void	take_env3(t_env **envi, char *av, t_takee *nrm, t_global *global)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(NULL, 4096 + 1);
	nrm->new_shlvl = strcats("_=", tmp);
	free(tmp);
	if (!nrm->new_shlvl)
		free_n_exit(global);
	tmp = strcats(nrm->new_shlvl, "/");
	if (!tmp)
	{
		free(nrm->new_shlvl);
		free_n_exit(global);
	}
	nrm->rtn_itoa = strcats(tmp, av);
	if (!nrm->rtn_itoa)
	{
		free(tmp);
		free_n_exit(global);
	}
	add_node_back(envi, nrm->rtn_itoa, global);
	free(nrm->new_shlvl);
	free(nrm->rtn_itoa);
	free(tmp);
}

static void	init_local(t_takee *nrm)
{
	nrm->i = -1;
	nrm->new_shlvl = NULL;
	nrm->rtn_itoa = NULL;
	nrm->exist[0] = 0;
	nrm->exist[1] = 0;
	nrm->exist[2] = 0;
}

void	take_env(char **env, t_env **envi, char *av, t_global *global)
{
	t_takee	nrm;

	init_local(&nrm);
	take_env2(env, envi, &nrm, global);
	if (!nrm.exist[0])
		add_node_back(envi, "SHLVL=1", global);
	if (!nrm.exist[2])
		take_env3(envi, av, &nrm, global);
	if (!nrm.exist[1])
	{
		nrm.new_shlvl = getcwd(NULL, 4096 + 1);
		nrm.rtn_itoa = strcats("PWD=", nrm.new_shlvl);
		if (!nrm.rtn_itoa)
		{
			free(nrm.new_shlvl);
			free_n_exit(global);
		}
		add_node_back(envi, nrm.rtn_itoa, global);
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

	i = -1;
	tmp = *lst;
	size = lst_size(lst);
	if (size == 0)
		return (NULL);
	big = malloc(sizeof(*big) * (size + 1));
	if (!big)
		return (NULL);
	while (tmp)
	{
		big[++i] = ft_strdup(tmp->var);
		if (!big[i])
		{
			destroy_tab(big);
			return (NULL);
		}
		tmp = tmp->next;
	}
	big[++i] = NULL;
	return (big);
}
