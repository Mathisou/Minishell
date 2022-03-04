/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/04 17:53:40 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdopt_size(char **cmdopt)
{
	int	i;
	int	start;
	int	j;

	i = -1;
	j = 0;
	start = 0;
	while (ft_strcmp(cmdopt[++i], "<") == 0
		|| ft_strcmp(cmdopt[i], "<<") == 0
		|| ft_strcmp(cmdopt[i], ">") == 0
		|| ft_strcmp(cmdopt[i], ">>") == 0)
		j = j + 2;
	while (cmdopt[j + start] && (check_limiter(cmdopt[j + start]) == 0
			|| ft_strcmp(cmdopt[j + start], "|") != 0))
		start++;
	return (start + 1);
}

void	destroy_cmdopt(char ***cmdopt)
{
	int	i;

	i = -1;
	if (cmdopt)
	{
		while (cmdopt[++i])
			destroy_tab_size(cmdopt[i], cmdopt_size(cmdopt[i]));
		free(cmdopt);
	}
}

void	destroy_big_tab_size(char ***bt, int size)
{
	int	i;

	i = -1;
	if (bt)
	{
		while (bt[++i])
			destroy_tab_size(bt[i], size);
		free(bt);
	}
}

void	free_end_line(t_global *global)
{
	destroy_tab(global->parse->t);
	destroy_cmdopt(global->parse->cmdopt);
	destroy_tab_size(global->parse->cmd, count_triple_tab(global->parse->bt));
	destroy_big_tab(global->parse->bt);
	global->parse->t = NULL;
	global->parse->bt = NULL;
	global->parse->cmd = NULL;
	global->parse->cmdopt = NULL;
}

void	free_in_child(t_global *global)
{
	if (global->parse)
	{
		if (global->parse->line)
			free(global->parse->line);
		destroy_tab(global->parse->t);
		destroy_tab(global->parse->big);
		del_list(global->envi);
		destroy_tab_size(global->parse->cmd,
			count_triple_tab(global->parse->bt));
		destroy_cmdopt(global->parse->cmdopt);
		destroy_big_tab(global->parse->bt);
		free(global->parse);
	}
	pid_del_list(global->pid);
	reset_stdin_stdout(global);
}
