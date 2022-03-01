/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:17:16 by maroly            #+#    #+#             */
/*   Updated: 2022/03/01 14:16:27 by maroly           ###   ########.fr       */
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

void	wait_func(t_global *global)
{
	t_pid *tmp;

	tmp = *global->pid;
	while (tmp)
	{
		waitpid(tmp->pid, &tmp->statu, 0);
		tmp = tmp->next;
	}
}

void	reset_stdin_stdout(t_global *global)
{
	if (global->sfd->is_output_redirected == true)
	{
		close(global->sfd->outfile);
		dup2(global->sfd->save_stdout, STDOUT_FILENO);
		global->sfd->is_output_redirected = false;
		close(global->sfd->save_stdout);
		// close save_stdout?
	}
	if (global->sfd->is_input_redirected == true)
	{
		close(global->sfd->infile);
		dup2(global->sfd->save_stdin, STDIN_FILENO);
		global->sfd->is_input_redirected = false;
		close(global->sfd->save_stdin);
		// close save_stdin?
	}
}