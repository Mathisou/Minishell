/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:46:27 by maroly            #+#    #+#             */
/*   Updated: 2022/02/16 15:22:48 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd(char **path, char *cmd)
{
	int		i;
	int		j;
	int		k;
	int		size_add;
	char	*tmp;
	
	i = -1;
	size_add = ft_strlen(cmd) + 2;
	while (path[++i])
	{
		tmp = ft_strdup(path[i]);
		free(path[i]);
		path[i] = malloc(sizeof (char) * (ft_strlen(tmp) + size_add));
		if (!path[i])
		{
			destroy_tab(path);
			path = NULL;
			return ;
		}
		j = -1;
		k = 0;
		while (tmp[++j])
			path[i][k++] = tmp[j];
		path[i][k++] = '/';
		j = -1;
		while (cmd[++j])
			path[i][k++] = cmd[j];
		path[i][k++] = 0;
		free(tmp);
	}
	path[i] = NULL;
}

char	*findpath(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*new;

	i = 0;
	new = find_var(env, "PATH=");
	path = ft_split(new, ':');
	free(new);
	new = NULL;
	put_cmd(path, cmd);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && access(path[i], X_OK) != 0)
		i++;
	if (path[i] != NULL)
		new = ft_strdup(path[i]);
	destroy_tab(path);
	return (new);
}
