/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:19:39 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_tab_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	call_builtin(t_global *global, int i, int sign)
{
	if (sign == 1 && ft_strcmp(global->parse->cmd[i], "pwd") == 0)
		pwd(global);
	else if (ft_strcmp(global->parse->cmd[i], "cd") == 0)
	{
		if (double_tab_len(global->parse->bt[i]) <= 2)
			cd(global->parse->bt[i][1], global->envi, global, sign);
		else if (double_tab_len(global->parse->bt[i]) > 2 && sign == 1)
		{
			ft_putstr_fd("Too many arguments!\n", 2);
			free_in_child(global);
			exit(1);
		}
	}
	else if (sign == 1 && ft_strcmp(global->parse->cmd[i], "echo") == 0)
		echo_b(global->parse->bt[i], global);
	else if (ft_strcmp(global->parse->cmd[i], "unset") == 0)
		unset(global->parse->bt[i], global->envi, global, sign);
	else if (sign == 1 && ft_strcmp(global->parse->cmd[i], "env") == 0)
		env(global->envi, global);
	else if (ft_strcmp(global->parse->cmd[i], "export") == 0)
		export_b(global->envi, global->parse->bt[i], global, sign);
	else if (ft_strcmp(global->parse->cmd[i], "exit") == 0)
		exit_b(global, sign);
}
