/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/10 10:48:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_bash_syntax(t_list **tokens)
{
	int				count_cmd_line;
	t_cmd_list		*exec_commands;
	t_list			*tmp;

	tmp = *tokens;
	count_cmd_line = 0;
	exec_commands = NULL;
	while ((*tokens) != NULL)
	{
		printf("기점을 출력합니다 : %s \n", (*tokens)->token);
		get_exec_commads(&(*tokens), &(exec_commands), count_cmd_line);
		if (check_is_valid(&(*tokens), count_cmd_line) == 0)
		{
			printf_exec_commads(exec_commands);
			free_exec_linked_list(exec_commands);
			printf("틀렸습니다.\n");
			*tokens = tmp;
			return ;
		}
		count_cmd_line++;
	}
	printf_exec_commads(exec_commands);
	free_exec_linked_list(exec_commands);
	printf("맞았습니다.\n");
	*tokens = tmp;
	return ;
}
