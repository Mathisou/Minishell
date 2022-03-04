/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:39:59 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 15:50:40 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tab(char **t)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (t[++i] && ft_strcmp(t[i], "|") != 0)
		count++;
	return (count);
}

int	count_double_tab(char **t)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (t[++i])
		if (ft_strcmp(t[i], "|") == 0)
			count++;
	return (count);
}

int	count_triple_tab(char ***t)
{
	int	i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

void	pipe_split2(t_global *global)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = 0;
	while (global->parse->t[++i])
	{
		if (ft_strcmp(global->parse->t[i], "|") == 0)
		{
			global->parse->bt[k][++j] = NULL;
			k++;
			global->parse->bt[k] = malloc(sizeof(char *)
					* (count_tab(&global->parse->t[i + 1]) + 1));
			if (!global->parse->bt[k])
				return ;
			j = -1;
		}
		else
			global->parse->bt[k][++j] = ft_strdup(global->parse->t[i]);
	}
	global->parse->bt[k][++j] = NULL;
	global->parse->bt[++k] = NULL;
}

void	pipe_split(t_global *global)
{
	global->parse->bt = malloc(sizeof(*global->parse->bt)
			* (count_double_tab(global->parse->t) + 2));
	if (!global->parse->bt)
		free_n_exit(global);
	global->parse->bt[0] = malloc(sizeof(char *)
			* (count_tab(global->parse->t) + 1));
	if (!global->parse->bt[0])
		free_n_exit(global);
	pipe_split2(global);
}
