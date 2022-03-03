/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:10:40 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/03 17:33:56 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**destroy_tab_size(char **t, int size)
{
	int	i;

	i = -1;
	if (t)
	{
		while (++i < size)
			if (t[i])
				free(t[i]);
		free(t);
	}
	t = NULL;
	return (NULL);
}

char	**destroy_tab(char **t)
{
	int	i;

	i = -1;
	if (t)
	{
		while (t[++i])
			if (t[i])
				free(t[i]);
		free(t);
	}
	t = NULL;
	return (NULL);
}

void	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	free_n_exit(t_global *global)
{
	ft_putstr_fd("Malloc issue!\n", 2);
	free_in_child(global);
	exit (1);
}
