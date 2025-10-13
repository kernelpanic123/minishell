/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:54:39 by abtouait          #+#    #+#             */
/*   Updated: 2025/10/13 18:24:16 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&s[i]);
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	count_paths(char *path_env)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			count++;
		i++;
	}
	return (count);
}

char	*ft_strjoin(char *variable, char *value)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(variable) + ft_strlen(value) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (variable[i])
	{
		result[i] = variable[i];
		i++;
	}
	result[i++] = '=';
	j = 0;
	while (value[j])
	{
		result[i++] = value[j++];
	}
	result[i] = '\0';
	return (result);
}
