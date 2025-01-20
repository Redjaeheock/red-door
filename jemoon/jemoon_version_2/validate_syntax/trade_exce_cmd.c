/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/20 22:08:43 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trade_exec_cmd(t_data *meta, t_cmd_list **exec_cmd, \
t_list **tokens, char **str)
{
	tpye_init(tokens);
	validate_bash_syntax(exec_cmd, tokens);
	free_linked_list(*tokens);
	if ((*exec_cmd))
	{
		*str = add_readline(exec_cmd, meta, *str);
		if (*exec_cmd == NULL)
		{
			meta->exec_cmd = NULL;
			return ;
		}
		exec_cmd_set_tpye(exec_cmd);
		meta->exec_cmd = *exec_cmd;
	}
}
