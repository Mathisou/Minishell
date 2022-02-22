/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 11:10:53 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(t_global *global)
{
	if (ft_strcmp(global->parse->cmd, "pwd") == 0)
		pwd();
	else if (ft_strcmp(global->parse->cmd, "cd") == 0)
		cd(global->parse->t[1]); //
	else if (ft_strcmp(global->parse->cmd, "echo") == 0)
		echo_b(global->parse->t);
	else if (ft_strcmp(global->parse->cmd, "exit") == 0)
		exit_b(global);
	else if (ft_strcmp(global->parse->cmd, "unset") == 0)
		unset(global->parse->t[1], global->envi); //
	else if (ft_strcmp(global->parse->cmd, "env") == 0)
		env(global->envi);
	else if (ft_strcmp(global->parse->cmd, "export") == 0)
		export(global->envi, global->parse->t[1]); //
}