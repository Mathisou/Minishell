/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:10:11 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 19:49:23 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	startchildprocess2(t_global *global, int i)
{
	if (i % 2 == 0)
	{
		pipe(global->sfd->p1);
		opening_child(global, 1, i);
		close(global->sfd->p1[1]);
		if (i > 0)
			close(global->sfd->p2[0]);
	}
	else
	{
		pipe(global->sfd->p2);
		opening_child(global, 2, i);
		close(global->sfd->p1[0]);
		close(global->sfd->p2[1]);
	}
}

void	startchildprocess(t_global *global)
{
	int	i;

	i = -1;
	close_fd(global);
	while (global->parse->bt[++i])
	{
		if (parsing_redirection(global->parse->bt[i], global->sfd) == 0)
		{
			if (global->sfd->is_here_doc == true && global->sfd->is_sig == true)
				break ;
			startchildprocess2(global, i);
		}
		reset_stdin_stdout(global);
	}
	wait_func(global);
	close_fd(global);
}

void	pipex(t_global *global)
{
	int		p1[2];
	int		p2[2];

	global->parse->bt_size = count_triple_tab(global->parse->bt);
	pipe(p1);
	pipe(p2);
	global->sfd->p1 = p1;
	global->sfd->p2 = p2;
	startchildprocess(global);
}
