/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:32:59 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 18:36:18 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test62(int *i, int *size, char const *s)
{
	if (s[*i] == 62 || (s[*i] == 62 && s[(*i) + 1] == 62))
	{
		if ((*i) != 0 && s[(*i) - 1] != ' ')
			(*size)++;
		if (s[(*i) + 1] == 62)
			(*i)++;
		if (s[(*i) + 1] && s[(*i) + 1] != ' ')
			(*size)++;
	}
}

void	test60(int *i, int *size, char const *s)
{
	if (s[*i] == 60 || (s[*i] == 60 && s[(*i) + 1] == 60))
	{
		if ((*i) != 0 && s[(*i) - 1] != ' ')
			(*size)++;
		if (s[(*i) + 1] == 60)
			(*i)++;
		if (s[(*i) + 1] && s[(*i) + 1] != ' ')
			(*size)++;
	}
}

void	test_p(int *i, int *size, char const *s)
{
	if (s[*i] == '|')
	{
		if ((*i) != 0 && s[(*i) - 1] != ' ')
			(*size)++;
		if (s[(*i) + 1] && s[(*i) + 1] != ' ')
			(*size)++;
	}
}

int	create_tab(char const *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (((i == 0 || s[i - 1] == c) && s[i] != c) && s[i])
		{
			if (s[i] == 39)
				while (s[++i] != 39)
					;
			else if (s[i] == 34)
				while (s[++i] != 34)
					;
			size++;
		}
		test62(&i, &size, s);
		test60(&i, &size, s);
		test_p(&i, &size, s);
		if (s[i])
			i++;
	}
	return (size);
}

void	put_str_in_tab2(char *str, int *i, const char *s)
{
	str[*i] = s[*i];
	if (s[*i] == 39)
	{
		while (s[++(*i)] != 39)
			str[*i] = s[*i];
		str[*i] = s[*i];
	}
	else if (s[*i] == 34)
	{
		while (s[++(*i)] != 34)
			str[*i] = s[*i];
		str[*i] = s[*i];
	}
	if (s[*i])
		(*i)++;
}
