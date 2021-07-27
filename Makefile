# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 20:56:10 by sangcpar          #+#    #+#              #
#    Updated: 2021/07/25 20:56:12 by sangcpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philosopher

FLAGS = -Wall -Wextra -Werror -pedantic -pthread

CC = gcc

FILES =	main.c utils.c parsing.c thread_utils.c start_thread.c

all: $(NAME)

$(NAME):
	$(CC) $(FILES) $(FLAGS) -o $(NAME)

clean:
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all
