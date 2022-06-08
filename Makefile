# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 17:56:49 by elpastor          #+#    #+#              #
#    Updated: 2022/06/08 16:10:02 by elpastor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

DIR_S = srcs/

HEADER = includes/

SOURCES = philo.c 

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = ${SRCS:.c=.o}

FLAGS = -I $(HEADER) -Wall -Wextra -Werror -pthread

all:	${NAME}

.c.o:
	cc ${FLAGS} -c $^ -o $@

${NAME}: ${OBJS} $(HEADER)
	cc ${FLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY: all clean fclean re