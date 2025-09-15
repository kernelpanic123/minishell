/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:30:09 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/14 19:12:45 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*new_node(int token, char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	new->token = token;
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}
//cd caca | echo "cacacacaca         "
static int	skip_token(char *input, int i)
{
	char	quote;

	if (input[i] == '"' || input[i] == '\'')
	{
		quote = input[i];
		i++;
		while (input[i] && input[i] != quote)
			i++;
		if (input[i] == quote)
			i++;
	}
	else
	{
		while (input[i] && !is_whitespace(input[i]))
			i++;
	}
	return (i);
}

void	add_element(char *input, t_lexer **list)
{
	int		i;
	int		start;
	char	*token;

	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		start = i;
		i = skip_token(input, i);
		token = ft_substr(input, start, i - start);
		add_to_back(list, token, what_type_token(token));
		free(token);
	}
}

int what_type_token(char *str)
{
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '>' && str[1] == '>')
		return (GREATGREAT);
	else if (str[0] == '<' && str[1] == '<')
		return (LESSLESS);
	else if (str[0] == '>')
		return (GREAT);
	else if (str[0] == '<')
		return (LESS);
	else
		return (WORD);
}
void add_to_back(t_lexer **list, char *str, int token)
{
	t_lexer *new; 
	t_lexer *current;
	
	new = new_node(token, str);

	if (*list == NULL)
	{
		*list = new;
	}
	else
	{
		current = *list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
}