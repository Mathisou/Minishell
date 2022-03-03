/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:04:11 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 11:19:51 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

static char	***find_opt2(char ***bt, t_opt *nrm, t_global *global)
{
	while (bt[nrm->i][nrm->j] && check_limiter(bt[nrm->i][nrm->j]) == 0)
		nrm->j++;
	nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * (nrm->j + 1));
	if (!nrm->cmdopt[nrm->k])
		return (NULL);
	nrm->m = -1;
	while (++nrm->m < nrm->j)
	{
		nrm->cmdopt[nrm->k][nrm->m] = ft_strdup(bt[nrm->i][nrm->m]);
		if (!nrm->cmdopt[nrm->k][nrm->m])
			free_n_exit(global);
	}
	nrm->cmdopt[nrm->k][nrm->m] = NULL;
	return ((char ***)1);
}

static int	is_last_here_doc(char **t)
{
	int i;
	int sign;

	i = -1;
	sign = 0;
	while (t[++i])
	{
		if (ft_strcmp(t[i], "<") == 0)
			sign = 1;
		else if (ft_strcmp(t[i], "<<") == 0)
			sign = 2;
	}
	if (sign == 2)
		return (1);
	else
		return (0);
}

static char	***find_opt3(char ***bt, t_opt *nrm, t_global *global)
{
	while (ft_strcmp(bt[nrm->i][nrm->j], "<") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], "<<") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], ">") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], ">>") == 0)
		nrm->j = nrm->j + 2;
	nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * 3);
	if (!nrm->cmdopt[nrm->k])
		return (NULL);
	if (bt[nrm->i][nrm->j])
	{
		nrm->cmdopt[nrm->k][0] = ft_strdup(bt[nrm->i][nrm->j]);
		if (!nrm->cmdopt[nrm->k][0])
			free_n_exit(global);
		if (is_last_here_doc(bt[nrm->i]) == 1)
		{
			nrm->cmdopt[nrm->k][1] = ft_strdup("here_doc");
			nrm->cmdopt[nrm->k][2] = NULL;
		}
		else
			nrm->cmdopt[nrm->k][1] = NULL;
	}
	else
		nrm->cmdopt[nrm->k][0] = NULL;
	return ((char ***)1);
}

char	***find_opt(char ***bt, t_global *global)
{
	t_opt	nrm;

	nrm.i = -1;
	nrm.k = 0;
	nrm.cmdopt = malloc(sizeof(*nrm.cmdopt) * (count_triple_tab(bt) + 1));
	if (!nrm.cmdopt)
		return (NULL);
	while (bt[++nrm.i])
	{
		nrm.j = 0;
		if (!(ft_strcmp(bt[nrm.i][0], "<") == 0
			|| ft_strcmp(bt[nrm.i][0], "<<") == 0
			|| ft_strcmp(bt[nrm.i][0], ">") == 0
			|| ft_strcmp(bt[nrm.i][0], ">>") == 0))
		{
			if (!find_opt2(bt, &nrm, global))
				return (NULL);
		}
		else
			if (!find_opt3(bt, &nrm, global))
				return (NULL);
		nrm.k++;
	}
	nrm.cmdopt[nrm.k] = NULL;
	return (nrm.cmdopt);
}

int	find_cmd(t_global *global)
{
	int	i;
	int	j;

	i = -1;
	global->parse->cmd = malloc(sizeof(*global->parse->cmd)
			* (count_triple_tab(global->parse->bt) + 1));
	if (!global->parse->cmd)
		return (1);
	*global->parse->cmd = 0;
	while (global->parse->bt[++i])
	{
		j = 0;
		while (ft_strcmp(global->parse->bt[i][j], "<") == 0
		|| ft_strcmp(global->parse->bt[i][j], "<<") == 0
		|| ft_strcmp(global->parse->bt[i][j], ">") == 0
		|| ft_strcmp(global->parse->bt[i][j], ">>") == 0)
			j = j + 2;
		if (global->parse->bt[i][j])
			global->parse->cmd[i]
			= findpath(ft_strdup(global->parse->bt[i][j]), global->envi, global);
	}
	global->parse->cmd[i] = NULL;
	return (0);
}
