/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:58:29 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/07 14:15:26 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_mall2(const char *s, int *i)
{
	if (s[*i] == 62)
	{
		(*i)++;
		if (s[*i] == 62)
			(*i)++;
	}
	else if (s[*i] == 60)
	{
		(*i)++;
		if (s[*i] == 60)
			(*i)++;
	}
	else if (s[*i] == '|')
	{
		(*i)++;
	}
	else
		return (1);
	return (0);
}

char	*count_mall(const char *s, char c)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	if (count_mall2(s, &i))
	{	
		while (s[i] != c && s[i] && s[i] != 60 && s[i] != 62 && s[i] != '|')
		{
			if (s[i] == 39)
				while (s[++i] != 39)
					;
			else if (s[i] == 34)
				while (s[++i] != 34)
					;
			if (s[i])
				i++;
		}
	}
	str = (char *) malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	return (str);
}

int	norm2(t_norm *norm)
{
	if (norm->i == 0 && norm->s[norm->i] != norm->c)
		return (1);
	else if (norm->i > 0 && norm->s[norm->i - 1] == norm->c
		&& norm->s[norm->i] != norm->c)
		return (2);
	else if (norm->s[norm->i] == 60 && norm->s[norm->i - 1]
		&& norm->s[norm->i - 1] != ' ' && norm->s[norm->i - 1] != 60)
		return (3);
	else if (norm->s[norm->i] == 62 && norm->s[norm->i - 1]
		&& norm->s[norm->i - 1] != ' ' && norm->s[norm->i - 1] != 62)
		return (4);
	else if (norm->i > 0 && norm->s[norm->i - 1] == 60
		&& norm->s[norm->i] != 60 && norm->s[norm->i] != ' ')
		return (5);
	else if (norm->i > 0 && norm->s[norm->i - 1] == 62
		&& norm->s[norm->i] != 62 && norm->s[norm->i] != ' ')
		return (6);
	else if (norm->s[norm->i] == '|' && norm->s[norm->i - 1]
		&& norm->s[norm->i - 1] != ' ')
		return (7);
	else if (norm->i > 0 && norm->s[norm->i - 1] && norm->s[norm->i - 1] == '|'
		&& norm->s[norm->i] != ' ')
		return (8);
	return (0);
}

char	**norm1(t_norm *norm, char **big_tab)
{
	if (norm2(norm))
	{
		big_tab[norm->string] = put_str_in_tab(&norm->s[norm->i], norm->c);
		if (!big_tab[norm->string])
			return (destroy_tab(big_tab));
		norm->string++;
	}
	if (norm->s[norm->i] == 39)
		while (norm->s[++norm->i] && norm->s[norm->i] != 39)
			;
	else if (norm->s[norm->i] == 34)
		while (norm->s[++norm->i] && norm->s[norm->i] != 34)
			;
	norm->i++;
	return (NULL);
}

char	**split2(char const *s, char c)
{
	t_norm	norm;
	char	**big_tab;

	norm.i = 0;
	norm.string = 0;
	norm.c = c;
	norm.s = s;
	if (!s)
		return (NULL);
	big_tab = (char **) malloc(sizeof(*big_tab) * (create_tab(s, c) + 1));
	if (big_tab == NULL)
		return (NULL);
	while (s[norm.i])
		norm1(&norm, big_tab);
	big_tab[norm.string] = NULL;
	return (big_tab);
}
