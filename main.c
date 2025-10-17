/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/17 09:10:46 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int main(void)
{
	t_data data;
	t_lexer *list = NULL;

	init_struct(&data);
	char *input;
	while (1)
	{
		input = readline("$minishell: ");
		process_input(&list, input, &data);
		print_list(list);
		free_list_token(&list);
		free(input);
	}
}*/
/*int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	shell;
	char		*input;
	t_lexer		*list;

	(void)argc;
	(void)argv;
	list = NULL;
	init_struct(&data);
	shell.env = NULL;
	shell.exit_status = 0;
	add_env_list(&shell.env, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (process_input(&list, input, &data, shell.env, shell.exit_status))
			print_list(list);
		free_list_token(&list);
		free(input);
	}
	free_list_env(&shell.env);
	return (0);
}*/

/*int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	shell;
	char		*input;
	t_lexer		*tokens;
	t_cmd		*cmd_list;

	(void)argc;
	(void)argv;
	tokens = NULL;
	init_struct(&data);
	shell.env = NULL;
	shell.exit_status = 0;
	add_env_list(&shell.env, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (process_input(&tokens, input, &data, shell.env, shell.exit_status))
		{
			cmd_list = parse_commands(tokens);
			if (cmd_list)
			{
				print_cmd_list(cmd_list);
				free_cmd_list(cmd_list);
			}
		}
		free_list_token(&tokens);
		free(input);
	}
	free_list_env(&shell.env);
	return (0);
}*/

/*int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	shell;
	char		*input;
	t_lexer		*tokens;
	t_cmd		*cmd_list;

	(void)argc;
	(void)argv;
	tokens = NULL;
	init_struct(&data);
	shell.env = NULL;
	shell.exit_status = 0;
	add_env_list(&shell.env, envp);
	setup_signals_interactive();
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			shell.exit_status = 130;
			g_signal_received = 0;
		}
		if (process_input(&tokens, input, &data, shell.env, shell.exit_status))
		{
			cmd_list = parse_commands(tokens);
			if (cmd_list)
			{
				t_cmd *tmp = cmd_list;
				while (tmp)
				{
					process_heredocs(tmp);
					tmp = tmp->next;
				}
				setup_signals_execution();
				execute_commands(cmd_list, &shell);
				setup_signals_interactive();
				free_cmd_list(cmd_list);
			}
		}
		free_list_token(&tokens);
		free(input);
	}
	free_list_env(&shell.env);
	return (0);
}*/
int	g_signal_received = 0;

static void	handle_heredocs(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		process_heredocs(tmp);
		tmp = tmp->next;
	}
}

static void	process_command(t_lexer *tokens, t_minishell *shell)
{
	t_cmd	*cmd_list;

	cmd_list = parse_commands(tokens);
	if (cmd_list != NULL)
	{
		handle_heredocs(cmd_list);
		setup_signals_execution();
		execute_commands(cmd_list, shell);
		setup_signals_interactive();
		free_cmd_list(cmd_list);
	}
}

static void	handle_input(char *input, t_minishell *shell, t_data *data)
{
	t_lexer	*tokens;

	tokens = NULL;
	if (g_signal_received == SIGINT)
	{
		shell->exit_status = 130;
		g_signal_received = 0;
	}
	if (input[0] != '\0')
		add_history(input);
	if (process_input(&tokens, input, data, shell))
		process_command(tokens, shell);
	free_list_token(&tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	shell;
	char		*input;

	(void)argc;
	(void)argv;
	init_struct(&data);
	shell.env = NULL;
	shell.exit_status = 0;
	add_env_list(&shell.env, envp);
	setup_signals_interactive();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_input(input, &shell, &data);
		free(input);
	}
	free_list_env(&shell.env);
	return (0);
}
