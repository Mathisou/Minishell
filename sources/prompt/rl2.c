/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:44:18 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:21:59 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line_redirection(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0
				|| ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0
				|| ft_strcmp(t[i], "|") == 0) && t[i + 1] == NULL)
			return (1);
		else if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0
				|| ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0
				|| ft_strcmp(t[i], "|") == 0) && ft_strcmp(t[i + 1], "|") == 0)
			return (2);
		else if ((ft_strcmp(t[i], ">") == 0 || ft_strcmp(t[i], ">>") == 0
				|| ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], "<<") == 0
				|| ft_strcmp(t[i], "|") == 0) && (ft_strcmp(t[i + 1], ">") == 0
				|| ft_strcmp(t[i + 1], ">>") == 0
				|| ft_strcmp(t[i + 1], "<") == 0
				|| ft_strcmp(t[i + 1], "<<") == 0))
			return (3);
		i++;
	}
	return (0);
}

void	quit(t_global *global)
{
	write(1, "exit\n", 5);
	del_list(global->envi);
	pid_del_list(global->pid);
	free(global->parse);
	rl_clear_history();
	exit(0);
}
