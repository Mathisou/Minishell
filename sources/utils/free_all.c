/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/03 16:08:14 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//bt = NULL;
}

void	free_end_line(t_global *global)
{
	destroy_tab(global->parse->t);
	destroy_big_tab_size(global->parse->cmdopt, count_triple_tab(global->parse->bt));
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
		destroy_tab_size(global->parse->cmd, count_triple_tab(global->parse->bt));
		destroy_big_tab_size(global->parse->cmdopt, count_triple_tab(global->parse->bt));
		destroy_big_tab(global->parse->bt);
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
	//bt = NULL;
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
