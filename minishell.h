/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:01:42 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/30 01:00:17 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>

#define WORD		1    // word
#define PIPE		2    // |
#define GREAT		3    // >
#define LESS		4    // <
#define GREATGREAT	5    // >>
#define LESSLESS	6    // <<

typedef struct s_lexer
{
	char	*str;
	int		token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env
{
	char	*variable;
	char 	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	bool simple_quotes;
	bool double_quotes;
}	t_data;

typedef struct s_expand
{
	bool	in_single;
	bool	in_double;
	t_env	*env;
	int		exit_status;
}	t_expand;

typedef struct s_minishell
{
	t_env	*env;
	int		exit_status;
}	t_minishell;

//utils
int ft_strlen(char *str);
int is_whitespace(char c);
int skip_quotes(char *input, t_data *data);
char *ft_substr(char *str, int start, int len);
void print_list(t_lexer *list);

//init_data
void init_struct(t_data *data);
int process_input(t_lexer **list, char *input, t_data *data);

//check_string
char *delete_espace(char *input, t_data *data);
int check_pipe(t_lexer **list);
int check_first_token(t_lexer **list);
int parse(t_lexer **list);
int check_invalid_token(t_lexer **list);

//lexer
int what_type_token(char *str);
t_lexer	*new_node(int token, char *str);
static int	skip_token(char *input, int i);
void	add_element(char *input, t_lexer **list);
void add_to_back(t_lexer **list, char *str, int token);

//utils_2
char 	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);

//free_stuff
void	free_list_token(t_lexer **list);

//env
char	**copy_env(char **env);
void	addback_env(t_env **list, char *variable, char *value);
t_env	*new_env_node(char *variable, char *value);
char	*get_variable(char *str);
char	*get_value(char *str);

//env_free
void add_env_list(t_env **env, char **envp);
void free_env_copy(char **str);
void free_list_env(t_env **list);

#endif