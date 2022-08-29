# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 03:43:32 by cbarbit           #+#    #+#              #
#    Updated: 2022/07/16 01:08:32 by aboudjel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

C_FILES =	sources/cub3d.c sources/parsing/get_param_and_map.c \
			sources/parsing/parsing_map.c sources/parsing/utils_parsing.c \
			sources/parsing/are_params_correct.c \
			sources/parsing/init_struct_and_get_file.c
			
CC = cc

CFLAGS = -Werror -Wall -Wextra -g3 

RM = rm -f

O_FILES = ${C_FILES:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${O_FILES}
	@${MAKE} -C libft
	@${CC} ${O_FILES} libft/libft.a -g -o ${NAME}

clean:
	@${RM} ${O_FILES}

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re