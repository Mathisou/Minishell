/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/02 16:53:27 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_end_line(t_global *global)
{
	destroy_tab(global->parse->t);
	destroy_big_tab(global->parse->cmdopt);
	destroy_tab(global->parse->cmd);
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
		destroy_big_tab(global->parse->bt);
		del_list(global->envi);
		destroy_tab(global->parse->big);
		destroy_tab(global->parse->cmd);
		destroy_big_tab(global->parse->cmdopt);
		free(global->parse);
	}
	pid_del_list(global->pid);
	reset_stdin_stdout(global);
}

void	destroy_big_tab(char ***bt)
{
	int	i;

	i = -1;
	if (bt)
	{
		while (bt[++i])
			destroy_tab(bt[i]);
		free(bt);
	}
}

int	pid_del_list(t_pid **lst)
{
	t_pid	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
	return (0);
}
