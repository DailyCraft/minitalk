# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 10:47:34 by dvan-hum          #+#    #+#              #
#    Updated: 2024/11/29 13:40:06 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CC = gcc -Wall -Wextra -Werror

SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = $(patsubst %.c, obj/%.o, $(SRC_CLIENT))
OBJ_SERVER = $(patsubst %.c, obj/%.o, $(SRC_SERVER))
INCLUDES = ./

all: $(NAME)

makelibft:
	make -C libft
	cp libft/libft.a .

$(NAME): makelibft $(OBJ_CLIENT) $(OBJ_SERVER)
	$(CC) $(OBJ_CLIENT) -o client -I ./libft -L ./libft -lft
	$(CC) $(OBJ_SERVER) -o server -I ./libft -L ./libft -lft

obj/%.o: src/%.c | ./obj
	$(CC) -c $< -o $@ -I $(INCLUDES) -I ./libft -L ./libft -lft

./obj:
	mkdir obj

clean:
	rm -rf ./obj libft.a
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

bonus: all