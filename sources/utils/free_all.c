/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/23 20:28:19 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_end_line(t_global *global)
{
	free(global->parse->line);
	destroy_tab(global->parse->t);
	destroy_big_tab(global->parse->cmdopt);
	destroy_tab(global->parse->cmd); // possible double free
	destroy_big_tab(global->parse->bt);
}

void	free_parse(t_global *global)
{
	if	(global->parse)
	{
		if (global->parse->line)
			free(global->parse->line);
		if (global->parse->cmd)
			free(global->parse->cmd);
		if (global->parse->t)
			destroy_tab(global->parse->t);
		if (global->parse->cmdopt)
			free(global->parse);
		free(global->parse);
	}
}

void	free_env(t_global *global)
{
	del_list(global->envi);
}

void	free_all(int mode, t_global *global)
{
	if (mode == PARSE)
		return (free_parse(global));
	else if (mode == ENV)
		return (free_env(global));
	else if (mode == ALL)
	{
		free_parse(global);
		free_env(global);
	}
	
}

void	destroy_big_tab(char ***bt)
{
	int i;

	i = -1;
	while (bt[++i])
		destroy_tab(bt[i]);
	free(bt);
}