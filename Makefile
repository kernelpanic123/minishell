NAME = minishell

SRC = parsing/check_string.c parsing/init_data.c parsing/utils.c main.c parsing/lexer.c parsing/utils_2.c parsing/free_stuff.c parsing/env.c parsing/env_free.c parsing/dollar_handle.c parsing/dollar_handle2.c parsing/expander.c built_in/ft_env.c built_in/pwd.c

CFLAGS =


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

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
