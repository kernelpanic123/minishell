/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:23:10 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/10 10:51:33 by abtouait         ###   ########.fr       */
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
	data->double_quotes = false;
	data->simple_quotes = false;
	return (i);
}

char *ft_substr(char *str, int start, int len)
{
    char *result;
    int i;
    
    if (start >= ft_strlen(str))
        return (ft_strdup(""));
    
    if (len > ft_strlen(str) - start)
        len = ft_strlen(str) - start;
    
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        result[i] = str[start + i];
        i++;
    }
    result[i] = '\0';
    return (result);
}
void print_list(t_lexer *list)
{
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
    }
}
