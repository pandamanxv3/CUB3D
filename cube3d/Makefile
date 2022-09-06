# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/03 04:38:46 by aboudjel          #+#    #+#              #
#    Updated: 2022/09/06 20:03:14 by adben-mc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

C_FILES =	sources/cub3d.c sources/parsing/get_param_and_map.c \
			sources/parsing/parsing_map.c sources/parsing/utils_parsing.c \
			sources/parsing/are_params_correct.c \
			sources/parsing/init_struct.c \
			sources/parsing/get_file.c sources/parsing/expand_map_size.c \
			sources/parsing/ft_get_pixel.c sources/hook.c sources/utils.c
			
CC = cc

MLX_FLAGS	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

CFLAGS = -Werror -Wall -Wextra -g3# -fsanitize=address

RM = rm -f

O_FILES = ${C_FILES:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

${NAME} : ${O_FILES}
	@make -C libft
	@make -C mlx_linux
	@${CC} ${O_FILES} libft/libft.a -g $(MLX_FLAGS) -o ${NAME}

clean:
	@${RM} ${O_FILES}

fclean: clean
	@make fclean -C libft
	@make clean -C mlx_linux
	@${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re