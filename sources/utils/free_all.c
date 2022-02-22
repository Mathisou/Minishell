/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:41:34 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/22 14:49:13 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_parse(t_global *global)
{
	
}

static int	free_env(t_global *global)
{
	
}

static int	free_global(t_global *global)
{
	
}

int	free_all(int mode, t_global *global)
{
	if (mode == PARSE)
		return (free_parse(global));
	else if (mode == ENV)
		return (free_env(global));
	else if (mode == GLOBAL)
		return (free_globall(global));
	// else if (mode == ALL)
	
}