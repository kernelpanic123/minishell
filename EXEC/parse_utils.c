/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:33:39 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/18 10:46:09 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir_list(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->file);
		if (redirs->heredoc_content)
			free(redirs->heredoc_content);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				free(cmd_list->args[i]);
				i++;
			}
			free(cmd_list->args);
		}
		free_redir_list(cmd_list->redirs);
		free(cmd_list);
		cmd_list = tmp;
	}
}
