/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/02/18 15:20:42 by maroly           ###   ########.fr       */
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
int		check_limiter(char *str);
int		count_delete(char *str);
int		is_there_quotes(char *str);
int		is_there_dollar(char *str);
int		should_replace_var(char *str, int dollarindex);
/*redirections*/
void	parsing_redirection(char **t, t_fd *sfd);
/*builtins*/
void	call_builtin(char *cmd, char **t);
void	pwd();
void	cd(char *directory);
void	echo_b(char **t);

#endif
