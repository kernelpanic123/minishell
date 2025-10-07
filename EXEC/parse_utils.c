/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:33:39 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/07 23:30:30 by abtouait         ###   ########.fr       */
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

static void	print_redir_type(int type)
{
	if (type == GREAT)
		printf("  > ");
	else if (type == GREATGREAT)
		printf("  >> ");
	else if (type == LESS)
		printf("  < ");
	else if (type == LESSLESS)
		printf("  << ");
}

static void	print_redirections(t_redir *redir)
{
	if (!redir)
		return ;
	printf("Redirect:\n");
	while (redir)
	{
		print_redir_type(redir->type);
		printf("%s\n", redir->file);
		redir = redir->next;
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	int	cmd_num;
	int	i;

	cmd_num = 1;
	while (cmd_list)
	{
		printf("\n cmd %d \n", cmd_num);
		printf("Args: ");
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				printf("%s ", cmd_list->args[i]);
				i++;
			}
		}
		printf("\n");
		print_redirections(cmd_list->redirs);
		cmd_list = cmd_list->next;
		cmd_num++;
	}
}