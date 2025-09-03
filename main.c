/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/03 00:31:26 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_data data;

	init_struct(&data);
	char *input;
	while (1)
	{
		input = readline("$minishell: ");
		printf("%d\n", skip_quotes(input, &data));
	}
}