/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:51:16 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/02 05:12:58 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_data data;

	init_struct(&data);
	char *input;
	input = readline("$minishell: ");
	printf("%d", skip_quotes(input, &data));
}