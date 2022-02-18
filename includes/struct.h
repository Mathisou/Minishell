/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:16:53 by hkovac            #+#    #+#             */
/*   Updated: 2022/02/18 14:31:38 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_fd
{
	int save_stdout;
	int outfile;
}	t_fd;

typedef struct s_env
{
    char            *var;
    struct s_env    *next;
}   t_env;

#endif