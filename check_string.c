/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:41 by abtouait          #+#    #+#             */
/*   Updated: 2025/08/29 22:28:53 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *delete_espace(char *input, t_data *data)
{
	int i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"')
			data->double_quotes = 1;
		if (input[i] == "'")
			data->simple_quotes = 1;
		if ()
		
	}
}
cd    test    | "test   "

