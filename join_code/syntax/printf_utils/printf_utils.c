/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:58:04 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/28 11:35:58 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	printf_exec_commads(t_cmd_list *exec_commands)
{
	int	i;

	while (exec_commands)
	{
		i = 0;
		if (exec_commands->str != NULL)
		{
			while (exec_commands->str[i] != NULL)
			{
				printf("[%s] ", exec_commands->str[i]);
				i++;
			}
		}
		else
			printf("[NULL] ");
		printf(": [%s] [%s] [%s] ", token_type_to_str_1(exec_commands->type_cmd), token_type_to_str_1(exec_commands->type_pipe), \
		token_type_to_str_1(exec_commands->type_re));
		if (exec_commands->key != NULL)
			printf("key [%s] \n", exec_commands->key);
		else
			printf("\n");
		exec_commands = exec_commands->next;
	}
	printf("성공!\n");
}

const char	*token_type_to_str_1(t_tokentype type)
{
	if (type == NONE)
		return ("NONE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIRECTION)
		return ("REDIRECTION");
	else if (type == IN_REDEC)
		return ("IN_REDEC");
	else if (type == OUT_REDEC)
		return ("OUT_REDEC");
	else if (type == GR_REDEC)
		return ("GR_REDEC");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == CMD)
		return ("CMD");
	else if (type == OPTION)
		return ("OPTION");
	else if (type == ARG)
		return ("ARG");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	return ("UNKNOWN");
}

void	printf_tokens(t_list *tokens)
{
	while (tokens != NULL)
	{
		printf("%s [%s]\n", tokens->token, token_type_to_str_1(tokens->type));
		tokens = tokens->next;
	}
}
