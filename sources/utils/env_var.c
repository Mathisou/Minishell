/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:55:26 by maroly            #+#    #+#             */
/*   Updated: 2022/02/17 17:58:45 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_there_dollar(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

char *replace_var2(char *old_str, int sizeofvar, char *ref_var)
{
	int i;
	int j;
	int k;
	char *new;

	i = -1;
	j = 0;
	k = -1;
	new = malloc(sizeof(char) * (ft_strlen(old_str) + ft_strlen(ref_var) - sizeofvar + 1));
	if (!new)
		return (NULL);
	new[0] = 0;
	while (old_str[++i] && old_str[i] != '$')
	{
		new[j] = old_str[i];
		j++;
	}
	new[j] = 0;
	while (old_str[++i] && ft_isalnum(old_str[i]) == 1)
		;
	while (ref_var[++k])
	{
		new[j] = ref_var[k];
		j++;
	}
	new[j] = 0;
	while (old_str[i])
	{
		new[j] = old_str[i];
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

char *find_ref_var(char *old_str)
{
	char *var;
	char *ref_var;
	int j;
	int i;

	i = 0;
	j = 0;
	ref_var = NULL;
	while (old_str[++i] && ft_isalnum(old_str[i]) == 1)
			j++;
	var = malloc(sizeof(char) * (j + 2));
	if (!var)
		return (NULL);
	i = 0;
	j = 0;
	while (old_str[++i] && ft_isalnum(old_str[i]) == 1)
	{
		var[j] = old_str[i];
		j++;
	}
	var[j] = '\0';
	ref_var = getenv(var); //gerer le cas unset donc a ne pas use
	free(var);
	return (ref_var);
}

char *replace_var(char *old_str)
{
	int i;
	int j;
	char *ref_var;
	char *new;

	i = -1;
	ref_var = NULL;
	while (old_str[++i])
	{
		j = 1;
		if (old_str[i] == '$')
		{
			ref_var = find_ref_var(&old_str[i]);
			if (ref_var == NULL)
			{
				free(ref_var);
				ref_var = malloc(sizeof(char) * 1);
				ref_var[0] = 0;
			}
			while (old_str[++i] && ft_isalnum(old_str[i]) == 1)
				j++;
			new = replace_var2(old_str, j, ref_var);
			i = -1;
			free(old_str);
			old_str = new;
			if (ref_var[0] == 0)
				free(ref_var);
		}
	}
	return (new);
}

char *replace_str(char *old_str)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(old_str) - 1));
	if (!new)
		return (NULL);
	while (old_str[++i] && old_str[i + 1])
	{
		new[j] = old_str[i];
		j++;
	}
	new[j] = '\0';
	free(old_str); //
	return (new);
}

void check_var_and_quotes(char **t)
{
	int i;

	i = -1;
	while (t[++i])
	{
		if (t[i][0] == 39 || t[i][0] == 34)
		{
			if (t[i][0] == 34 && is_there_dollar(t[i]) == 1)
				t[i] = replace_var(t[i]); // '$' tout seul a afficher, fonctionne aussi sans les doubles quotes
			t[i] = replace_str(t[i]);
		}
	}
}