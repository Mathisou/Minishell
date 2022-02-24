/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:04:11 by maroly            #+#    #+#             */
/*   Updated: 2022/02/24 18:24:16 by maroly           ###   ########.fr       */
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
		while (bt[i][j] && check_limiter(bt[i][j]) == 0)
			j++;
		cmdopt[k] = malloc(sizeof(char *) * (j + 1));
		if (!cmdopt)
			return (NULL);
		m = -1;
		while (++m < j)
			cmdopt[k][m] = ft_strdup(bt[i][m]);
		cmdopt[k][m] = NULL;
		k++;
	}
	cmdopt[k] = NULL;
	return (cmdopt);
}

int	find_cmd(t_global *global)
{
	int i;

	i = -1;
	global->parse->cmd = malloc(sizeof(*global->parse->cmd) * (count_triple_tab(global->parse->bt) + 1));
	if (!global->parse->cmd)
		return (1);
	while (global->parse->bt[++i])
	{
		if (ft_strcmp(global->parse->bt[i][0], "<") != 0)
			global->parse->cmd[i]  = findpath(ft_strdup(global->parse->bt[i][0]), global->envi); //need: remplacer premier argument avc la bonne commande
		else
			global->parse->cmd[i]  = findpath(ft_strdup(global->parse->bt[i][2]), global->envi);
		if (global->parse->cmd[i] == NULL)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(global->parse->bt[i][0], 2); // ou 2
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	global->parse->cmd[i] = NULL;
	return (0);
}