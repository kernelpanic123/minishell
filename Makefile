NAME = minishell

SRC = check_string.c init_data.c utils.c main.c lexer.c utils_2.c free_stuff.c env.c env_free.c dollar_handle.c dollar_handle2.c expander.c

CFLAGS =


OBJ = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
