/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:36:35 by maroly            #+#    #+#             */
/*   Updated: 2022/02/18 01:15:00 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char *cmd, char *dir)
{
	if (ft_strcmp(cmd, "/bin/pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd, "/usr/bin/cd") == 0)
		cd(dir);
	/*else if (ft_strcmp(cmd, "echo") == 0)
		echo();
	else if (ft_strcmp(cmd, "export") == 0)
		export();
	else if (ft_strcmp(cmd, "unset") == 0)
		unset();
	else if (ft_strcmp(cmd, "env") == 0)
		env();
	else if (ft_strcmp(cmd, "exit") == 0)
		exit();*/
}