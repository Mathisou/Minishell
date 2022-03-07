NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iincludes \
#-g -O0 -fsanitize=address
INC			=	includes/minishell.h includes/functions.h
MAIN		=	main.c
MAINS		=	$(addprefix sources/, $(MAIN))
UTIL		=	split2.c split3.c split4.c check_line.c find_cmdopt.c truc_de_merde.c pipe_split.c free_all.c \
ft_atoi.c ft_isalnum.c ft_itoa.c ft_strncmp.c ft_strcmp_bonus.c ft_strdup.c ft_strlen.c tools.c find_cmdopt2.c free_all2.c
UTILS		=	$(addprefix sources/utils/, $(UTIL))  
PROMPT		=	rl.c path.c rl2.c
PROMPTS		=	$(addprefix sources/prompt/, $(PROMPT))
BUILTIN		=	call.c pwd.c cd.c echo.c exit.c env.c unset.c export.c
BUILTINS	=	$(addprefix sources/builtins/, $(BUILTIN))
REDIRECTION =	parse_redirection.c
REDIRECTIONS=	$(addprefix sources/redirections/, $(REDIRECTION))
ENV			=	env_var.c env_var2.c find_var.c env_var_utils.c own_env.c
ENVS		=	$(addprefix sources/env/, $(ENV))
LIST        =   list.c
LISTS       =   $(addprefix sources/list/, $(LIST))
PIPEX		=	pipex.c pipex2.c here_doc.c utils.c
PIPEXS		=	$(addprefix sources/pipex/, $(PIPEX))
OBJS		=	$(MAIN:.c=.o) $(PROMPT:.c=.o) $(UTIL:.c=.o) $(REDIRECTION:.c=.o) $(BUILTIN:.c=.o) $(ENV:.c=.o) $(LIST:.c=.o) $(PIPEX:.c=.o)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJS):	$(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS) $(BUILTINS) $(ENVS) $(LISTS) $(PIPEXS) $(INC)
	$(CC) $(CFLAGS) -c $(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS) $(BUILTINS) $(ENVS) $(LISTS) $(PIPEXS)


.PHONY:		all clean fclean re

all:		$(NAME)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean	$(NAME)
