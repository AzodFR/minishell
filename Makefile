NAME = minishell

LIBFT = libftprintf.a


INCLUDES = includes/

SRC = srcs/

FLAGS = -Wall -Wextra -Werror -L. -lftprintf -g3 -fsanitize=address

CC = gcc $(FLAGS)

FILES = mishell.c welcome.c \
		builtins/pwd.c builtins/env.c \
		builtins/cd.c \
		env/env_lst.c env/env_edit.c\
		utils/cmd_handler.c \
		utils/trim_args.c utils/exit.c \
		utils/init_env.c

RM = rm -f

OBJ = $(addprefix $(SRC), $(FILES))

$(NAME): $(LIBFT) 
	@$(CC) $(OBJ) -o $@ -I$(INCLUDES) -Ilibft/${INCLUDES}
	@printf "$(notdir $@) [\033[32m✔️\033[0m]\n"

$(LIBFT):
	make -C libft/
	@cp libft/$(LIBFT) .

all: $(NAME)

clean:
	@make clean -C libft/
	@$(RM) $(LIBFT)
	@printf "$(LIBFT) [\033[31mX\033[0m]\n"

fclean: clean
	@make fclean -C libft/
	@$(RM) $(NAME)
	@printf "$(NAME) [\033[31mX\033[0m]\n"

m : all
	@clear
	./minishell
re: fclean all

.PHONY: all clean fclean re minishell libftprintf.a 