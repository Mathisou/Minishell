/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/22 15:14:44 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_parse(t_global *global)
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

static int	free_env(t_global *global)
{
	del_list(global->envi);
}

int	free_all(int mode, t_global *global)
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