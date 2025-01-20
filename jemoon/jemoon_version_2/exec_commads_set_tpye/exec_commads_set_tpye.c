/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/20 21:55:01 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd_set_tpye(t_cmd_list **exec_cmd)
{
	t_cmd_list	*tmp;

	tmp = *exec_cmd;
	while (*exec_cmd)
	{
		if ((*exec_cmd)->next != NULL && \
		(REDIRECTION <= (*exec_cmd)->type_re && \
		(*exec_cmd)->type_re <= HEREDOC))
			(*exec_cmd)->next->type_re = (*exec_cmd)->type_re;
		if ((*exec_cmd)->prev != NULL && \
		(AND <= (*exec_cmd)->type_pipe && \
		(*exec_cmd)->type_pipe <= PIPE))
			(*exec_cmd)->prev->type_pipe = (*exec_cmd)->type_pipe;
		*exec_cmd = (*exec_cmd)->next;
	}
	*exec_cmd = tmp;
	return ;
}
