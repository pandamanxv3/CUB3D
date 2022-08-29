NAME = libft.a

SRCS = utils/ft_atoi.c utils/ft_isalpha.c utils/ft_itoa.c utils/ft_putchar_fd.c utils/ft_memcpy.c \
utils/ft_strjoin.c  utils/ft_strmapi.c  utils/ft_substr.c utils/ft_bzero.c utils/ft_isascii.c \
utils/ft_putendl_fd.c utils/ft_strchr.c utils/ft_strlcat.c utils/ft_strnstr.c utils/ft_tolower.c utils/ft_calloc.c \
utils/ft_isdigit.c utils/ft_memmove.c utils/ft_putnbr_fd.c utils/ft_strdup.c utils/ft_strlcpy.c utils/ft_strrchr.c \
utils/ft_toupper.c utils/ft_isalnum.c utils/ft_isprint.c utils/ft_memset.c utils/ft_putstr_fd.c utils/ft_striteri.c \
utils/ft_strlen.c utils/ft_strtrim.c utils/ft_memchr.c utils/ft_memcmp.c utils/ft_strcmp.c utils/ft_strncmp.c \
split/ft_split.c garbage_collector/garbage_collector.c garbage_collector/garbage_collector2.c garbage_collector/node_gc.c \
gnl/ft_strjoingnl.c gnl/get_next_line.c split2/ft_split2.c split2/ft_split2_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME): ${OBJS}
		@ar rcs ${NAME} ${OBJS}
		
.c.o:
		@${CC} ${CC_FLAGS} -g -c $< -o ${<:.c=.o}

all:	${NAME}

clean:
		@${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}

re:		fclean all