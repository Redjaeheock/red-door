/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/26 11:45:47 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	trade_exec_cmd(t_data *meta, t_cmd_list **exec_cmd, \
t_list **tokens, char **str)
{
	tpye_init(tokens);
	set_here_doc(meta);
	if (validate_bash_syntax(exec_cmd, tokens) == -1)
	{
		meta->exec_cmd = NULL;
		return (0);
	}
	meta->tokens = free_t_list(meta->tokens);
	meta->exec_cmd = *exec_cmd;
	if ((meta->exec_cmd))
	{
		*str = add_readline(&meta->exec_cmd, meta, *str);
		if (*str == NULL)
		{
			free_exec_linked_list(meta->exec_cmd);
			meta->exec_cmd = NULL;
			return (-1);
		}
		if (meta->exec_cmd == NULL)
			return (0);
		normalize_cmd(meta);
		exec_cmd_set_tpye(&meta->exec_cmd);
		operator_str_free(meta);
	}
	return (0);
}
