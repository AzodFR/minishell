NAME = minishell

LIBFT = libftprintf.a


INCLUDES = includes/

SRC = srcs/

FLAGS = -Wall -Wextra -Werror -g3

CC = gcc $(FLAGS)

I := 1


FILES = mishell.c welcome.c \
		builtins/pwd.c builtins/env.c \
		builtins/cd.c builtins/export.c \
		builtins/unset.c builtins/echo.c \
		builtins/exit.c builtins/export_utils.c\
		env/env_lst.c env/env_edit.c \
		env/env_to_tab.c env/env_remove.c \
		utils/cmd_handler.c \
		utils/exit.c \
		utils/init_env.c \
		utils/translator.c utils/file_searcher.c \
		utils/prepare_array.c \
		perso/donut.c tree/build_tree.c \
		tree/node_control.c \
		exec/exec_cmd.c exec/piped.c exec/redir.c \
		signals/sig_c.c utils/file_opener.c tree/recreate_parse.c \
		exec/process.c utils/preparator.c utils/treat.c \
		utils/search_exec.c utils/prep_checker.c \
		utils/tokenize.c tree/prep_tree.c tree/build_utils.c

RM = rm -f

OBJ = $(addprefix $(SRC), $(FILES))

OBJS = $(OBJ:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) -L. -lftprintf -o $@ -I$(INCLUDES) -Ilibft/${INCLUDES}
	@printf "\n\e[36mMI\e[33mSHELL \e[92mis ready !\e[0m\e[?25h\n"

$(LIBFT):
	@make -C libft/
	@cp libft/$(LIBFT) .

%.o: %.c $(INCLUDES) libft/${INCLUDES}
	@gcc -Wall -Wextra -Werror -g3 -o $@ -c $< -I$(INCLUDES) -Ilibft/${INCLUDES}
	@printf "\e[?25l\e[JCreated \e[92m$(notdir $@)\e[0m\r"

all: $(NAME)

clean:
	@make clean -C libft/
	@$(RM) $(LIBFT)
	@$(RM) $(OBJS)
	@printf "$(LIBFT) [\033[31mX\033[0m]\n"

fclean: clean
	@make fclean -C libft/
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@printf "$(NAME) [\033[31mX\033[0m]\n"

m : all
	@clear
	@rm -rf minishell.dSYM
	@./minishell

re: fclean all

.PHONY: all clean fclean re minishell libftprintf.a 
