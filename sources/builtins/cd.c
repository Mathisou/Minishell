/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:37 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 17:58:29 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strcats(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc(sizeof(*new) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[++i])
	{
		new[j] = s1[i];
		j++;
	}
	i = -1;
	if (s2)
	{
		while (s2[++i])
		{
			new[j] = s2[i];
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}

static void	norm(t_norm3 *nrm, t_env **lst)
{
	while (nrm->tmp)
	{
		if (ft_strncmp(nrm->tmp->var, "PWD=", 4) == 0)
		{
			nrm->old_pwd = ft_strdup(nrm->tmp->var + 4);
			free(nrm->tmp->var);
			nrm->tmp->var = strcats("PWD=", getcwd(nrm->s, 4096 + 1));
			break ;
		}
		nrm->tmp = nrm->tmp->next;
	}
	nrm->tmp = *lst;
	while (nrm->tmp)
	{
		if (ft_strncmp(nrm->tmp->var, "OLDPWD=", 7) == 0)
		{
			free(nrm->tmp->var);
			nrm->tmp->var = strcats("OLDPWD=", nrm->old_pwd);
			nrm->exist++;
			break ;
		}
		nrm->tmp = nrm->tmp->next;
	}
}

void	change_env(t_env **lst)
{
	t_norm3	nrm;

	nrm.tmp = *lst;
	nrm.exist = 0;
	nrm.old_pwd = NULL;
	norm(&nrm, lst);
	if (!nrm.exist)
	{
		nrm.str = strcats("OLDPWD=", nrm.old_pwd);
		add_node_back(lst, nrm.str);
		free(nrm.str);
	}
	if (nrm.old_pwd)
		free(nrm.old_pwd);
}

void	cd(char *directory, t_env **lst)
{
	if (!directory)
		directory = getenv("HOME");
	if (chdir(directory) == -1)
		perror(directory);
	change_env(lst);
}
