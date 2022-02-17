/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:04:11 by maroly            #+#    #+#             */
/*   Updated: 2022/02/17 14:04:29 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

char	**find_opt(char **t)
{
	int i;
	int j;
	char **cmdopt;

	i = 0;
	j = -1;
	while (t[i] && check_limiter(t[i]) == 0)
		i++;
	cmdopt = malloc(sizeof(char *) * (i + 1));
	if (!cmdopt)
		return (NULL);
	while (++j < i)
		cmdopt[j] = t[j];
	cmdopt[j] = NULL;
	return (cmdopt);
}