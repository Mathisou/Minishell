/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 15:43:57 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_b(t_global *global)
{
	free(global->parse->line);
	destroy_tab(global->parse->t);
	destroy_tab_size(global->parse->cmd, count_triple_tab(global->parse->bt));
	destroy_big_tab(global->parse->cmdopt);
	destroy_big_tab(global->parse->bt);
	del_list(global->envi);
	pid_del_list(global->pid);
	free(global->parse);
	rl_clear_history();
	reset_stdin_stdout(global);
	ft_putstr("exit\n");
	exit(0);
}
