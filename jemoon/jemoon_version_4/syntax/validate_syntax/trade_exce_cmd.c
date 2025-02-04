/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/03 17:24:52 by jemoon           ###   ########.fr       */
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
	if ((*exec_cmd))
	{
		*str = add_readline(exec_cmd, meta, *str);
		if (*exec_cmd == NULL)
		{
			meta->exec_cmd = NULL;
			return ;
		}
		exec_cmd_set_tpye(&(*exec_cmd));
		meta->exec_cmd = *exec_cmd;
	}
}
