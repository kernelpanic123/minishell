/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 21:22:47 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/12 21:36:11 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//change la source du stdin en gros
int	handle_less(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
//creer le fichier ou efface tout sinon thx les macros ^^
int	handle_great(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
//idem mais ajoute a la fin
int	handle_greatgreat(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_redirection(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == LESS)
		{
			if (!handle_less(redirs->file))
				return (0);
		}
		else if (redirs->type == GREAT)
		{
			if (!handle_great(redirs->file))
				return (0);
		}
		else if (redirs->type == GREATGREAT)
		{
			if (!handle_greatgreat(redirs->file))
				return (0);
		}
		else if (redirs->type == LESSLESS)
		{
			if (!handle_heredoc(redirs->heredoc_content))
				return (0);
		}
		redirs = redirs->next;
	}
	return (1);
}
