/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 05:12:59 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/15 06:14:02 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_builtin_fork(t_cmd *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!handle_redirection(cmd->redirs))
			exit(1);
		shell->exit_status = execute_builtin(cmd->args, shell);
		exit(shell->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

static void	handle_exit_status(int status, t_minishell *shell)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			printf("Quit: %d\n", sig);
		else if (sig == SIGINT)
			printf("\n");
		shell->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

static void	execute_external_cmd(t_cmd *cmd, t_minishell *shell, char *path)
{
	pid_t	pid;
	int		status;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->redirs && !handle_redirection(cmd->redirs))
			exit(1);
		envp = env_to_array(shell->env);
		execve(path, cmd->args, envp);
		perror("execve");
		free_array(envp);
		free(path); 
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		handle_exit_status(status, shell);
		free(path);
	}
}

void	execute_simple_cmd(t_cmd *cmd, t_minishell *shell)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]) && !cmd->redirs)
	{
		shell->exit_status = execute_builtin(cmd->args, shell);
		return ;
	}
	if (is_builtin(cmd->args[0]) && cmd->redirs)
	{
		execute_builtin_fork(cmd, shell);
		return ;
	}
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		shell->exit_status = 127;
		return ;
	}
	execute_external_cmd(cmd, shell, path);
}
