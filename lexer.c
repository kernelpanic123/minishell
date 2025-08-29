/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:41 by abtouait          #+#    #+#             */
/*   Updated: 2025/08/28 14:36:25 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *input_loop(void)
{
	char *input;

	while (input != NULL)
	{
		input = readline("$minishell ");
		printf("%s\n", input);
	}
}

int main(void)
{
	while (1)
	{
		input_loop();
	}
}
