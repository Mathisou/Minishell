NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iincludes -Isources/libft \
-g3 -fsanitize=address -O0
INC			=	includes/minishell.h includes/functions.h includes/define.h
MAIN		=	main.c
MAINS		=	$(addprefix sources/, $(MAIN))
UTIL		=	error.c split2.c check_line.c find_cmdopt.c
UTILS		=	$(addprefix sources/utils/, $(UTIL))  
PROMPT		=	rl.c path.c
PROMPTS		=	$(addprefix sources/prompt/, $(PROMPT))
BUILTIN		=	call.c pwd.c cd.c echo.c
BUILTINS	=	$(addprefix sources/builtins/, $(BUILTIN))
REDIRECTION =	parse_redirection.c
REDIRECTIONS=	$(addprefix sources/redirections/, $(REDIRECTION))
ENV			=	env_var.c find_var.c
ENVS		=	$(addprefix sources/env/, $(ENV))
LIBFT_PATH	=	sources/libft/
LIBFT		=	$(addsuffix libft.a, $(LIBFT_PATH))
OBJS		=	$(MAIN:.c=.o) $(PROMPT:.c=.o) $(UTIL:.c=.o) $(REDIRECTION:.c=.o) $(BUILTIN:.c=.o) $(ENV:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L$(LIBFT_PATH) -lft

$(OBJS):	$(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS) $(BUILTINS) $(ENVS) $(INC)
	$(CC) $(CFLAGS) -c $(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS) $(BUILTINS) $(ENVS)

$(LIBFT):
	@make -C $(LIBFT_PATH)

.PHONY:		all clean fclean re

all:		$(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean:		clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re:			fclean	$(NAME)
