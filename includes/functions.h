/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/02/22 11:21:17 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/*prompt.c*/
char	*findpath(char *cmd, t_env **lst);
void	rl(char **env, t_global *s_global);
/*utils*/
char    **split_quotes(char *str, char sep, char **env);
char    *find_var(t_env **lst, char *var);
int      check_line(char *line);
char	**find_opt(char **t);
char	**split2(char const *s, char c);
void check_var_and_quotes(char **t, t_env **lst);
int		check_limiter(char *str);
int		count_delete(char *str);
int		is_there_quotes(char *str);
int		is_there_dollar(char *str);
int		should_replace_var(char *str, int dollarindex);
int         tdm(char *cmd);
/*redirections*/
void	parsing_redirection(char **t, t_fd *sfd);
/*builtins*/
void	call_builtin(t_global *global);
void	pwd();
void	cd(char *directory);
void	echo_b(char **t);
void    exit_b(t_global *parse);
void    env(t_env **lst);
void    unset(char *to_unset, t_env **lst);
void    export(t_env **lst, char *to_export);
/*own_env.c*/
void    take_env(char   **env, t_env **envi);
/*list*/
t_env    *new_node(char *content);
void    add_node_back(t_env **first, char *content);
int        del_list(t_env **lst);
void    echo_b(char **t);

#endif
