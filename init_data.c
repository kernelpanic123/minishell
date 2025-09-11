/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:27:48 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/11 06:01:40 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_data *data)
{
	data->double_quotes = false;
	data->simple_quotes = false;
}

int	process_input(t_lexer **list, char *input, t_data *data)
{
	char	*str;

	str = delete_espace(input, data);
	add_element(str, list);
	if (parse(list) == 0)
		return (0);
	return (1);
}
