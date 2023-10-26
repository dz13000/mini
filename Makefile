# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 15:02:24 by mabed             #+#    #+#              #
#    Updated: 2023/10/26 13:35:58 by cabouzir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	main.c $(addprefix parcing/, verif_quote.c enum.c enum2.c structure.c syntax_error.c env.c dollar_quote.c dollar_quote2.c dollar.c dollar2.c structure2.c)\

OBJS	=	${SRCS:.c=.o}

LIBFT = libft/libft.a

NAME = minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
			make -C libft
			$(CC) $(OBJS) $(LIBFT) -g -o $(NAME) -lreadline

clean:
				make -C libft clean
				rm -f ${OBJS}

fclean:		clean
				make clean
				rm -f ${NAME} $ $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
