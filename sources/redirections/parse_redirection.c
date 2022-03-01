/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:37:23 by maroly            #+#    #+#             */
/*   Updated: 2022/03/01 13:43:39 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last(char **t, int i)
{
	int j;

	j = -1;
	while (t[++j])
		if (ft_strcmp(t[j], "<<") == 0 && j > i)
			return (1);
	return (0);
}

int	parsing_redirection(char **t, t_fd *sfd)
{
	int i;

	i = -1;
	// sfd->save_stdout = dup(STDOUT_FILENO);
	// sfd->save_stdin = dup(STDIN_FILENO);
	// close(sfd->save_stdout);
	// close(sfd->save_stdin);
	while (t[++i])
	{
		if (ft_strcmp(t[i], ">") == 0 && t[i + 1])
		{
			sfd->is_output_redirected = true;
			dup2(sfd->save_stdout, 1);
			if (access(t[i + 1], F_OK) == 0)
				unlink(t[i + 1]);
			if (ft_strcmp(t[i + 1], "/dev/stdout") == 0)
				sfd->is_stdout = true;
			sfd->outfile = open(t[i + 1], O_WRONLY | O_CREAT, 0644);
			sfd->save_stdout = dup(STDOUT_FILENO);
			dup2(sfd->outfile, STDOUT_FILENO);
		}
		else if (ft_strcmp(t[i], ">>") == 0 && t[i + 1])
		{
			sfd->is_output_redirected = true;
			dup2(sfd->save_stdout, 1);
			if (ft_strcmp(t[i + 1], "/dev/stdout") == 0)
				sfd->is_stdout = true;
			sfd->outfile = open(t[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			sfd->save_stdout = dup(STDOUT_FILENO);
			dup2(sfd->outfile, STDOUT_FILENO);
		}
		if (ft_strcmp(t[i], "<") == 0 && t[i + 1])
		{
			sfd->is_input_redirected = true;
			dup2(sfd->save_stdin, 0);
			sfd->infile = open(t[i + 1], O_RDONLY);
			if (sfd->infile == -1)
			{
				perror(t[i + 1]);
				return (1);
			}
			sfd->save_stdin = dup(STDIN_FILENO);
			dup2(sfd->infile, STDIN_FILENO);
		}
		if (ft_strcmp(t[i], "<<") == 0 && t[i + 1]) // gerer ce genre de cas : < Makefile << tg cat //fais
		{
			sfd->is_input_redirected = true;
			dup2(sfd->save_stdin, 1);
			sfd->save_stdin = dup(STDIN_FILENO);
			here_doc(sfd, t[i + 1]);
			dup2(sfd->infile, STDIN_FILENO);
		}
	}
	return (0);
}