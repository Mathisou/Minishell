NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iincludes -Isources/libft/libft.h
INC			=	includes/minishell.h includes/functions.h includes/define.h
MAIN		=	main.c
MAINS		=	$(addprefix sources/, $(MAIN)) 
PROMPT		=	rl.c path.c
PROMPTS		=	$(addprefix sources/prompt/, $(PROMPT))
LIBFT_PATH	=	sources/libft/
LIBFT		=	$(addsuffix libft.a, $(LIBFT_PATH))
OBJS		=	$(MAIN:.c=.o) $(PROMPT:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline -L$(LIBFT_PATH) -lft $(OBJS) -o $(NAME)

$(OBJS):	$(MAINS) $(PROMPTS) $(INC)
	$(CC) $(CFLAGS) -c $(MAINS) $(PROMPTS)

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