/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:37:23 by maroly            #+#    #+#             */
/*   Updated: 2022/02/17 13:10:10 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_redirection(char **t, t_fd *sfd)
{
	int i;

	i = -1;
	sfd->save_stdout = dup(STDOUT_FILENO);
	while (t[++i])
	{
		if (ft_strcmp(t[i], ">") == 0 && t[i + 1])
		{
			dup2(sfd->save_stdout, 1);
			if (access(t[i + 1], F_OK) == 0)
				unlink(t[i + 1]);
			sfd->outfile = open(t[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			sfd->save_stdout = dup(STDOUT_FILENO);
			dup2(sfd->outfile, STDOUT_FILENO);
		}
		else if (ft_strcmp(t[i], ">>") == 0 && t[i + 1]) // ne secrit pas a la suite
		{
			dup2(sfd->save_stdout, 1);
			sfd->outfile = open(t[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			sfd->save_stdout = dup(STDOUT_FILENO);
			dup2(sfd->outfile, STDOUT_FILENO);
		}
	}
}