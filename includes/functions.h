/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/02/17 17:56:19 by maroly           ###   ########.fr       */
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
char	**find_opt(char **t);
char	**split2(char const *s, char c);
void	check_var_and_quotes(char **t);
/*redirections*/
void	parsing_redirection(char **t, t_fd *sfd);

#endif
