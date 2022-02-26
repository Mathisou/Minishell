/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:16:53 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/26 13:43:02 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# include <stdbool.h>

/*path.c*/
typedef struct s_path
{
	int		i;
	int		j;
	int		k;
	int		size_add;
	char	*tmp;
}	t_path;

/*split2*/
typedef struct s_norm
{
	int			i;
	int			string;
	char const	*s;
	char		c;
} t_norm;

/*struct spe*/
typedef struct s_fd
{
	bool	is_output_redirected;
	bool	is_input_redirected;
	int		save_stdout;
	int		outfile;
	int		*p1;
	int		*p2;
}	t_fd;

typedef struct s_parse
{
	char	*path_minishell;
	char    *line;
	char    **cmd;
	char    **t;
	char	***bt;
	int		bt_size;
	int		child;
	char    ***cmdopt;
}   t_parse;

/*link list pid*/
typedef struct s_pid
{
	int				pid;
	int				statu;
	struct s_pid	*next;
}	t_pid;

/*link list env*/
typedef struct s_env
{
	char            *var;
	struct s_env    *next;
}   t_env;

/*struct global*/
typedef struct s_global
{
	struct s_parse	*parse;
	struct s_fd		*sfd;
	struct s_env	**envi;
	struct s_pid	**pid;
}	t_global;

#endif