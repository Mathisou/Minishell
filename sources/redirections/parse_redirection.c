/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:37:23 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 18:07:37 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_stdout(t_fd *sfd)
{
	if (sfd->is_output_redirected == true)
	{
		close(sfd->outfile);
		dup2(sfd->save_stdout, STDOUT_FILENO);
		close(sfd->save_stdout);
		sfd->is_output_redirected = false;
		sfd->is_here_doc = false;
	}
}

static void	parsing_redirection_out(char **t, t_fd *sfd, int i)
{
	if (ft_strcmp(t[i], ">") == 0 && t[i + 1])
	{
		reset_stdout(sfd);
		sfd->save_stdout = dup(STDOUT_FILENO);
		sfd->is_output_redirected = true;
		if (access(t[i + 1], F_OK) == 0)
			unlink(t[i + 1]);
		if (ft_strcmp(t[i + 1], "/dev/stdout") == 0)
			sfd->is_stdout = true;
		sfd->outfile = open(t[i + 1], O_WRONLY | O_CREAT, 0644);
		dup2(sfd->outfile, STDOUT_FILENO);
	}
	else if (ft_strcmp(t[i], ">>") == 0 && t[i + 1])
	{
		reset_stdout(sfd);
		sfd->save_stdout = dup(STDOUT_FILENO);
		sfd->is_output_redirected = true;
		if (ft_strcmp(t[i + 1], "/dev/stdout") == 0)
			sfd->is_stdout = true;
		sfd->outfile = open(t[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(sfd->outfile, STDOUT_FILENO);
	}
}

static void	reset_stdin(t_fd *sfd)
{
	if (sfd->is_input_redirected == true)
	{
		close(sfd->infile);
		dup2(sfd->save_stdin, STDIN_FILENO);
		close(sfd->save_stdin);
		sfd->is_input_redirected = false;
		sfd->is_here_doc = false;
	}
}

static int	parsing_redirection_in(char **t, t_fd *sfd, int i)
{
	if (ft_strcmp(t[i], "<") == 0 && t[i + 1])
	{
		reset_stdin(sfd);
		sfd->save_stdin = dup(STDIN_FILENO);
		sfd->is_input_redirected = true;
		sfd->infile = open(t[i + 1], O_RDONLY);
		if (sfd->infile == -1)
		{
			perror(t[i + 1]);
			return (1);
		}
		dup2(sfd->infile, STDIN_FILENO);
	}
	if (ft_strcmp(t[i], "<<") == 0 && t[i + 1])
	{
		reset_stdin(sfd);
		sfd->is_here_doc = true;
		sfd->save_stdin = dup(STDIN_FILENO);
		here_doc(sfd, t[i + 1]);
		sfd->is_input_redirected = true;
	}
	return (0);
}

int	parsing_redirection(char **t, t_fd *sfd)
{
	int	i;

	i = -1;
	while (t[++i])
	{
		parsing_redirection_out(t, sfd, i);
		if (parsing_redirection_in(t, sfd, i))
			return (1);
	}
	return (0);
}
