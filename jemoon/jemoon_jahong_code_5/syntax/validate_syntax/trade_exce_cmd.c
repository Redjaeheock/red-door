/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/28 16:06:16 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	trade_exec_cmd(t_data *meta, t_cmd_list **exec_cmd, \
t_list **tokens, char **str)
{
	tpye_init(tokens);
	set_here_doc(meta, *tokens);
	meta->heredoc = 0;
	if (tokens == NULL)
		return (0);
	if (validate_bash_syntax(tokens) == -1)
		return (0);
	*str = add_readline(meta, *str);
	if (tokens == NULL)
		return (0);
	if (*str == NULL)
		return (-1);
	get_exec_cmd_2(*tokens, exec_cmd);
	meta->tokens = free_t_list(meta->tokens);
	if (exec_cmd == NULL)
		return (0);
	meta->exec_cmd = *exec_cmd;
	normalize_cmd(meta);
	exec_cmd_set_tpye(meta);
	operator_str_free(meta);
	return (0);
}
