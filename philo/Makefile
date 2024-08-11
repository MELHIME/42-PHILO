# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:13:13 by mel-hime          #+#    #+#              #
#    Updated: 2024/06/29 12:28:14 by mel-hime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = initialisation.c main.c philo_tools.c routine.c supervisor.c threads.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = cc

%.o : %.c philo.h
	@$(CC) $(CFLAGS) -c -o $@ $< 

all : $(NAME)
	
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re