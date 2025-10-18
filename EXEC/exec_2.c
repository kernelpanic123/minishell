/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:35:44 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/18 09:15:19 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands(t_cmd *cmd, t_minishell *shell, t_lexer *tokens)
{
	if (cmd->next)
	{
		execute_pipeline(cmd, shell, tokens);
		return ;
	}
	execute_simple_cmd(cmd, shell);
}

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
