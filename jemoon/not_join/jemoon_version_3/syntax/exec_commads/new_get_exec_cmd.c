/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_exec_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:42:25 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/22 19:46:13 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	new_get_exec_cmd(t_tmp *tokens, t_cmd_list **exec_cmd)
{
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;
	int			cmd_size;
	int			check_redi;
	char		**string_array;

	check_redi = 0;
	if (tokens == NULL)
		return ;
	while (tokens)
	{
		plag_pipe = NONE;
		plag_redi = NONE;
		cmd_size = get_double_string_array_size(tokens, &check_redi, \
		&plag_pipe, &plag_redi);
		if (cmd_size == 0)
			return ;
		string_array = set_string_array_2(&tokens, cmd_size);
		if (string_array == NULL)
			return ;
		exec_make_node_2(&(*exec_cmd), string_array, \
		plag_pipe, plag_redi);
	}	
}
