/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 01:14:31 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:31:34 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_one_path(char *path_env, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	while (path_env[*i] && path_env[*i] != ':')
	{
		len++;
		(*i)++;
	}
	if (path_env[*i] == ':')
		(*i)++;
	return (ft_substr(path_env, start, len));
}

char	**split_path(char *path_env)
{
	char	**paths;
	int		i;
	int		j;

	if (!path_env)
		return (NULL);
	paths = malloc(sizeof(char *) * (count_paths(path_env) + 1));
	if (!paths)
		return (NULL);
	i = 0;
	j = 0;
	while (path_env[i])
	{
		paths[j] = extract_one_path(path_env, &i);
		j++;
	}
	paths[j] = NULL;
	return (paths);
}

char	*join_path(char *dir, char *cmd)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		result[i] = dir[i];
		i++;
	}
	result[i++] = '/';
	j = 0;
	while (cmd[j])
	{
		result[i++] = cmd[j++];
	}
	result[i] = '\0';
	return (result);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (file_exists(full_path))
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	paths = split_path(path_env);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
