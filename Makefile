NAME = minishell

SRC = parsing/check_string.c parsing/init_data.c parsing/utils.c main.c parsing/lexer.c parsing/utils_2.c parsing/free_stuff.c parsing/env.c parsing/env_free.c parsing/dollar_handle.c parsing/dollar_handle2.c parsing/expander.c built_in/ft_env.c built_in/pwd.c EXEC/parse_utils.c EXEC/parse.c EXEC/parser_cmd.c EXEC/utils.c EXEC/get_envpath.c EXEC/split_path.c EXEC/exec.c EXEC/redir.c built_in/ft_export.c built_in/ft_exit.c built_in/ft_echo.c built_in/ft_cd.c EXEC/check_built_in.c built_in/ft_unset.c EXEC/pipes.c EXEC/heredoc.c EXEC/utils2.c EXEC/signal.c EXEC/exec_2.c parsing/check_token.c

CFLAGS = -Wall -Wextra -Werror

#valgrind --leak-check=full --show-leak-kinds=all --suppressions=.valgrind_ignore -s ./minishell

OBJ = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f *.o
	rm -f parsing/*.o
	rm -f built_in/*.o
	rm -f EXEC/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


