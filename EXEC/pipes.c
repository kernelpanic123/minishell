/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 06:50:02 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/12 22:21:25 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//pipe child parent etc
//https://www.youtube.com/watch?v=NlFvGZoAgTs
//fork function 
//https://youtu.be/cex9XrZCU14?si=7SMM3HUvdRXVkpHq
void	execute_cmd_in_pipe(t_cmd *cmd, t_minishell *shell)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->args[0]))
	{
		shell->exit_status = execute_builtin(cmd->args, shell);
		exit(shell->exit_status);
	}
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	
	envp = env_to_array(shell->env);
	execve(path, cmd->args, envp);
	perror("execve");
	exit(127);
}

void	setup_pipe_redirs(int prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (cmd->redirs)
		handle_redirection(cmd->redirs);
}
static void	handle_parent_fds(int *prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	execute_pipeline(t_cmd *cmd_list, t_minishell *shell)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			setup_pipe_redirs(prev_fd, pipe_fd, cmd_list);
			execute_cmd_in_pipe(cmd_list, shell);
		}
		handle_parent_fds(&prev_fd, pipe_fd, cmd_list);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) > 0)
		;
}
