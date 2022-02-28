/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:44:47 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 16:44:53 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/*prompt.c*/
char	*findpath(t_global *global, char *cmd, t_env **lst);
void	rl(t_global *global, char *pwd);
/*utils*/
char	**split_quotes(char *str, char sep, char **env);
char	*find_var(t_env **lst, char *var);
int		check_line(char *line);
char	***find_opt(char ***bt);
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
/*redirections*/
void	parsing_redirection(char **t, t_fd *sfd);
/*builtins*/
void	call_builtin(t_global *global, int i);
void	pwd(void);
void	cd(char *directory, t_env **lst);
void	echo_b(char **t);
void	exit_b(t_global *global);
void	env(t_env **lst);
void	unset(char **to_unset, t_env **lst);
void	export(t_env **lst, char **to_export);
/*own_env.c*/
void	take_env(char **env, t_env **envi);
char	**convert_env(t_env **lst);
/*list*/
t_env	*new_node(char *content);
void	add_node_back(t_env **first, char *content);
int		del_list(t_env **lst);
int		lst_size(t_env **lst);
/*free*/
void	destroy_big_tab(char ***bt);
void	free_end_line(t_global *global);
int		pid_del_list(t_pid **lst);
/*pipex*/
void	pipex(t_global *global);
int		here_doc(t_fd *sfd, char *limiter);
void	pid_add_node_back(t_pid **first, int content);
t_pid	*pid_new_node(int content);
void	wait_func(t_global *global);
void	reset_stdin_stdout(t_global *global);
/*libft*/
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**destroy_tab(char **t);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);

#endif
