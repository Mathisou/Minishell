/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:04:11 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 01:03:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *str)
{
	if (ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

static char	***find_opt2(char **bt, t_opt *nrm, t_global *global)
{
	int	start;
	int	z;

	start = 0;
	while (bt[nrm->j + start] && (check_limiter(bt[nrm->j + start]) == 0
			&& ft_strcmp(bt[nrm->j + start], "|") != 0))
		start++;
	nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * (start + 1));
	if (!nrm->cmdopt[nrm->k])
		return (NULL);
	z = nrm->j - 1;
	while (++z < nrm->j + start)
	{
		nrm->cmdopt[nrm->k][nrm->m] = ft_strdup(bt[nrm->m + nrm->j]);
		if (!nrm->cmdopt[nrm->k][nrm->m])
			free_n_exit(global);
		nrm->m++;
	}
	nrm->cmdopt[nrm->k][nrm->m] = NULL;
	return ((char ***)1);
}

static void	find_opt4(char ***bt, t_opt *nrm)
{
	if (bt[nrm->i][nrm->j] && nrm->cmdopt[nrm->k][1] == NULL)
	{
		destroy_tab_size(nrm->cmdopt[nrm->k], cmdopt_size(nrm->cmdopt[nrm->k]));
		if (is_last_here_doc(bt[nrm->i]) == 1)
		{
			nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * 3);
			nrm->cmdopt[nrm->k][0] = ft_strdup(bt[nrm->i][nrm->j]);
			nrm->cmdopt[nrm->k][1] = ft_strdup("here_doc");
			nrm->cmdopt[nrm->k][2] = NULL;
		}
		else
		{
			nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * 2);
			nrm->cmdopt[nrm->k][0] = ft_strdup(bt[nrm->i][nrm->j]);
			nrm->cmdopt[nrm->k][1] = NULL;
		}
	}
}

static char	***find_opt3(char ***bt, t_opt *nrm, t_global *global)
{
	while (ft_strcmp(bt[nrm->i][nrm->j], "<") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], "<<") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], ">") == 0
		|| ft_strcmp(bt[nrm->i][nrm->j], ">>") == 0)
		nrm->j = nrm->j + 2;
	if (bt[nrm->i][nrm->j])
		find_opt2(bt[nrm->i], nrm, global);
	else
	{
		nrm->cmdopt[nrm->k] = malloc(sizeof(char *) * 1);
		nrm->cmdopt[nrm->k][0] = NULL;
	}
	find_opt4(bt, nrm);
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
		nrm.m = 0;
		if (!find_opt3(bt, &nrm, global))
			return (NULL);
		nrm.k++;
	}
	nrm.cmdopt[nrm.k] = NULL;
	return (nrm.cmdopt);
}
