/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:58:29 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/17 16:31:19 by maroly           ###   ########.fr       */
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
	return (str);
}

static char	*put_str_in_tab(const char *s, char c)
{
	size_t	i;
	char	*str;

	str = count_mall(s, c);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		if (s[i] == 39)
		{
			while (s[++i] != 39)
				str[i] = s[i];
			str[i] = s[i];
		}
		else if (s[i] == 34)
		{
			while (s[++i] != 34)
				str[i] = s[i];
			str[i] = s[i];
		}
		if (s[i])
			i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**destroytab(char **big_tab)
{
	int	i;

	i = 0;
	while (big_tab[i])
		free(big_tab[i++]);
	free(big_tab);
	return (NULL);
}

char	**split2(char const *s, char c)
{
	size_t	i;
	size_t	string;
	char	**big_tab;

	i = 0;
	string = 0;
	if (!s)
		return (NULL);
	big_tab = (char **) malloc(sizeof(*big_tab) * (create_tab(s, c) + 1));
	if (big_tab == NULL)
		return (NULL);
	while (s[i])
	{
		if (((i == 0 || s[i - 1] == c) && s[i] != c) && s[i])
		{
			big_tab[string] = put_str_in_tab(&s[i], c);
			if (!big_tab[string])
				return (destroytab(big_tab));
			string++;
		}
		if (s[i] == 39)
			while (s[++i] != 39)
				;
		else if (s[i] == 34)
			while (s[++i] != 34)
				;
		if (s[i] && s[i] != c)
			i++;
		i++;
	}
	big_tab[string] = NULL;
	return (big_tab);
}