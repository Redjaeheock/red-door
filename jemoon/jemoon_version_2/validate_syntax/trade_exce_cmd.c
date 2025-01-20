/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/20 15:49:10 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trade_exce_cmd(t_data *meta, t_cmd_list **exec_commdas, \
t_list **tokens, char **str)
{
	tpye_init(tokens);
	printf_tokens(*tokens);
	validate_bash_syntax(exec_commdas, tokens);
	free_linked_list(*tokens);
	if (*exec_commdas != NULL)
	{
		*str = add_readline(exec_commdas, meta, *str);
		meta->exec_commads = *exec_commdas;
	}
}
