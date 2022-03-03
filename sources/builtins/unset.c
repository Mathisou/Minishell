/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:49 by maroly            #+#    #+#             */
/*   Updated: 2022/03/03 19:13:43 by hkovac           ###   ########.fr       */
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

void	unset(char **to_unset, t_env **lst, t_global *global)
{
	int		i;
	t_env	*tmp;
	int		exitt;

	tmp = *lst;
	i = 0;
	exitt = 0;
	while (to_unset[++i])
	{
		if (is_var(tmp->var, to_unset[i], global) == 0)
		{
			exitt++;
			first (lst);
		}
		tmp = *lst;
		while (tmp->next && is_var(tmp->next->var, to_unset[i], global) == 1)
			tmp = tmp->next;
		if (tmp->next)
			after (tmp);
		else
		{
			if (exitt != 1)
			{
				free_in_child(global);
				exit(EXIT_FAILURE);
			}
		}
			
	}
	exit (EXIT_SUCCESS);
}
