/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:19:32 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

/*prompt.c*/
char	*findpath(char *cmd, t_env **lst, t_global *global);
void	rl(t_global *global);
int		check_line_redirection(char **t);
void	quit(t_global *global);
/*utils*/
void	init_rl(t_global *global);
char	**split_quotes(char *str, char sep, char **env);
char	*find_var(t_env **lst, char *var);
int		check_line(char *line);
char	***find_opt(char ***bt, t_global *global);
char	**split2(char const *s, char c);
void	check_var_and_quotes(char **t, t_env **lst, t_global *global);
int		check_limiter(char *str);
int		count_delete(char *str);
int		is_there_quotes(char *str);
int		is_there_dollar(char *str);
int		should_replace_var(char *str, int dollarindex);
int		tdm(char *cmd);
void	pipe_split(t_global *global);
int		count_double_tab(char **t);
int		count_triple_tab(char ***t);
int		find_cmd(t_global *global);
char	*strcats(char *s1, char *s2);
int		cmdopt_size(char **cmdopt);
int		check_chev(char *str);
int		is_a_directory(char *str);
/*redirections*/
int		parsing_redirection(char **t, t_fd *sfd);
void	reset_stdin_stdout(t_global *global);
int		is_last_here_doc(char **t);
/*builtins*/
void	call_builtin(t_global *global, int i, int sign);
void	pwd(t_global *global);
void	cd(char *directory, t_env **lst, t_global *global, int sign);
void	echo_b(char **t, t_global *global);
void	exit_b(t_global *global, int sign);
void	env(t_env **lst, t_global *global);
void	unset(char **to_unset, t_env **lst, t_global *global, int sign);
void	export_b(t_env **lst, char **to_export, t_global *global, int sign);
/*own_env.c*/
char	*statu(t_global *global);
char	*replace_var(char *old_str, t_env **lst, t_global *global);
void	remove_quotes2(char *old_str, char *n, int *i, int *j);
char	*find_ref_var(char *old_str, t_env **lst, t_global *global);
void	take_env(char **env, t_env **envi, char *av, t_global *global);
char	**convert_env(t_env **lst);
int		dollar_count(char *str);
/*list*/
t_env	*new_node(char *content);
void	add_node_back(t_env **first, char *content, t_global *global);
int		del_list(t_env **lst);
int		lst_size(t_env **lst);
/*free*/
void	destroy_big_tab_size(char ***bt, int size);
void	destroy_big_tab(char ***bt);
void	free_end_line(t_global *global);
int		pid_del_list(t_pid **lst);
void	free_in_child(t_global *global);
void	free_n_exit(t_global *global);
/*pipex*/
void	pipex(t_global *global);
int		here_doc(t_fd *sfd, char *limiter);
void	pid_add_node_back(t_pid **first, int content);
t_pid	*pid_new_node(int content);
void	wait_func(t_global *global);
void	execute(t_global *global, int i);
void	close_fd(t_global *global);
void	opening_child(t_global *global, int sign, int i);
/*libft*/
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**destroy_tab_size(char **t, int size);
char	**destroy_tab(char **t);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
/*split*/
void	test62(int *i, int *size, char const *s);
void	test60(int *i, int *size, char const *s);
void	test_p(int *i, int *size, char const *s);
int		create_tab(char const *s, char c);
void	put_str_in_tab2(char *str, int *i, const char *s);
char	*count_mall(const char *s, char c);
char	*put_str_in_tab(const char *s, char c);

#endif
