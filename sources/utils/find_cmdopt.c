/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:04:11 by maroly            #+#    #+#             */
/*   Updated: 2022/02/26 16:50:44 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

char	***find_opt(char ***bt)
{
	int i;
	int j;
	int k;
	int m;
	char ***cmdopt;

	i = -1;
	k = 0;
	cmdopt = malloc(sizeof(*cmdopt) * (count_triple_tab(bt) + 1));
	if (!cmdopt)
		return (NULL);
	while (bt[++i])
	{
		j = 0;
		if (!(ft_strcmp(bt[i][0], "<") == 0 || ft_strcmp(bt[i][0], "<<") == 0 || ft_strcmp(bt[i][0], ">") == 0 || ft_strcmp(bt[i][0], ">>") == 0))
		{
			while (bt[i][j] && check_limiter(bt[i][j]) == 0)
				j++;
			cmdopt[k] = malloc(sizeof(char *) * (j + 1));
			if (!cmdopt[k])
				return (NULL); //
			m = -1;
			while (++m < j)
				cmdopt[k][m] = ft_strdup(bt[i][m]);
			cmdopt[k][m] = NULL;
		}	
		else
		{
			while (ft_strcmp(bt[i][j], "<") == 0 || ft_strcmp(bt[i][j], "<<") == 0 || ft_strcmp(bt[i][j], ">") == 0 || ft_strcmp(bt[i][j], ">>") == 0)
				j = j + 2;
			cmdopt[k] = malloc(sizeof(char *) * 3);
			if (!cmdopt[k])
				return (NULL); //
			cmdopt[k][0] = ft_strdup(bt[i][j]);
			cmdopt[k][1] = ft_strdup(bt[i][j - 1]);
			cmdopt[k][2] = NULL;
		}
		k++;
	}
	cmdopt[k] = NULL;
	return (cmdopt);
}

int	find_cmd(t_global *global)
{
	int i;
	int j;

	i = -1;
	global->parse->cmd = malloc(sizeof(*global->parse->cmd) * (count_triple_tab(global->parse->bt) + 1));
	if (!global->parse->cmd)
		return (1);
	while (global->parse->bt[++i])
	{
		j = 0;
		while (ft_strcmp(global->parse->bt[i][j], "<") == 0 || ft_strcmp(global->parse->bt[i][j], "<<") == 0 || ft_strcmp(global->parse->bt[i][j], ">") == 0 || ft_strcmp(global->parse->bt[i][j], ">>") == 0)
			j = j + 2;
		global->parse->cmd[i]  = findpath(global, ft_strdup(global->parse->bt[i][j]), global->envi);
		if (global->parse->cmd[i] == NULL)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(global->parse->bt[i][j], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	global->parse->cmd[i] = NULL;
	return (0);
}