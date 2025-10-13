/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:58:58 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:33:47 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			new_args[i] = cmd->args[i];
			i++;
		}
		free(cmd->args);
	}
	new_args[i] = remove_quotes(arg);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
}

t_redir	*new_redir(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = remove_quotes(file);
	redir->heredoc_content = NULL;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_cmd *cmd, int type, char *file)
{
	t_redir	*new;
	t_redir	*current;

	new = new_redir(type, file);
	if (!new)
		return ;
	if (!cmd->redirs)
	{
		cmd->redirs = new;
	}
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	is_redir(int token)
{
	return (token == GREAT || token == LESS
		|| token == GREATGREAT || token == LESSLESS);
}
