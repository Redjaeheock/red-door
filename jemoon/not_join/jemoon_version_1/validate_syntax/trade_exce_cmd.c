/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trade_exce_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:58:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/20 20:25:12 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trade_exce_cmd(t_cmd_list **exec_commdas, t_list **tokens, char **str)
{
	tpye_init(tokens);
	printf_tokens(*tokens);
	validate_bash_syntax(exec_commdas, tokens);
	free_linked_list(*tokens);
	if (*exec_commdas != NULL)
	{
		*str = add_readline(exec_commdas, *str);
		if (*exec_commdas == NULL)
			return ;
		printf_exec_commads(*exec_commdas);
		free_exec_linked_list(*exec_commdas);
	}
}
