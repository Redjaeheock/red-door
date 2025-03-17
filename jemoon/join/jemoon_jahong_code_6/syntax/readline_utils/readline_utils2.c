/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:33:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/25 17:04:57 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

char	*add_readline_signal(t_data *meta, char *str)
{
	if (meta->stdin_flag == -1)
	{
		meta->heredoc = 0;
		reset_stdin_fileno(meta);
		return (str);
	}
	else
	{
		wranning_msg("abc");
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
