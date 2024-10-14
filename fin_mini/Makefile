# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 11:22:29 by hichokri          #+#    #+#              #
#    Updated: 2024/10/14 01:32:24 by hichokri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SAN = -fsanitize=address
CFLAGS = -g3 $(SAN) 

SRC = main.c utils/ft_split.c \
		utils/ft_strdup.c utils/ft_free.c utils/ft_strlen.c utils/ft_strjoin.c \
		utils/ft_putstr.c env_creation/ft_strchr.c utils/parse_utils.c \
		env_creation/create_env_list.c env_creation/env_utils.c utils/ft_strlcpy.c \
		utils/ft_atoi.c utils/ft_strcmp.c utils/ft_substr.c utils/ft_strlcat.c \
		token_parsing/parsing.c token_parsing/tokenization.c utils/ft_strndup.c utils/ft_strncmp.c \
		builtins/cd.c builtins/export.c token_parsing/expantion.c utils/count_args.c \
       builtins/echo.c builtins/env.c builtins/pwd.c builtins/unset.c execution/execute.c 

OBJ = ${SRC:.c=.o}

NAME = minishell

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lreadline 

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
