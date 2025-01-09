/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:58:04 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/09 17:17:25 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_exec_commads(t_cmd_list *exec_commands)
{
	int	i;

	while (exec_commands)
	{
		i = 0;
		while (exec_commands->str[i] != NULL)
		{
			printf("%s ", exec_commands->str[i]);
			i++;
		}
		printf("\n");
		exec_commands = exec_commands->next;
	}
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
	else
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
