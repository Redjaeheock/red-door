/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 15:10:00 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	validate_bash_syntax(t_cmd_list **exec_cmd, t_list **tokens)
{
	int		count_cmd_line;
	t_list	*tmp;

	tmp = *tokens;
	count_cmd_line = 0;
	*exec_cmd = NULL;
	while (*tokens != NULL)
	{
		if (check_is_valid(tokens, count_cmd_line) == 0)
		{
			error_syntax((*tokens)->token);
			*tokens = tmp;
			return (-1);
		}
		count_cmd_line++;
	}
	*tokens = tmp;
	get_exec_cmd_2(*tokens, exec_cmd);
	return (0);
}
