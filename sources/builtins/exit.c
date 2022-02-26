/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:44 by maroly            #+#    #+#             */
/*   Updated: 2022/02/26 14:32:11 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exit_b(t_global *global)
{
    free(global->parse->line);
	destroy_tab(global->parse->t);
    destroy_tab(global->parse->cmd);
    destroy_big_tab(global->parse->cmdopt);
    destroy_big_tab(global->parse->bt);
    del_list(global->envi);
    free(global->parse->path_minishell);
	free(global->parse);
    ft_putstr("exit\n");
    exit(0);
}