/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:16:53 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/01 14:27:47 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

/*path.c*/
typedef struct s_path
{
	int		i;
	int		j;
	int		k;
	int		size_add;
	char	*tmp;
}	t_path;

/*struct spe*/
typedef struct s_fd
{
	bool	is_output_redirected;
	bool	is_input_redirected;
	int		save_stdout;
	int		save_stdin;
	int		outfile;
	int		infile;
	int		here_doc_fd;
	int		*p1;
	int		*p2;
	bool	is_sig;
	bool	is_here_doc;
	bool	is_stdout;
}	t_fd;

typedef struct s_parse
{
	char	*path_minishell;
	char	*line;
	char	**cmd;
	char	**t;
	char	***bt;
	int		bt_size;
	int		child;
	char	***cmdopt;
	char **big;
}	t_parse;

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
	char			*var;
	struct s_env	*next;
}	t_env;

/*struct global*/
typedef struct s_global
{
	struct s_parse	*parse;
	struct s_fd		*sfd;
	struct s_env	**envi;
	struct s_pid	**pid;
}	t_global;

/*split2.c*/
typedef struct s_norm
{
	int			i;
	int			string;
	char const	*s;
	char		c;
}	t_norm;

/*export.c*/
typedef struct s_norm2
{
	t_env	*tmp;
	int		i;
	char	*str;
}	t_norm2;

/*cd.c*/
typedef struct s_norm3
{
	t_env	*tmp;
	char	*old_pwd;
	char	s[4096 + 1];
	int		exist;
	char	*str;
}	t_norm3;

/*env_var.c*/
typedef struct s_rep_var
{
	int		i;
	int		j;
	int		k;
	char	*new;
}	t_rep_var;

/*env_var.c*/
typedef struct s_rep_var2
{
	int		i;
	int		j;
	char	*ref_var;
	char	*new;
}	t_rep_var2;


#endif