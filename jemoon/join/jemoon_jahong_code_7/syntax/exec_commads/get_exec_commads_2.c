/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 16:02:29 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	get_exec_cmd(t_list *tokens, t_cmd_list **exec_cmd)
{
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;
	int			cmd_size;
	int			check_redi;
	char		**string_array;

	check_redi = 0;
	*exec_cmd = NULL;
	while (tokens)
	{
		plag_pipe = NONE;
		plag_redi = NONE;
		cmd_size = get_double_string_array_size(tokens, &check_redi, \
		&plag_pipe, &plag_redi);
		if (cmd_size == 0)
		{
			tokens = tokens->next;
			continue ;
		}
		string_array = set_string_array_2(&tokens, cmd_size);
		if (string_array == NULL)
			return ;
		exec_make_node_2(exec_cmd, string_array, \
		plag_pipe, plag_redi);
	}
}
