NAME = libft.a
CC = gcc
RM = rm -f


SRC = srcs/
INCLUDE = includes/


HEADER = libft.h

FILES = ft_atoi.c ft_isalpha.c \
		ft_isalnum.c ft_isdigit.c \
		ft_isascii.c ft_isprint.c \
		ft_tolower.c ft_toupper.c \
		ft_strlen.c ft_strnstr.c \
		ft_strncmp.c ft_strchr.c \
		ft_strrchr.c ft_strlcpy.c \
		ft_strlcat.c ft_memset.c \
		ft_memcmp.c ft_memchr.c \
		ft_memcpy.c ft_memccpy.c \
		ft_memmove.c ft_calloc.c \
		ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_digitlen.c \
		ft_itoa.c ft_strmapi.c \
		ft_bzero.c ft_itoa_base.c \
		ft_ulltoa_base.c ft_advanced_sort_tab.c \
		ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstrchr_fd.c ft_putstr_len.c \
		ft_putchar_len.c ft_putunbr_fd.c \
		ft_wrmalloc.c

BONUS_FILES =	ft_lstnew.c ft_lstadd_front.c \
				ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c


OBJ = $(addprefix ${SRC}, ${FILES})
BONOBJ = $(addprefix ${SRC}, ${BONUS_FILES})
HFILES = $(addprefix ${INCLUDE}, ${HEADER})

OBJS = ${OBJ:.c=.o}
BONUS = ${BONOBJ:.c=.o}
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ${HFILES}
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCLUDE}
		@printf "\e[?25l\e[JCreated \e[92m$(notdir $@) \e[0m\r"



${NAME}: ${OBJS}
		@ar rcs ${NAME} ${OBJS}
		@printf "\n\033[1m\033[32mlibft.a \033[1m\033[32mgenerated !\n\n\033[0m"



bonus : ${NAME} ${BONUS}
		@ar rcs ${NAME} ${BONUS}


all:	${NAME}

clean:
		@${RM} ${OBJS} ${BONUS}
		@printf "\033[31mDeleting\033[0m >>\033[31m \033[1mall libft .o files\n\033[0m"

fclean: clean
		@${RM} ${NAME}
		@printf "\033[31mDeleting\033[0m >>\033[31m \033[1mlibft.a\n\033[0m"

lclean:
	@${RM} ${NAME}
	@printf "\033[31mDeleting\033[0m >>\033[31m \033[1mlibft.a\n\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus libft.a
