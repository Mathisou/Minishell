/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:40 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 14:21:30 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp_opt(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		if (s[i] == '-')
		{
			while (s[++i] == 'n')
				;
			if (s[i] == '\0')
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

int	double_tab_len_without_redir(char **t)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (t[++i])
	{
		if (check_limiter(t[i]) == 0 && strcmp_opt(t[i]) == 1)
			count++;
		else if (check_limiter(t[i]) == 1 && strcmp_opt(t[i]) == 1)
			i++;
	}
	return (count);
}

static void	print(char **t, int *i, int size)
{
	int	count;

	count = 0;
	while (t[*i])
	{
		if (check_limiter(t[*i]) == 0)
		{
			ft_putstr(t[*i]);
			count++;
			if (count < size - 1)
				write(1, " ", 1);
		}
		else
			(*i)++;
		(*i)++;
	}
}

void	echo_b(char **t, t_global *global)
{
	int	i;
	int	size;

	size = double_tab_len_without_redir(t);
	i = 0;
	while (t[i] && (ft_strcmp(t[i], "echo") != 0
			|| (ft_strcmp(t[i], "echo") == 0
				&& i > 0 && check_limiter(t[i - 1]) == 1)))
		i++;
	if (t[++i] && strcmp_opt(t[i]) == 0)
	{
		while (strcmp_opt(t[++i]) == 0)
			;
		print(t, &i, size);
	}
	else
	{
		print(t, &i, size);
		write(1, "\n", 1);
	}
	free_in_child(global);
	exit (EXIT_SUCCESS);
}
