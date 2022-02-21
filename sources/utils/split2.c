/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:58:29 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/21 17:16:25 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_tab(char const *s, char c)
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
		if (s[i])
			i++;
	}
	return (size);
}

char	*count_mall(const char *s, char c)
{
	size_t	i;
	char	*str;

	str = NULL;
	i = 0;
	while (s[i] != c && s[i])
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
	str = (char *) malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	return (str);
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

static char	*put_str_in_tab(const char *s, char c)
{
	int	i;
	char	*str;

	str = count_mall(s, c);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		put_str_in_tab2(str, &i, s);
	str[i] = '\0';
	return (str);
}

char **norm1(t_norm *norm, char **big_tab)
{
	if (((norm->i == 0 || norm->s[norm->i - 1] == norm->c) && norm->s[norm->i] != norm->c) && norm->s[norm->i])
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
	char 	**rtn;

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
	{
		rtn = norm1(&norm, big_tab);
		if (rtn)
			return (rtn);
	}
	big_tab[norm.string] = NULL;
	return (big_tab);
}