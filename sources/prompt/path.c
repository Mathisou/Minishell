/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:46:27 by maroly            #+#    #+#             */
/*   Updated: 2022/03/02 19:03:59 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_cmd2(char **path, char *cmd, t_path *norm, t_global *global)
{
	norm->tmp = ft_strdup(path[norm->i]);
	if (!norm->tmp)
	{
		destroy_tab(path);
		free_n_exit(global);
	}
	free(path[norm->i]);
	path[norm->i] = malloc(sizeof (char)
			* (ft_strlen(norm->tmp) + norm->size_add));
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

static int	put_cmd(char **path, char *cmd, t_global *global)
{
	t_path	norm;

	if (!cmd)
		return (0);
	norm.i = -1;
	norm.size_add = ft_strlen(cmd) + 2;
	while (path[++norm.i])
		put_cmd2(path, cmd, &norm, global);
	path[norm.i] = NULL;
	return (1);
}

static char	*findpath2(char **path, t_global *global)
{
	int		i;
	char	*new;

	new = NULL;
	i = 0;
	while (path[i] && access(path[i], X_OK) != 0)
		i++;
	if (path[i] != NULL)
	{
		new = ft_strdup(path[i]);
		if (!new)
		{
			destroy_tab(path);
			free_n_exit(global);
		}
	}
	destroy_tab(path);
	if (new == NULL)
		return (NULL);
	return (new);
}

char	*findpath(char *cmd, t_env **lst, t_global *global)
{
	char	**path;
	char	*new;

	if (!cmd)
		free_n_exit(global);
	if (tdm(cmd) || ft_strcmp(cmd, "minishell") == 0)
		return (cmd);
	new = find_var(lst, "PATH=");
	if (new != NULL)
	{
		path = split2(new, ':');
		free(new);
		if (!put_cmd(path, cmd, global))
		{
			destroy_tab(path);
			free(cmd);
			return (NULL);
		}
		if (!path)
		{
			free(cmd);
			return (NULL);
		}
		new = findpath2(path, global);
		if (!new)
			return (cmd);
	}
	free(cmd);
	return (new);
}
