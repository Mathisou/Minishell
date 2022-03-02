/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/03/02 13:48:42 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(t_global *global, int i)
{
	if (ft_strcmp(global->parse->cmd[i], "pwd") == 0)
		pwd();
	else if (ft_strcmp(global->parse->cmd[i], "cd") == 0)
		cd(global->parse->bt[i][1], global->envi, global);
	else if (ft_strcmp(global->parse->cmd[i], "echo") == 0)
		echo_b(global->parse->bt[i]);
	else if (ft_strcmp(global->parse->cmd[i], "exit") == 0
		&& count_triple_tab(global->parse->bt) == 1)
		exit_b(global);
	else if (ft_strcmp(global->parse->cmd[i], "unset") == 0)
		unset(global->parse->bt[i], global->envi);
	else if (ft_strcmp(global->parse->cmd[i], "env") == 0)
		env(global->envi);
	else if (ft_strcmp(global->parse->cmd[i], "export") == 0)
		export_b(global->envi, global->parse->bt[i], global);
}
