/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:55:26 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 17:19:00 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var3(char *old_str, t_rep_var *nrm, int dollarindex)
{
	if (!nrm->new)
		return (NULL);
	while (++nrm->i < dollarindex)
	{
		nrm->new[nrm->j] = old_str[nrm->i];
		nrm->j++;
	}
	nrm->new[nrm->j] = 0;
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

static char	*replace_var2(char *old_str,
int sizeofvar, char *ref_var, int dollarindex)
{
	t_rep_var	nrm;

	nrm.i = -1;
	nrm.j = 0;
	nrm.k = -1;
	nrm.new = malloc(sizeof(char) * (ft_strlen(old_str)
				+ ft_strlen(ref_var) - sizeofvar + 1));
	if (!replace_var3(old_str, &nrm, dollarindex))
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
		nrm->ref_var = find_ref_var(&old_str[nrm->i], lst, global);
	if (nrm->ref_var == NULL)
	{
		free(nrm->ref_var);
		nrm->ref_var = malloc(sizeof(char) * 1);
		nrm->ref_var[0] = 0;
	}
	while (old_str[nrm->i + nrm->j]
		&& (ft_isalnum(old_str[nrm->i + nrm->j]) == 1
			|| (old_str[nrm->i + nrm->j] == '?' && nrm->i + nrm->j > 0
				&& old_str[nrm->i + nrm->j - 1] == '$')))
		nrm->j++;
	free(nrm->new);
	nrm->new = replace_var2(old_str, nrm->j, nrm->ref_var, nrm->i);
	nrm->i = -1;
	free(old_str);
	old_str = ft_strdup(nrm->new);
	free(nrm->ref_var);
	return (old_str);
}

static void	init_norm(t_rep_var2 *nrm, int *i, char *oldstr, int *nb)
{
	*i = -1;
	nrm->i = -1;
	nrm->ref_var = NULL;
	*nb = dollar_count(oldstr);
	nrm->new = ft_strdup(oldstr);
}

char	*replace_var(char *old_str, t_env **lst, t_global *global)
{
	t_rep_var2	nrm;
	int			i;
	int			nb_rep;

	init_norm(&nrm, &i, old_str, &nb_rep);
	if (!nrm.new)
		free_n_exit(global);
	while (old_str[++nrm.i])
	{
		nrm.j = 1;
		if ((old_str[nrm.i] == '$' && (ft_isalnum(old_str[nrm.i + 1]) == 1
					|| old_str[nrm.i + 1] == '?')
				&& should_replace_var(old_str, nrm.i) == 0) && ++i < nb_rep)
		{
			old_str = replace_var4(old_str, lst, global, &nrm);
			if (!old_str)
			{
				free(nrm.new);
				return (NULL);
			}
			nrm.i = -1;
		}
	}
	free(old_str);
	return (nrm.new);
}
