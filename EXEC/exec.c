/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 05:12:59 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/12 21:02:43 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		count;
	int		i;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strjoin(env->variable, env->value);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
//WEXITSTATUS macro pour avoir le code de retour
void	execute_simple_cmd(t_cmd *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]) && !cmd->redirs)
	{
		shell->exit_status = execute_builtin(cmd->args, shell);
		return ;
	}
	if (is_builtin(cmd->args[0]) && cmd->redirs)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!handle_redirection(cmd->redirs))
				exit(1);
			shell->exit_status = execute_builtin(cmd->args, shell);
			exit(shell->exit_status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		return ;
	}
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		shell->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (!handle_redirection(cmd->redirs))
			exit(1);
		envp = env_to_array(shell->env);
		execve(path, cmd->args, envp);
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		free(path);
	}
}
void	execute_commands(t_cmd *cmd, t_minishell *shell)
{
	if (cmd->next)
	{
		execute_pipeline(cmd, shell);
		return ;
	}
	execute_simple_cmd(cmd, shell);
}
