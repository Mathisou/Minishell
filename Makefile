NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iincludes -Isources/libft \
-g3 -fsanitize=address -O0
INC			=	includes/minishell.h includes/functions.h includes/define.h
MAIN		=	main.c
MAINS		=	$(addprefix sources/, $(MAIN))
UTIL		=	split_quotes.c find_var.c check_line.c find_cmdopt.c
UTILS		=	$(addprefix sources/utils/, $(UTIL))  
PROMPT		=	rl.c path.c
PROMPTS		=	$(addprefix sources/prompt/, $(PROMPT))
REDIRECTION =	parse_redirection.c
REDIRECTIONS=	$(addprefix sources/redirections/, $(REDIRECTION))
LIBFT_PATH	=	sources/libft/
LIBFT		=	$(addsuffix libft.a, $(LIBFT_PATH))
OBJS		=	$(MAIN:.c=.o) $(PROMPT:.c=.o) $(UTIL:.c=.o) $(REDIRECTION:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L$(LIBFT_PATH) -lft

$(OBJS):	$(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS) $(INC)
	$(CC) $(CFLAGS) -c $(MAINS) $(PROMPTS) $(UTILS) $(REDIRECTIONS)

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
