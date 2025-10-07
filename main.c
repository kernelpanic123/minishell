/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/07 23:27:03 by abtouait         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/07 20:00:00 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
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
}
