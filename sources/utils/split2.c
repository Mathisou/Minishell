/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:58:29 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 16:34:55 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	test62(int *i, int *size, char const *s)/* test les < > dpour split les char * */
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

static int	create_tab(char const *s, char c)/* compte cmb de char * dans char ** */
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

char	*count_mall(const char *s, char c)/* compte combien mall dans char * */
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;		
	if (s[i] == 62)
	{
		i++;
		if (s[i] == 62)
			i++;
	}
	else if (s[i] == 60)
	{
		i++;
		if (s[i] == 60)
			i++;
	}
	else if (s[i] == '|')
	{
		i++;
	}
	else 
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

void	put_str_in_tab2(char *str, int *i, const char *s)/*extension de en bas*/
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

static char	*put_str_in_tab(const char *s, char c)/*copy de sep a sep*/
{
	int	i;
	char	*str;

	str = count_mall(s, c);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (s[i] == 60)
	{
		str[i] = s[i];
		i++;
		if (s[i] == 60)
		{
			str[i] = s[i];
			i++;
		}
	}
	else if (s[i] == 62)
	{
		str[i] = s[i];
		i++;
		if (s[i] == 62)
		{
			str[i] = s[i];
			i++;
		}
	}
	else if (s[i] == '|')
	{
		str[i] = s[i];
		i++;
	}
	else
	{
		while (s[i] && s[i] != c && s[i] != 60 && s[i] != 62 && s[i] != '|')
			put_str_in_tab2(str, &i, s);
	}
	str[i] = '\0';
	return (str);
}

char **norm1(t_norm *norm, char **big_tab)/*parcours tout str * et dispatch*/
{
	if ((((norm->i == 0 || norm->s[norm->i - 1] == norm->c)/*sep before*/
	&& norm->s[norm->i] != norm->c) && norm->s[norm->i])/*current sep*/
	|| (norm->s[norm->i] == 60 && norm->s[norm->i - 1] && norm->s[norm->i - 1] != ' ' && norm->s[norm->i - 1] != 60)
	|| (norm->s[norm->i] == 62 && norm->s[norm->i - 1] && norm->s[norm->i - 1] != ' ' && norm->s[norm->i - 1] != 62)
	|| (norm->i > 0 && norm->s[norm->i - 1] == 60 && norm->s[norm->i] != 60 && norm->s[norm->i] != ' ')
	|| (norm->i > 0 && norm->s[norm->i - 1] == 62 && norm->s[norm->i] != 62 && norm->s[norm->i] != ' ')
	|| (norm->s[norm->i] == '|' && norm->s[norm->i - 1] && norm->s[norm->i - 1] != ' ')
	|| (norm->i > 0 && norm->s[norm->i - 1] == '|' && norm->s[norm->i] != ' '))
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
