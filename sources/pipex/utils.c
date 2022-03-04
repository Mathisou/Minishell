/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:17:16 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 18:13:33 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid	*pid_new_node(int content)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	if (!new)
		return (NULL);
	new->pid = content;
	new->next = NULL;
	return (new);
}

void	pid_add_node_back(t_pid **first, int content)
{
	t_pid	*tmp;

	if (!*first)
		*first = pid_new_node(content);
	else
	{	
		tmp = *first;
		while (tmp->next != NULL)
			tmp = (tmp)->next;
		tmp->next = pid_new_node(content);
	}
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sfd.is_sig = true;
		write(1, "\n", 1);
		if (g_sfd.is_here_doc == true || g_sfd.after == false)
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	reset_stdin_stdout(t_global *global)
{
	if (global->sfd)
	{
		if (global->sfd->is_output_redirected == true)
		{
			close(global->sfd->outfile);
			dup2(global->sfd->save_stdout, STDOUT_FILENO);
			close(global->sfd->save_stdout);
			global->sfd->is_output_redirected = false;
			global->sfd->is_here_doc = false;
		}
		if (global->sfd->is_input_redirected == true)
		{
			close(global->sfd->infile);
			dup2(global->sfd->save_stdin, STDIN_FILENO);
			close(global->sfd->save_stdin);
			global->sfd->is_input_redirected = false;
			global->sfd->is_here_doc = false;
		}
	}		
}

void	init_rl(t_global *global)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	global->sfd->is_sig = false;
	global->sfd->is_here_doc = false;
	global->sfd->is_input_redirected = false;
	global->sfd->is_output_redirected = false;
	global->sfd->is_stdout = false;
}
