/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/14 19:31:53 by abtouait         ###   ########.fr       */
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
int main(int argc, char **argv, char **envp)
{
	t_env *env;
	int i = 0;
	(void)argc;
	(void)argv;
	// for ( int i = 0; envp[i]; i++)
	// 	printf("%s\n", envp[i]);
	env = copy_env(envp);
	while (env)
	{
		printf("%s=%s\n", env->variable, env->value);
		env = env->next;
	}
}
