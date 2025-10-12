/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:01:42 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/30 17:02:50 by abtouait         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

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

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;	// prochaine redirection
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

//EXEC

//pipes
void	execute_cmd_in_pipe(t_cmd *cmd, t_minishell *shell);
void	setup_pipe_redirs(int prev_fd, int pipe_fd[2], t_cmd *cmd);
void	execute_pipeline(t_cmd *cmd_list, t_minishell *shell);

//check_bulitin
int	is_builtin(char *cmd);
int	execute_builtin(char **args, t_minishell *shell);

//ft_exit
int	ft_exit(t_minishell *shell);

//ft_cd
void	update_env_var(t_env **env, char *var, char *value);
int		ft_cd(char **args, t_env **env);

//ft_export
void	print_export(t_env *env);
int	is_valid_char(char c, int first);
int	is_valid_identifier(char *str);
int	ft_export(char **args, t_env **env);


//ft_unset
void	remove_env_var(t_env **env, char *del_var);
int	ft_unset(char **args, t_env **env);

//ft_echo
int	ft_echo(char **args);

//ft_env.c
int ft_env(t_env *list);

//pwd
int ft_pwd(void);

//redir
int	handle_less(char *file);
int	handle_great(char *file);
int	handle_greatgreat(char *file);
int	handle_redirection(t_redir *redirs);

//exec.c
char	**env_to_array(t_env *env);
void	execute_simple_cmd(t_cmd *cmd, t_minishell *shell);
void	execute_commands(t_cmd *cmd, t_minishell *shell);

//split_path
char	*extract_one_path(char *path_env, int *i);
char	**split_path(char *path_env);
char	*join_path(char *dir, char *cmd);
char	*find_command_path(char *cmd, t_env *env);

//get_path_env
char	*get_path_env(t_env *env);

//exec/utils
char	*ft_strchr(char *s, int c);
void	free_array(char **array);
int	file_exists(char *path);
int	count_paths(char *path_env);
char	*ft_strjoin(char *variable, char *value);

//exec/parse
t_cmd	*parse_commands(t_lexer *tokens);

//exec/parser_cmd
t_cmd	*new_cmd(void);
void	add_arg(t_cmd *cmd, char *arg);
t_redir	*new_redir(int type, char *file);
void	add_redir(t_cmd *cmd, int type, char *file);
int	is_redir(int token);

//parse_utils
void	free_redir_list(t_redir *redirs);
void	free_cmd_list(t_cmd *cmd_list);
void	print_cmd_list(t_cmd *cmd_list);

//utils
int ft_strlen(char *str);
int is_whitespace(char c);
int skip_quotes(char *input, t_data *data);
char *ft_substr(char *str, int start, int len);
char	*remove_quotes(char *str);

//init_data
void init_struct(t_data *data);
int	process_input(t_lexer **list, char *input, t_data *data, t_env *env, int exit_status);

//check_string
char *delete_espace(char *input, t_data *data);
int check_pipe(t_lexer **list);
int check_first_token(t_lexer **list);
int parse(t_lexer **list);
int check_invalid_token(t_lexer **list);

//lexer
int what_type_token(char *str);
t_lexer	*new_node(int token, char *str);
void	add_element(char *input, t_lexer **list);
void add_to_back(t_lexer **list, char *str, int token);

//utils_2
char 	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalnum(char c);
int		get_nb_len(int n);
char	*ft_itoa(int n);

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

//dollar_handle
char *find_env_value(t_env *env, char *variable);
int	get_var_name_len(char *str, int i);
void	update_quotes_state(char c, bool *single, bool *doubl);
int	get_normal_var_size(char *input, int *i, t_env *env);
int	add_var_size(char *input, int *i, t_env *env);

//dollar_handle2
int	calculate_expanded_size(char *input, t_env *env, t_data *data);
void	copy_exit_status(char *result, int *j, int exit_status);
void	copy_var_value(char *result, int *j, char *var_value);
void	expand_normal_var(char *input, int *i, char *result, int *j, t_env *env);
void	expand_var_in_result(char *input, int *i, char *result, int *j, t_env *env, int exit_status);

//expander
void	process_char(char *input, int *i, char *result, int *j, t_expand *exp);
char	*expand_variables(char *input, t_env *env, t_data *data, int exit_status);
char	*process_expansion(char *input, t_env *env, t_data *data, int exit_status);

#endif