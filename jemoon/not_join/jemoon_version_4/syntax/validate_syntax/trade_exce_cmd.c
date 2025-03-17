/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 16:37:44 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	trade_exec_cmd(t_data *meta, t_cmd_list **exec_cmd, \
t_list **tokens, char **str)
{
	tpye_init(tokens);
	printf_tokens(*tokens);
	validate_bash_syntax(exec_cmd, tokens);
	meta->exec_cmd = *exec_cmd;
	if ((meta->exec_cmd))
	{
		*str = add_readline(&meta->exec_cmd, meta, *str);
		if (*str == NULL)
		{
			free_exec_linked_list(meta->exec_cmd);
			meta->exec_cmd = NULL;
			return ;
		}
		exec_cmd_set_tpye(&meta->exec_cmd);
		//meta->exec_cmd = *exec_cmd;
	}
}
