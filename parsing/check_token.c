/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:10:14 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 20:11:47 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_token(t_lexer **list)
{
	t_lexer	*tmp;

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

int	check_last_token(t_lexer **list)
{
	t_lexer	*tmp;

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

int	check_invalid_token(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp->next)
	{
		if (tmp->token != WORD)
		{
			if (tmp->next->token != WORD)
			{
				printf("bash: syntax error near unexpected token %s\n",
					tmp->next->str);
				free_list_token(list);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	parse(t_lexer **list)
{
	if (check_first_token(list) == 0)
		return (0);
	if (check_last_token(list) == 0)
		return (0);
	if (check_invalid_token(list) == 0)
		return (0);
	return (1);
}
