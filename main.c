/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/30 01:38:05 by abtouait         ###   ########.fr       */
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
int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	shell;
	char		*input;
	char		*expanded;

	(void)argc;
	(void)argv;
	init_struct(&data);
	shell.env = NULL;
	shell.exit_status = 0;
	add_env_list(&shell.env, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		expanded = process_expansion(input, shell.env, &data, shell.exit_status);
		printf("%s\n", expanded);
		free(expanded);
		free(input);
	}
	free_list_env(&shell.env);
	return (0);
}
