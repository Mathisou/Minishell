/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/02/16 15:16:26 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/*prompt.c*/
char	*findpath(char *cmd, char **env);
void	rl(char **env);
/*utils*/
char    **split_quotes(char *str, char sep, char **env);
char    *find_var(char **env, char *var);
int      check_line(char *line);

#endif
