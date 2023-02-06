# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaber <asaber@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 20:41:51 by asaber            #+#    #+#              #
#    Updated: 2023/02/05 20:22:06 by asaber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

Client = client.c

Server = server.c 


OBJS_C = $(Client:.c=.o)

OBJS_S = $(Server:.c=.o)


Client_bonus = client_bonus.c

Server_bonus = server_bonus.c


OBJS_CB = $(Client_bonus:.c=.o)

OBJS_SB = $(Server_bonus:.c=.o)

RM	= rm -f

all: client server

server : $(Server)
	$(CC) $(CFLAGS) $^ -o $@

client : $(Client)
	$(CC) $(CFLAGS) $^ -o $@

    
clean:
	rm -f client client_bonus server server_bonus

fclean: clean

re: fclean all bonus

bonus: client_bonus server_bonus


server_bonus : $(Server_bonus)
	$(CC) $(CFLAGS) $^ -o $@

client_bonus : $(Client_bonus)
	$(CC) $(CFLAGS) $^ -o $@