/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:02:12 by hkovac           ###   ########.fr       */
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

static void	norm2(t_norm3 *nrm, t_env **lst, t_global *global)
{
	nrm->tmp = *lst;
	while (nrm->tmp)
	{
		if (ft_strncmp(nrm->tmp->var, "OLDPWD=", 7) == 0)
		{
			free(nrm->tmp->var);
			nrm->tmp->var = strcats("OLDPWD=", nrm->old_pwd);
			if (!nrm->tmp->var)
			{
				free(nrm->old_pwd);
				free_n_exit(global);
			}
			nrm->exist++;
			break ;
		}
		nrm->tmp = nrm->tmp->next;
	}
}

static void	norm(t_norm3 *nrm, t_env **lst, t_global *global)
{
	char	*str;

	while (nrm->tmp)
	{
		if (ft_strncmp(nrm->tmp->var, "PWD=", 4) == 0)
		{
			nrm->old_pwd = ft_strdup(nrm->tmp->var + 4);
			if (!nrm->old_pwd)
				free_n_exit(global);
			free(nrm->tmp->var);
			str = getcwd(NULL, 4096 + 1);
			nrm->tmp->var = strcats("PWD=", str);
			free(str);
			if (!nrm->tmp->var)
				free_n_exit(global);
			break ;
		}
		nrm->tmp = nrm->tmp->next;
	}
	norm2(nrm, lst, global);
}

void	change_env(t_env **lst, t_global *global)
{
	t_norm3	nrm;

	nrm.tmp = *lst;
	nrm.exist = 0;
	nrm.old_pwd = NULL;
	norm(&nrm, lst, global);
	if (!nrm.exist)
	{
		nrm.str = strcats("OLDPWD=", nrm.old_pwd);
		if (!nrm.str)
		{
			free(nrm.old_pwd);
			free_n_exit(global);
		}
		add_node_back(lst, nrm.str, global);
		free(nrm.str);
	}
	if (nrm.old_pwd)
		free(nrm.old_pwd);
}

void	cd(char *directory, t_env **lst, t_global *global, int sign)
{
	if (!directory)
	{
		directory = find_var(lst, "HOME");
		if (!directory && sign == 0)
			return ;
		if (chdir(directory) == -1 && sign == 1)
			perror(directory);
		if (directory)
			free(directory);
	}
	else
	{
		if (chdir(directory) == -1 && sign == 1)
		{
			perror(directory);
			free_in_child(global);
			exit (EXIT_FAILURE);
		}			
	}
	change_env(lst, global);
	if (sign == 1)
	{
		free_in_child(global);
		exit (EXIT_SUCCESS);
	}
}
