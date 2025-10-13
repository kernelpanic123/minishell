/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:16:12 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 16:20:47 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//creer une new_cmd et fait bifurquer quand il y a un pipe vers la cmd 2
static t_lexer	*handle_pipe(t_cmd **current_cmd,
	t_lexer *tokens, t_cmd *cmd_list)
{
	(*current_cmd)->next = new_cmd();
	if (!(*current_cmd)->next)
	{
		free_cmd_list(cmd_list);
		return (NULL);
	}
	*current_cmd = (*current_cmd)->next;
	return (tokens->next);
}
//saute 2 token pour ajouter la redirection
static t_lexer	*handle_redir(t_cmd *current_cmd, t_lexer *tokens, t_cmd *cmd_list)
{
	if (!tokens->next || tokens->next->token != WORD)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		free_cmd_list(cmd_list);
		return (NULL);
	}
	add_redir(current_cmd, tokens->token, tokens->next->str);
	return (tokens->next->next);
}

static t_lexer	*process_token(t_cmd **current_cmd, t_lexer *tokens, t_cmd *cmd_list)
{
	if (tokens->token == PIPE)
		return (handle_pipe(current_cmd, tokens, cmd_list));
	else if (is_redir(tokens->token))
		return (handle_redir(*current_cmd, tokens, cmd_list));
	else if (tokens->token == WORD)
	{
		add_arg(*current_cmd, tokens->str);
		return (tokens->next);
	}
	else
	{
		printf("bash: syntax error\n");
		free_cmd_list(cmd_list);
		return (NULL);
	}
}

t_cmd	*parse_commands(t_lexer *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	cmd_list = new_cmd();
	if (!cmd_list)
		return (NULL);
	current_cmd = cmd_list;
	while (tokens)
	{
		tokens = process_token(&current_cmd, tokens, cmd_list);
		if (!tokens)
			break ;
	}
	return (cmd_list);
}