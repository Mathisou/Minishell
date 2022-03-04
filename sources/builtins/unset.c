/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:49 by maroly            #+#    #+#             */
/*   Updated: 2022/03/04 16:02:08 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var(char *var, char *to_unset, t_global *global)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_strdup(var);
	(void)global;
	if (!str)
		free_n_exit(global);
	while (str[++i] && str[i] != '=')
		;
	str[i] = '\0';
	if (ft_strcmp(str, to_unset) == 0)
	{
		free(str);
		return (0);
	}
	else
	{
		free(str);
		return (1);
	}
}

static void	first(t_env **lst)
{
	t_env	*tmp;
	t_env	*save;

	tmp = *lst;
	if (tmp->next)
	{
		save = (*lst)->next;
		free((*lst)->var);
		free(*lst);
		*lst = save;
	}
	else
	{
		free(*lst);
		*lst = NULL;
	}
}

static void	after(t_env *tmp)
{
	t_env	*save;

	if (tmp->next->next)
	{
		save = tmp->next;
		tmp->next = tmp->next->next;
		free(save->var);
		free(save);
		save = NULL;
	}
	else
	{
		free(tmp->next->var);
		free(tmp->next);
		tmp->next = NULL;
	}
}

void	unset2(char **to_unset, t_env **lst, t_global *global, t_uns *nrm)
{
	if (is_var(nrm->tmp->var, to_unset[nrm->i], global) == 0)
	{
		nrm->exitt++;
		first (lst);
	}
	nrm->tmp = *lst;
	while (nrm->tmp->next && is_var(nrm->tmp->next->var,
			to_unset[nrm->i], global) == 1)
		nrm->tmp = nrm->tmp->next;
	if (nrm->tmp->next)
		after (nrm->tmp);
	else
	{
		if (nrm->exitt != 1 && nrm->sign == 1)
		{
			free_in_child(global);
			exit(EXIT_FAILURE);
		}
	}
}

void	unset(char **to_unset, t_env **lst, t_global *global, int sign)
{
	t_uns	nrm;

	nrm.tmp = *lst;
	nrm.i = 0;
	nrm.exitt = 0;
	nrm.sign = sign;
	while (to_unset[++nrm.i])
	{
		unset2(to_unset, lst, global, &nrm);
	}
	if (sign == 1)
	{
		free_in_child(global);
		exit (EXIT_SUCCESS);
	}
}
