/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/26 20:19:06 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_end_line(t_global *global)
{
	free(global->parse->line);
	destroy_tab(global->parse->t);
	destroy_big_tab(global->parse->cmdopt);
	destroy_tab(global->parse->cmd);
	destroy_big_tab(global->parse->bt);
}

void	destroy_big_tab(char ***bt)
{
	int i;

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