/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:54:48 by maroly            #+#    #+#             */
/*   Updated: 2022/02/26 16:19:12 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_global *global)
{
	close(global->sfd->p1[0]);
	close(global->sfd->p2[1]);
	close(global->sfd->p1[1]);
	close(global->sfd->p2[0]);
}

int	firstchild(t_global *global, int i)
{
	char **big;
	if (i > 0 && global->sfd->is_input_redirected == false)
		dup2(global->sfd->p2[0], 0);
	if (i < global->parse->bt_size - 1 && global->sfd->is_output_redirected == false)
		dup2(global->sfd->p1[1], 1);
	close_fd(global);
	big = convert_env(global->envi);
	if (global->parse->cmd[i] != NULL && tdm(global->parse->cmd[i]))
		call_builtin(global, i);
	else
		execve(global->parse->cmd[i], global->parse->cmdopt[i], big);
	free(global->parse->line);
	destroy_tab(global->parse->t);
	pid_del_list(global->pid);
	destroy_big_tab(global->parse->bt);
	del_list(global->envi);
	destroy_tab(big);
	return (1);
}

int	secondchild(t_global *global, int i)
{
	char **big;
	if (global->sfd->is_input_redirected == false)
		dup2(global->sfd->p1[0], 0);
	if (i < global->parse->bt_size - 1 && global->sfd->is_output_redirected == false)
		dup2(global->sfd->p2[1], 1);
	close_fd(global);
	big = convert_env(global->envi);
	if (global->parse->cmd[i] != NULL && tdm(global->parse->cmd[i]))
		call_builtin(global, i);
	else
		execve(global->parse->cmd[i], global->parse->cmdopt[i], big);
	free(global->parse->line);
	destroy_tab(global->parse->t);
	destroy_big_tab(global->parse->bt);
	del_list(global->envi);
	destroy_tab(big);
	pid_del_list(global->pid);
	return (1);
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

void	opening_child(t_global *global, int sign, int i)
{
	if (sign == 1)
	{
		global->parse->child = fork();
		if (global->parse->child < 0)
			perror("Fork failed");
		else if (global->parse->child == 0)
			exit(firstchild(global, i));
		close(global->sfd->p1[1]);
	}
	else
	{
		global->parse->child = fork();
		if (global->parse->child < 0)
			perror("Fork failed");
		else if (global->parse->child == 0)
			exit(secondchild(global, i));
		close(global->sfd->p2[1]);
	}
	pid_add_node_back(global->pid, global->parse->child);
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

void	startchildprocess(t_global *global)
{
	int i;

	i = -1;
	close_fd(global);
	while (global->parse->bt[++i])
	{
		parsing_redirection(global->parse->bt[i], global->sfd);
		if (i % 2 == 0)
		{
			pipe(global->sfd->p1);
			opening_child(global, 1, i);
		}
		else
		{
			pipe(global->sfd->p2);
			opening_child(global, 2, i);
		}
		if (global->sfd->is_output_redirected == true)
		{
			close(global->sfd->outfile);
			dup2(global->sfd->save_stdout, STDOUT_FILENO);
		}
		else if (global->sfd->is_input_redirected == true)
		{
			close(global->sfd->infile);
			dup2(global->sfd->save_stdin, STDIN_FILENO);
		}
	}
	wait_func(global);
	close_fd(global);
}

void pipex(t_global *global)
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
