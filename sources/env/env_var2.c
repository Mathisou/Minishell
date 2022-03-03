/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:12:16 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/03 17:31:08 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *old_str)
{
	int		nb_to_delete;
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	nb_to_delete = count_delete(old_str);
	new = malloc(sizeof(char) * (ft_strlen(old_str) - nb_to_delete + 1));
	if (!new)
		return (NULL);
	remove_quotes2(old_str, new, &i, &j);
	new[j] = 0;
	free(old_str);
	return (new);
}

void	check_var_and_quotes(char **t, t_env **lst, t_global *global)
{
	int	i;

	i = -1;
	while (t[++i])
	{
		if (is_there_dollar(t[i]) == 1)
		{
			t[i] = replace_var(t[i], lst, global);
			if (!t[i])
				free_n_exit(global);
		}
		if (is_there_quotes(t[i]) == 1)
		{
			t[i] = remove_quotes(t[i]);
			if (!t[i])
				free_n_exit(global);
		}
	}
}

char	*statu(t_global *global)
{
	t_pid	*tmp;

	tmp = *global->pid;
	if (!tmp)
		return (ft_itoa(WEXITSTATUS(0)));
	while (tmp->next)
		tmp = tmp->next;
	return (ft_itoa(WEXITSTATUS(tmp->statu)));
}

char	*find_ref_var(char *old_str, t_env **lst, t_global *global)
{
	char	*var;
	char	*ref_var;
	int		j;
	int		i;

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
	(void) global;
	ref_var = find_var(lst, var);
	free(var);
	return (ref_var);
}

void	remove_quotes2(char *old_str, char *n, int *i, int *j)
{
	while (old_str[++(*i)])
	{
		if (old_str[*i] == 34)
		{
			while (old_str[++(*i)] && old_str[*i] != 34)
			{
				n[*j] = old_str[*i];
				(*j)++;
			}
		}
		else if (old_str[*i] == 39)
		{
			while (old_str[++(*i)] && old_str[*i] != 39)
			{
				n[*j] = old_str[*i];
				(*j)++;
			}
		}
		else
		{
			n[*j] = old_str[*i];
			(*j)++;
		}
	}
}
