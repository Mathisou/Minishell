/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:16:53 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/23 18:42:17 by maroly           ###   ########.fr       */
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
	int save_stdout;
	int outfile;
}	t_fd;

typedef struct s_parse
{
	char    *line;
	char    **cmd; 
	char    **t;
	char	***bt;
	char    ***cmdopt;
}   t_parse;


/*link list*/
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
}	t_global;

#endif