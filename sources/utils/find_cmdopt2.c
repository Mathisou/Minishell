/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:50:25 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 18:52:41 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd2(t_global *global)
{
	global->parse->cmd = malloc(sizeof(*global->parse->cmd)
			* (count_triple_tab(global->parse->bt) + 1));
	if (!global->parse->cmd)
		return (1);
	*global->parse->cmd = 0;
	return (0);
}

int	find_cmd(t_global *global)
{
	int	i;
	int	j;

	i = -1;
	if (find_cmd2(global) == 1)
		return (1);
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
				= findpath(ft_strdup(global->parse->bt[i][j]),
					global->envi, global);
		else
			global->parse->cmd[i] = NULL;
	}
	global->parse->cmd[i] = NULL;
	return (0);
}

int	is_last_here_doc(char **t)
{
	int	i;
	int	sign;

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

int	count_opt(char ***bt, t_opt *nrm)
{
	int	count;

	count = 0;
	while (bt[nrm->i][nrm->j + 1] && (!(check_limiter(bt[nrm->i][nrm->j + 1])
			|| ft_strcmp(bt[nrm->i][nrm->j + 1], "|") == 0)))
		count++;
	return (count);
}
