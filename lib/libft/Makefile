NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = ft_isalnum.c ft_isalpha.c ft_isdigit.c \
       ft_isprint.c ft_isascii.c ft_strlen.c \
       ft_memset.c ft_bzero.c ft_memcpy.c \
       ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c \
       ft_memcmp.c ft_strnstr.c ft_atoi.c \
       ft_calloc.c ft_strdup.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c \
	   ft_split.c ft_itoa.c ft_strmapi.c \
	   ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c \
	   gnl/get_next_line.c gnl/get_next_line_utils.c \
	   ft_printf/ft_printf.c ft_printf/ft_utoa.c \
	   ft_printf/hex_conversion.c ft_printf/put_variables.c \
	   ft_realloc.c ft_2dstr_dup.c ft_2dstr_free.c \
	   ft_2dstr_len.c ft_2dstr_printf.c ft_2dstr_realloc.c \
	   ft_debug.c check_for_overflow.c ft_atof.c ft_arr2d_free.c

SRCS_BONUS = ft_lstnew.c ft_lstsize.c ft_lstadd_back.c \
			 ft_lstadd_front.c ft_lstlast.c ft_lstdelone.c \
			 ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
			ar rcs $(NAME) $(OBJS)

bonus:		${OBJS} ${OBJS_BONUS}
			ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
