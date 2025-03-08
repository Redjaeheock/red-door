/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/08 15:03:40 by jemoon           ###   ########.fr       */
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
	if (exec_cmd->type_pipe == PIPE)
	{
		if (exec_cmd->str == NULL && exec_cmd->type_re == NONE)
			return (1);
	}
	return (0);
}

void	exec_cmd_set_type(t_data *meta)
{
	t_cmd_list	*tmp;

	tmp = meta->exec_cmd;
	while (tmp)
	{
		if (check_pipe(tmp))
		{
			if (check_prev(tmp))
				tmp->prev->type_pipe = tmp->type_pipe;
			if (check_next(tmp))
				tmp->next->type_pipe = tmp->type_pipe;
			tmp->type_cmd = NONE;
		}
		else if (check_redi(tmp))
		{
			tmp->type_cmd = NONE;
			if (check_next(tmp))
				tmp->next->type_cmd = NONE;
		}
		tmp = tmp->next;
	}
}
