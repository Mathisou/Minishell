/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:54:48 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 14:53:56 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_global *global)
{
	close(global->sfd->p1[0]);
	close(global->sfd->p2[1]);
	close(global->sfd->p1[1]);
	close(global->sfd->p2[0]);
	if (global->sfd->is_input_redirected == true)
		close(global->sfd->infile);
	if (global->sfd->is_output_redirected == true)
		close(global->sfd->outfile);
}

void	execute(t_global *global, int i)
{
	global->parse->big = convert_env(global->envi);
	if (!global->parse->big)
		exit(1);
	if (global->parse->cmd[i]
		!= NULL && tdm(global->parse->cmd[i]))
		call_builtin(global, i, 1);
	else
	{
		if (global->parse->cmd[i] != NULL)
		{
			execve(global->parse->cmd[i], global->parse->cmdopt[i],
				global->parse->big);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(global->parse->cmdopt[i][0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

int	firstchild(t_global *global, int i)
{
	if (i > 0 && global->sfd->is_input_redirected == false)
		dup2(global->sfd->p2[0], 0);
	if (global->sfd->is_stdout == true)
		reset_stdin_stdout(global);
	if (i < global->parse->bt_size - 1
		&& global->sfd->is_output_redirected == false)
		dup2(global->sfd->p1[1], 1);
	close_fd(global);
	execute(global, i);
	free_in_child(global);
	exit(1);
}

int	secondchild(t_global *global, int i)
{
	if (global->sfd->is_input_redirected == false)
		dup2(global->sfd->p1[0], 0);
	if (i < global->parse->bt_size - 1
		&& global->sfd->is_output_redirected == false)
		dup2(global->sfd->p2[1], 1);
	close_fd(global);
	execute(global, i);
	free_in_child(global);
	exit(1);
}

void	opening_child(t_global *global, int sign, int i)
{
	if (sign == 1)
	{
		global->parse->child = fork();
		if (global->parse->child < 0)
			perror("Fork failed");
		else if (global->parse->child == 0)
			firstchild(global, i);
		close(global->sfd->p1[1]);
	}
	else
	{
		global->parse->child = fork();
		if (global->parse->child < 0)
			perror("Fork failed");
		else if (global->parse->child == 0)
			secondchild(global, i);
		close(global->sfd->p2[1]);
	}
	pid_add_node_back(global->pid, global->parse->child);
}
