/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/03 17:54:36 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	check_prev(t_cmd_list	*exec_cmd)
{
	if (exec_cmd->prev != NULL)
		return (1);
	return (0);
}

int	check_next(t_cmd_list	*exec_cmd)
{
	if (exec_cmd->next != NULL)
		return (1);
	return (0);
}

int	check_redi(t_cmd_list	*exec_cmd)
{
	if (REDIRECTION <= exec_cmd->type_re && exec_cmd->type_re <= HEREDOC)
		return (1);
	return (0);
}

int	check_pipe(t_cmd_list	*exec_cmd)
{
	if (AND <= exec_cmd->type_pipe && exec_cmd->type_pipe <= PIPE)
		return (1);
	return (0);
}

void	exec_cmd_set_tpye(t_cmd_list **exec_cmd)
{
	t_cmd_list	*tmp;

	tmp = *exec_cmd;
	while (*exec_cmd)
	{
		//if (check_pipe(*exec_cmd) || check_redi(*exec_cmd))
		//{
		//	(*exec_cmd) = (*exec_cmd)->next;
		//	continue ;
		//}9
		if (check_next(*exec_cmd) && check_pipe((*exec_cmd)->next))
		{
			(*exec_cmd)->type_pipe = (*exec_cmd)->next->type_pipe;
			if (check_next((*exec_cmd)->next) && check_redi((*exec_cmd)->next->next))
				(*exec_cmd)->type_re = (*exec_cmd)->next->next->type_re;
		}
		else if (check_next(*exec_cmd) && check_redi((*exec_cmd)->next))
			(*exec_cmd)->type_re = (*exec_cmd)->next->type_re;
		*exec_cmd = (*exec_cmd)->next;
	}
	*exec_cmd = tmp;
}

/*
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
*/
