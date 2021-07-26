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

FLAGS = -Wall -Wextra -Werror -pedantic

ifeq ($(shell uname), Linux)
 CXX = gcc
 FLAGS += -pthread
else
 CXX = clang
endif
ifdef REALG
 CXX = ~/.brew/bin/gcc-10
endif
ifdef DEBUG
 FLAGS += -g -fsanitize=address
endif

FILES =	main.c 

all: $(NAME)

$(NAME):
	$(CXX) $(FILES) $(FLAGS) -o $(NAME)

clean:
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: FLAGS += -g -fsanitize=thread
debug: re
	TSAN_OPTIONS=second_deadlock_stack=1 ./$(NAME) 4 410 200 200 2

