/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:23:10 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/04 21:31:13 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
int is_whitespace(char c)
{
	if (c >= 9 && c <= 13 || c == ' ')
		return (1);
	else
		return (0);
}
int skip_quotes(char *input, t_data *data)
{
	int i;

	i = 0;
	if (input[i] == '"' && !data->simple_quotes)
	{
		data->double_quotes = !data->double_quotes;
		i++;
		while (input[i] != '"' && input[i] != '\0')
			i++;
		i++;
	}
	else if (input[i] == '\'' && !data->double_quotes)
	{
		data->simple_quotes = !data->simple_quotes;
		i++;
		while (input[i] != '\'' && input[i] != '\0')
			i++;
		i++;
	}
	return (i);
}
