/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abtouait <abtouait@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:01:42 by abtouait          #+#    #+#             */
/*   Updated: 2025/08/30 19:13:13 by abtouait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>


#define WORD	1    // word
#define PIPE	2    // |
#define TRUNC	3    // >
#define INPUT	4    // <
#define APPEND	5    // >>
#define HEREDOC	6    // <<

typedef struct s_lexer// ls -la | >> a > b
{
	char	*str; //ls
	int		token;// 1
	struct s_lexer	*next; str   : ls ->  str   : -la  -> str  : | -> str  : >>. -> str : a -> >
}	t_lexer;			   token : 1  ->  token : 1    -> token: 2 ->token : 5. ->  token  

typedef struct s_data
{
	bool simple_quotes;
	bool double_quotes;
}	t_data;

//utils
int ft_strlen(char *str);

//init_data
void init_struct(t_data *data);

//check_string
char *delete_espace(char *input, t_data *data);

#endif