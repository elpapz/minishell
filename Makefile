# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 00:38:37 by acanelas          #+#    #+#              #
#    Updated: 2023/06/19 00:55:58 by acanelas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRC =	
		main.c

NAME = minishell
CC = cc
CLINE = -lreadline
CFLAGS = -Wall -Wextra -Werror
CLEAKS = -Wall -Wextra -Werror -fsanitize=adress
REMOVE = rm -rf
LIBFT = ./libft/libft.a
OBF = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBF)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBF) $(LIBFT) $(CLINE) -o $(NAME)

clean:
	$(REMOVE) $(OBF)
	$(MAKE) clean -C ./libft

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
