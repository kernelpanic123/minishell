/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:41 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/01 19:24:02 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *delete_espace(char *input, t_data *data)
{
	int i;
	int j;
	char *dupe;

	i = 0;
	j = 0;
	dupe = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && !data->double_quotes)
			data->simple_quotes = !data->simple_quotes;
		if (input[i] == '"' && !data->simple_quotes)
			data->double_quotes = !data->double_quotes;
		if (is_whitespace(input[i]) && !(data->simple_quotes || data->double_quotes) && j > 0 && !is_whitespace(dupe[j-1]))
			dupe[j++] = input[i];
		else if (!is_whitespace(input[i]) || (data->simple_quotes || data->double_quotes))
			dupe[j++] = input[i];
		i++;
	}
	if (j > 0 && is_whitespace(dupe[j-1]))
		j--;
	dupe[j] = '\0';
	if (data->double_quotes || data->simple_quotes)
		return (NULL);
	return (dupe);
}
int check_token_validity(char *input)
{
	check_pipe(input)
}