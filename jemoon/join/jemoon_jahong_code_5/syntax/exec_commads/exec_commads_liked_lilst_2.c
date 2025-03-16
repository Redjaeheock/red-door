/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_liked_lilst_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:56:46 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/08 15:47:39 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	t_tokentype_set(t_cmd_list *new_node, char **string_arry, \
		t_tokentype plag_pipe, t_tokentype plag_redi)
{
	new_node->str = string_arry;
	if (AND <= plag_pipe && plag_pipe <= PIPE)
		new_node->type_pipe = plag_pipe;
	if (REDIRECTION <= plag_redi && plag_redi <= HEREDOC)
		new_node->type_re = plag_redi;
}

void	exec_make_node(t_cmd_list **exec_cmd, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi)
{
	t_cmd_list	*new_node;

	new_node = create_exec_linked_list(string_array, plag_pipe, plag_redi);
	t_tokentype_set(new_node, string_array, plag_pipe, plag_redi);
	if (new_node == NULL)
		return (free_exec_linked_list(new_node));
	if (*exec_cmd == NULL)
		*exec_cmd = new_node;
	else
		add_back_exec_linked_list(exec_cmd, new_node);
}
