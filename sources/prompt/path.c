/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:46:27 by maroly            #+#    #+#             */
/*   Updated: 2022/02/15 14:18:48 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**putsep(char **path)
{
	int	i;
	int	size;

	i = 0;
	while (path[i])
	{
		size = ft_strlen(path[i]);
		path[i][size++] = '/';
		path[i++][size] = '\0';
	}
	return (path);
}

char	*findpath(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**path;
	char	*new;

	i = 0;
	j = -1;
	new = NULL;
	while (ft_strstr(env[i], "PATH=") == NULL)
		i++;
	path = ft_split(ft_strstr(env[i], "PATH="), ':');
	putsep(path);
	while (path[++j] != NULL)
		path[j] = ft_strcat(path[j], cmd);
	j = 0;
	while (path[j] && access(path[j], X_OK) == -1)
		j++;
	if (path[j] != NULL)
		new = ft_strdup(path[j]);
	destroy_tab(path);
	return (new);
}