/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/02/24 14:17:08 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(t_global *global)
{
	if (ft_strcmp(global->parse->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(global->parse->cmd[0], "cd") == 0) // change $PWD et $OLDPWD dans env
		cd(global->parse->bt[0][1], global->envi); //
	else if (ft_strcmp(global->parse->cmd[0], "echo") == 0)
		echo_b(global->parse->t); //envoyer bt 
	else if (ft_strcmp(global->parse->cmd[0], "exit") == 0) // decremente $SHLVL dans env
		exit_b(global);
	else if (ft_strcmp(global->parse->cmd[0], "unset") == 0)
		unset(global->parse->bt[0], global->envi); //
	else if (ft_strcmp(global->parse->cmd[0], "env") == 0)
		env(global->envi);
	else if (ft_strcmp(global->parse->cmd[0], "export") == 0)
		export(global->envi, global->parse->bt[0]); //
}