/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/25 19:17:49 by abtouait         ###   ########.fr       */
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
int main(void)
{
	t_data data;
	t_lexer *list = NULL;

	init_struct(&data);
	char *input;
	while (1)
	{
		input = readline("$minishell: ");
		add_element(input, &list);
		process_input(&list, input, &data);
		print_list(list);
		free_list_token(&list);
		free(input);
	}
}
