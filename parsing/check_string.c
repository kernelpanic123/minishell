/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:41 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/17 07:33:59 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_quotes(char c, t_data *data)
{
	if (c == '\'' && !data->double_quotes)
		data->simple_quotes = !data->simple_quotes;
	if (c == '"' && !data->simple_quotes)
		data->double_quotes = !data->double_quotes;
}

static int	should_add_space(char c, t_data *data, char *dupe, int j)
{
	if (!is_whitespace(c))
		return (0);
	if (data->simple_quotes || data->double_quotes)
		return (0);
	if (j == 0)
		return (0);
	if (is_whitespace(dupe[j - 1]))
		return (0);
	return (1);
}

static int	should_add_char(char c, t_data *data)
{
	if (!is_whitespace(c))
		return (1);
	if (data->simple_quotes || data->double_quotes)
		return (1);
	return (0);
}

//on enleve les espaces sauf dans les quotes
char	*delete_espace(char *input, t_data *data)
{
	int		i;
	int		j;
	char	*dupe;

	i = 0;
	j = 0;
	dupe = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[i] != '\0')
	{
		update_quotes(input[i], data);
		if (should_add_space(input[i], data, dupe, j))
			dupe[j++] = input[i];
		else if (should_add_char(input[i], data))
			dupe[j++] = input[i];
		i++;
	}
	if (j > 0 && is_whitespace(dupe[j - 1]))
		j--;
	dupe[j] = '\0';
	if (data->double_quotes || data->simple_quotes)
	{
		free(dupe);
		return (NULL);
	}
	return (dupe);
}
