/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:37 by maroly            #+#    #+#             */
/*   Updated: 2022/02/25 15:36:33 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strcats(char *s1, char *s2)
{
	char *new;
	int i;
	int j;

	i = -1;
	j = 0;
	new = malloc(sizeof(*new) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL); // a secur
	while (s1[++i])
	{
		new[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		new[j] = s2[i];
		j++;
	}
	new[j] = '\0'; 
	return (new);
}

void	change_env(t_env **lst)
{
	t_env	*tmp;
	char	*old_pwd;
	char	s[4096 + 1];
	int		exist;
	char	*str;

	tmp = *lst;
	exist = 0;
	(void)old_pwd;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
		{
			old_pwd = ft_strdup(tmp->var + 4);
			free(tmp->var);
			tmp->var = strcats("PWD=", getcwd(s, 4096 + 1));
			break;
		}
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "OLDPWD=", 7) == 0)
		{
			free(tmp->var);
			tmp->var = strcats("OLDPWD=", old_pwd);
			free(old_pwd);
			exist++;
			break;
		}
		tmp = tmp->next;
	}
	if (!exist)
	{
		str = strcats("OLDPWD=", old_pwd);	
		add_node_back(lst, str);
		free(str);
	}
	if (old_pwd)
		free(old_pwd);
}

void	cd(char *directory, t_env **lst)
{
	if (!directory)
		directory = getenv("HOME");
	if (chdir(directory) == -1)
		perror(directory);
	change_env(lst);
}