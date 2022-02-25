/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:55:26 by maroly            #+#    #+#             */
/*   Updated: 2022/02/25 18:37:51 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while ((old_str[++i] && old_str[i] != '$') || (old_str[i] && old_str[i] == '$' && old_str[i + 1] == '$'))
	{
		new[j] = old_str[i];
		j++;
	}
	while (old_str[++i] && (ft_isalnum(old_str[i]) == 1 || (old_str[i] == '?' && old_str[i - 1] == '$')))
		if (old_str[i] == '?' && old_str[i - 1] == '$')
		{
			i++;
			break;
		}
	while (ref_var[++k])
	{
		new[j] = ref_var[k];
		j++;
	}
	while (old_str[i])
	{
		new[j] = old_str[i];
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

char *find_ref_var(char *old_str, t_env **lst)
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
	ref_var = find_var(lst, var);
	free(var);
	return (ref_var);
}

char *statu(t_global *global)
{
	t_pid *tmp;

	tmp = *global->pid;
	if (!tmp)
		return (ft_itoa(WEXITSTATUS(0)));
	while (tmp->next)
		tmp = tmp->next;
	return (ft_itoa(WEXITSTATUS(tmp->statu)));
}

char *replace_var(char *old_str, t_env **lst, t_global *global)
{
	int i;
	int j;
	char *ref_var;
	char *new;

	i = -1;
	ref_var = NULL;
	new = ft_strdup(old_str);
	while (old_str[++i])
	{
		j = 1;
		if (old_str[i] == '$' && (ft_isalnum(old_str[i + 1]) == 1 || old_str[i + 1] == '?') && should_replace_var(old_str, i) == 0)
		{
			if (old_str[i + 1] == '?')
				ref_var = statu(global);
			else
				ref_var = find_ref_var(&old_str[i], lst);
			if (ref_var == NULL)
			{
				free(ref_var);
				ref_var = malloc(sizeof(char) * 1);
				ref_var[0] = 0;
			}
			while (old_str[++i] && (ft_isalnum(old_str[i]) == 1 || (old_str[i] == '?' && i > 0 && old_str[i - 1] == '$')))
				j++;
			new = replace_var2(old_str, j, ref_var);
			i = -1;
			free(old_str);
			old_str = ft_strdup(new); // free new ?
			free(ref_var);
		}
	}
	free(old_str);
	return (new);
}

void remove_quotes2(char *old_str, char *new, int *i, int *j)
{
	while (old_str[++(*i)])
	{
		if (old_str[*i] == 34)
		{
			while (old_str[++(*i)] && old_str[*i] != 34)
			{
				new[*j] = old_str[*i];
				(*j)++;
			}
		}
		else if (old_str[*i] == 39)
		{
			while (old_str[++(*i)] && old_str[*i] != 39)
			{
				new[*j] = old_str[*i];
				(*j)++;
			}
		}
		else
		{
			new[*j] = old_str[*i];
			(*j)++;
		}
	}
}

char *remove_quotes(char *old_str)
{
	int nb_to_delete;
	char *new;
	int i;
	int j;

	i = -1;
	j = 0;
	nb_to_delete = count_delete(old_str);
	new = malloc(sizeof(char) * (ft_strlen(old_str) - nb_to_delete + 1));
	if (!new)
		return (NULL); //
	remove_quotes2(old_str, new, &i, &j);
	new[j] = 0;
	return (new);
}

void check_var_and_quotes(char **t, t_env **lst, t_global *global)
{
	int i;

	i = -1;
	while (t[++i])
	{
		if (is_there_dollar(t[i]) == 1)
			t[i] = replace_var(t[i], lst, global);
		if (is_there_quotes(t[i]) == 1)
			t[i] = remove_quotes(t[i]);
	}
}