/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:46:27 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 16:26:02 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd2(char **path, char *cmd, t_path *norm)
{
	norm->tmp = ft_strdup(path[norm->i]);
	free(path[norm->i]);
	path[norm->i] = malloc(sizeof (char) * (ft_strlen(norm->tmp) + norm->size_add));
	if (!path[norm->i])
	{
		destroy_tab(path);
		path = NULL;
		return ;
	}
	norm->j = -1;
	norm->k = 0;
	while (norm->tmp[++norm->j])
		path[norm->i][norm->k++] = norm->tmp[norm->j];
	path[norm->i][norm->k++] = '/';
	norm->j = -1;
	if (cmd)
		while (cmd[++norm->j])
			path[norm->i][norm->k++] = cmd[norm->j];
	path[norm->i][norm->k++] = 0;
	free(norm->tmp);
}

void	put_cmd(char **path, char *cmd)
{
	t_path norm;

	norm.i = -1;
	norm.size_add = ft_strlen(cmd) + 2;
	while (path[++norm.i])
		put_cmd2(path, cmd, &norm);
	path[norm.i] = NULL;
}

char	*findpath(char *cmd, t_env **lst)
{
	int		i;
	char	**path;
	char	*new;

	i = 0;
	if (tdm(cmd) || ft_strcmp(cmd, "minishell") == 0)
		return (cmd);
	new = find_var(lst, "PATH=");
	if (new != NULL)
	{
		path = split2(new, ':');
		free(new);
		new = NULL;
		put_cmd(path, cmd);
		if (!path)
		{
			free(cmd);
			return (NULL);
		}
		i = 0;
		while (path[i] && access(path[i], X_OK) != 0)
			i++;
		if (path[i] != NULL)
			new = ft_strdup(path[i]);
		destroy_tab(path);
	}
	free(cmd);
	return (new);
}
