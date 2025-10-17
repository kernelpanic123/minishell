/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:29:40 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/17 08:53:49 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_heredoc(char *delimiter)
{
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("error heredoc %s\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		tmp = content;
		content = strjoin_heredoc(content, line);
		free(tmp);
		free(line);
	}
	return (content);
}

int	handle_heredoc(char *str)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	write(pipe_fd[1], str, ft_strlen(str));
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (1);
}

void	process_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == LESSLESS)
		{
			redir->heredoc_content = read_heredoc(redir->file);
		}
		redir = redir->next;
	}
}
