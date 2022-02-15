# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroly <maroly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 13:36:30 by maroly            #+#    #+#              #
#    Updated: 2022/02/03 23:02:50 by maroly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_isalpha.c				\
	       		ft_isdigit.c				\
	       		ft_isalnum.c				\
	       		ft_isascii.c				\
	       		ft_isprint.c				\
	       		ft_strlen.c					\
	       		ft_memset.c					\
	       		ft_bzero.c					\
	       		ft_memcpy.c					\
	       		ft_memmove.c				\
	       		ft_strlcpy.c				\
	       		ft_strlcat.c				\
	       		ft_toupper.c				\
	       		ft_tolower.c				\
	       		ft_strchr.c					\
	       		ft_strrchr.c				\
	       		ft_strncmp.c				\
	       		ft_memchr.c					\
	       		ft_memcmp.c					\
	       		ft_strnstr.c				\
	       		ft_atoi.c					\
	       		ft_calloc.c					\
	       		ft_strdup.c					\
	       		ft_substr.c					\
	       		ft_strjoin.c				\
	       		ft_strtrim.c				\
	       		ft_split.c					\
	       		ft_itoa.c					\
	       		ft_strmapi.c				\
	       		ft_striteri.c				\
	       		ft_putchar_fd.c				\
	       		ft_putstr_fd.c				\
	       		ft_putendl_fd.c				\
	       		ft_putnbr_fd.c				\
				get_next_line.c				\
				ft_lstnew.c					\
	       		ft_lstadd_front.c			\
	       		ft_lstsize.c				\
	       		ft_lstlast.c				\
	       		ft_lstadd_back.c			\
	       		ft_lstdelone.c				\
	       		ft_lstclear.c				\
	       		ft_lstiter.c				\
	       		ft_lstmap.c					\
	    	   	ft_putchar_bonus.c			\
	    	    ft_putnbr_bonus.c			\
	   	 	   	ft_swap_bonus.c				\
	     	  	ft_putstr_bonus.c			\
	   	    	ft_strcpy_bonus.c			\
	   	    	ft_strncpy_bonus.c			\
	   	    	ft_strlowcase_bonus.c		\
	    	   	ft_strcapitalize_bonus.c	\
	   	    	ft_strcmp_bonus.c			\
	    	   	ft_strcat_bonus.c			\
	   	    	ft_strncat_bonus.c			\
	    	   	ft_strstr_bonus.c			\
	   	    	ft_check_base_bonus.c		\
				ft_putnbr_base_bonus.c		\
	     	  	ft_atoi_base_bonus.c		\
	    	   	ft_factorial_bonus.c		\
	     	  	ft_power_bonus.c			\
	     	  	ft_fibonacci_bonus.c		\
	  	     	ft_sqrt_bonus.c				\
	  	     	ft_is_prime_bonus.c			\
	    	   	ft_range_bonus.c			\
	   	    	ft_ultimate_range_bonus.c	\
	    	   	ft_ultimate_strjoin_bonus.c	\
	    	   	ft_convert_base_bonus.c		\
	   	    	ft_stock_file_bonus.c		\
	    	   	ft_foreach_bonus.c			\
	   	    	ft_map_bonus.c				\
	   	    	ft_is_sort_bonus.c			\
	   	    	ft_sort_string_tab_bonus.c	\
	   	    	ft_count_strings_bonus.c	\
	   	    	ft_sort_list_bonus.c		\
	  	     	ft_list_remove_if_bonus.c	\
	   	    	ft_is_power_of_2_bonus.c	\

OBJS		=  	$(SRCS:.c=.o)

CC			= 	gcc

FLAGS		= 	-Wall -Wextra -Werror

NAME		= 	libft.a

all			:	$(NAME)
		
.c.o		:		
				@echo "\t\t    \033[33;32mCreation of $(NAME) in progress...\033[33;32m"
				@$(CC) $(FLAGS) -c $<

$(NAME)		:	$(OBJS)
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)
				@echo "\t\t\t\t \033[33;32mDONE.\033[33;32m"

clean		:
				@rm -rf *.o
				@echo "\t\t      \x1b[31mfiles .o deleted successfully.\x1b[31m"

fclean		:	clean
				@rm -f $(NAME)
				@echo "\t\t       \x1b[31m$(NAME) deleted sucessfully.\x1b[31m"

re			:	fclean all

.PHONY		: 	all, clean, fclean, re
