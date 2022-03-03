/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:44:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/03 13:46:52 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_str_in_tab3(const char *s, int *i, char *str)
{
	if (s[*i] == 60)
	{
		str[*i] = s[*i];
		(*i)++;
		if (s[*i] == 60)
		{
			str[*i] = s[*i];
			(*i)++;
		}
	}
	else if (s[*i] == 62)
	{
		str[*i] = s[*i];
		(*i)++;
		if (s[*i] == 62)
		{
			str[*i] = s[*i];
			(*i)++;
		}
	}
	else
		return (1);
	return (0);
}

char	*put_str_in_tab(const char *s, char c)
{
	int		i;
	char	*str;

	str = count_mall(s, c);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (put_str_in_tab3(s, &i, str))
	{
		if (s[i] == '|')
		{
			str[i] = s[i];
			i++;
		}
		else
		{
			while (s[i] && s[i] != c && s[i] != 60 && s[i] != 62 && s[i] != '|')
				put_str_in_tab2(str, &i, s);
		}
	}
	str[i] = '\0';
	return (str);
}
