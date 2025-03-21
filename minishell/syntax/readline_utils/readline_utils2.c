/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:33:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/21 20:52:20 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

char	*add_readline_signal(t_data *meta, char *str)
{
	if (meta->stdin_flag == -1)
	{
		g_ws = 130;
		meta->heredoc = 0;
		dup2(meta->oldstdin, STDIN_FILENO);
		close(meta->oldstdin);
		return (str);
	}
	else
	{
		wranning_msg("abc"); // 수정 요
		free(str);
		str = NULL;
		return (NULL);
	}
}

void	add_readline_trade_exec_cmd(t_data *meta, t_list *tmp, char *str)
{
	tpye_init(&meta->tokens);
	set_here_doc(meta, tmp);
	meta->heredoc = 0;
}
