/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:30:09 by abtouait          #+#    #+#             */
/*   Updated: 2025/09/05 04:39:12 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*new_node(int token, char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	new->token = token;
	new->str = str; //oublie pas strdup la chaine gros neuille
	new->next = NULL;
	return (new);
}
void add_element(char *input, t_lexer *list)
{
	int i;
	char *tmp;

	i = 0;
	while (input[i])
	{
		while (input[i] != ' ')
			tmp[i] = input[i];
		list->str = tmp;
		list->token = //fonction what_type_token() pour pas te casser la tete
		i++;
	}
}
int what_type_token(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (PIPE);
		else if (str[i] && str[i + 1] == '>>')
			return (GREATGREAT);
		else if (str[i] && str[i + 1] == '<<')
			return (LESSLESS);
		else if (str[i] == '>')
			return (GREAT);
		else if (str[i] == '<')
			return (LESS);
		else
			return (WORD);
		i++;
	}
}