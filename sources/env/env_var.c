/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:55:26 by maroly            #+#    #+#             */
/*   Updated: 2022/03/02 12:11:25 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var3(char *old_str, t_rep_var *nrm)
{
	if (!nrm->new)
		return (NULL);
	while ((old_str[++nrm->i] && old_str[nrm->i] != '$') || (old_str[nrm->i]
			&& old_str[nrm->i] == '$' && old_str[nrm->i + 1] == '$'))
	{
		nrm->new[nrm->j] = old_str[nrm->i];
		nrm->j++;
	}
	while (old_str[++nrm->i] && (ft_isalnum(old_str[nrm->i]) == 1
			|| (old_str[nrm->i] == '?' && old_str[nrm->i - 1] == '$')))
	{
		if (old_str[nrm->i] == '?' && old_str[nrm->i - 1] == '$')
		{
			nrm->i++;
			break ;
		}
	}
	return ((char *)1);
}

static char	*replace_var2(char *old_str, int sizeofvar, char *ref_var)
{
	t_rep_var	nrm;

	nrm.i = -1;
	nrm.j = 0;
	nrm.k = -1;
	nrm.new = malloc(sizeof(char) * (ft_strlen(old_str)
				+ ft_strlen(ref_var) - sizeofvar + 1));
	if (!replace_var3(old_str, &nrm))
		return (NULL);
	while (ref_var[++nrm.k])
	{
		nrm.new[nrm.j] = ref_var[nrm.k];
		nrm.j++;
	}
	while (old_str[nrm.i])
	{
		nrm.new[nrm.j] = old_str[nrm.i];
		nrm.j++;
		nrm.i++;
	}	
	nrm.new[nrm.j] = 0;
	return (nrm.new);
}

char	*replace_var4(char *old_str, t_env **lst
, t_global *global, t_rep_var2 *nrm)
{
	if (old_str[nrm->i + 1] == '?')
		nrm->ref_var = statu(global);
	else
		nrm->ref_var = find_ref_var(&old_str[nrm->i], lst);
	if (nrm->ref_var == NULL)
	{
		free(nrm->ref_var);
		nrm->ref_var = malloc(sizeof(char) * 1);
		nrm->ref_var[0] = 0;
	}
	while (old_str[++nrm->i] && (ft_isalnum(old_str[nrm->i]) == 1
			|| (old_str[nrm->i] == '?' && nrm->i > 0
				&& old_str[nrm->i - 1] == '$')))
		nrm->j++;
	free(nrm->new);
	nrm->new = replace_var2(old_str, nrm->j, nrm->ref_var);
	nrm->i = -1;
	free(old_str);
	old_str = ft_strdup(nrm->new);
	free(nrm->ref_var);
	return (old_str);
}

int	dollar_count(char *str)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == 39)
			while (str[++i] != 39)
				;
		if (str[i] == '$')
			count++;
	}
	return (count);
}

char	*replace_var(char *old_str, t_env **lst, t_global *global)
{
	t_rep_var2	nrm;
	int			i;
	int			nb_of_replace;

	nrm.i = -1;
	i = -1;
	nb_of_replace = dollar_count(old_str);
	nrm.ref_var = NULL;
	nrm.new = ft_strdup(old_str);
	while (old_str[++nrm.i])
	{
		nrm.j = 1;
		if ((old_str[nrm.i] == '$' && (ft_isalnum(old_str[nrm.i + 1]) == 1
					|| old_str[nrm.i + 1] == '?')
				&& should_replace_var(old_str, nrm.i) == 0)
			&& ++i < nb_of_replace)
			old_str = replace_var4(old_str, lst, global, &nrm);
	}
	free(old_str);
	return (nrm.new);
}
