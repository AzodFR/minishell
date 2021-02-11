NAME = minishell

LIBFT = libftprintf.a


INCLUDES = includes/

SRC = srcs/

FLAGS = -Wall -Wextra -Werror -g3 -ltermcap -lncurses -L. -lftprintf -fsanitize=address

CC = gcc $(FLAGS)

FILES = mishell.c welcome.c \
		builtins/pwd.c builtins/env.c \
		builtins/cd.c builtins/export.c \
		builtins/unset.c builtins/echo.c \
		builtins/exit.c \
		env/env_lst.c env/env_edit.c \
		env/env_to_tab.c env/env_remove.c \
		utils/cmd_handler.c \
		utils/trim_args.c utils/exit.c \
		utils/init_env.c \
		utils/translator.c utils/file_searcher.c \
		utils/prepare_array.c \
		perso/donut.c tree/build_tree.c \
		tree/node_control.c \
		exec/exec_cmd.c exec/piped.c exec/redir.c \
		signals/sig_c.c utils/file_opener.c tree/test.c \
		exec/process.c

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
	@rm -rf minishell.dSYM
	@./minishell

re: fclean all

.PHONY: all clean fclean re minishell libftprintf.a 