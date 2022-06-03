# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 16:39:01 by tnaton            #+#    #+#              #
#    Updated: 2022/03/10 18:44:51 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC		= gcc

CFLAGS = -Wall -Wextra -Werror

source = philo.c philo2.c ft_atoi.c ft_isdigit.c time.c thread.c thread2.c\
		 print.c

object = $(source:.c=.o)

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME) : $(object) 
	clang -pthread -pedantic $(object) -o $@

.PHONY: debug
debug : $(object) $(LIBFT) $(MLX)
	gcc -g3 -fsanitize=thread -pthread $(object) -o $@

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
	rm -rf $(object)

.PHONY: fclean
fclean :
	rm -rf $(NAME) $(object)

.PHONY: re
re : fclean all

$(object) : philo.h

.SECONDARY: $(object)
