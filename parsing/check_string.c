/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:00:41 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/01 16:29:52 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int check_first_token(t_lexer **list)
{
	t_lexer *tmp;

	tmp = *list;
	if (tmp->token == PIPE)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		free_list_token(list);
		return (0);
	}
	if (!tmp->next && (tmp->token != WORD && tmp->token != PIPE))
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		free_list_token(list);
		return (0);
	}
	return (1);
}
int check_last_token(t_lexer **list)
{
	t_lexer *tmp;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->token == PIPE)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		free_list_token(list);
		return (0);
	}
	if (!tmp->next && (tmp->token != WORD && tmp->token != PIPE))
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		free_list_token(list);
		return (0);
	}
	return (1);
}
int check_invalid_token(t_lexer **list)
{
	t_lexer *tmp;
	
	tmp = *list;
	while (tmp->next)
	{
		if (tmp->token != WORD)
		{
			if (tmp->next->token != WORD)
			{
				printf("bash: syntax error near unexpected token %s\n", tmp->next->str);
				free_list_token(list);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int parse(t_lexer **list)
{
	if (check_first_token(list) == 0)
		return (0);
	if (check_last_token(list) == 0)
		return (0);
	if (check_invalid_token(list) == 0)
		return (0);
	return (1);
}