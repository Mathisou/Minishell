/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:10:11 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/07 15:20:11 by hkovac           ###   ########.fr       */
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

int	is_a_directory(char *str)
{
	int	i;

	i = 0;
	if (str[i])
		while (str[i + 1])
			i++;
	if (str[i] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	startchildprocess(t_global *global)
{
	int	i;

	i = -1;
	close_fd(global);
	while (global->parse->bt[++i])
	{
		if (ft_strlen(global->parse->cmdopt[i][0]) > 0
			&& parsing_redirection(global->parse->bt[i], global->sfd) == 0
			&& is_a_directory(global->parse->cmdopt[i][0]) == 0)
		{
			if ((global->sfd->is_here_doc == true
					&& global->sfd->is_sig == true))
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
