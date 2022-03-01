/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/03/01 17:08:15 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_b(t_global *global)
{
	free(global->parse->line);
	destroy_tab(global->parse->t);
	destroy_tab(global->parse->cmd);
	destroy_big_tab(global->parse->cmdopt);
	destroy_big_tab(global->parse->bt);
	del_list(global->envi);
	pid_del_list(global->pid);
	free(global->parse);
	close(global->sfd->save_stdout);
	rl_clear_history();
	ft_putstr("exit\n");
	exit(0);
}
