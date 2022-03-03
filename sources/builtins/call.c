/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 18:54:31 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(t_global *global, int i)
{
	if (ft_strcmp(global->parse->cmd[i], "pwd") == 0)
		pwd(global);
	else if (ft_strcmp(global->parse->cmd[i], "cd") == 0)
		cd(global->parse->bt[i][1], global->envi, global);
	else if (ft_strcmp(global->parse->cmd[i], "echo") == 0)
		echo_b(global->parse->bt[i], global);
	else if (ft_strcmp(global->parse->cmd[i], "unset") == 0)
		unset(global->parse->bt[i], global->envi, global);
	else if (ft_strcmp(global->parse->cmd[i], "env") == 0)
		env(global->envi, global);
	else if (ft_strcmp(global->parse->cmd[i], "export") == 0)
		export_b(global->envi, global->parse->bt[i], global);
}
