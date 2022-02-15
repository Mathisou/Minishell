NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -Iincludes
INC		=	includes/include.h
MAIN	=	main.c
RL		=	rl.c
RLS		=	$(addprefix rl_manager/, $(RL))
OBJS	=	$(MAIN:.c=.o) $(RL:.c=.o)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

$(OBJS):	$(MAIN) $(RLS) $(INC)
	@echo $(MAIN) $(RLS)
	$(CC) $(CFLAGS) -c $(MAIN) $(RLS)

.PHONY:		all clean fclean re

all:		$(NAME)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean	$(NAME)