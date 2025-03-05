/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/28 15:18:27 by jemoon           ###   ########.fr       */
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

void	exec_cmd_set_tpye(t_data *meta)
{
	t_cmd_list	*tmp;

	tmp = meta->exec_cmd;
	while (tmp)
	{
		if (check_pipe(tmp))
		{
			if (check_prev(tmp))
				tmp->prev->type_pipe = tmp->type_pipe;
			tmp->token_cmd = NONE;
		}
		else if (check_redi(tmp))
		{
			tmp->token_cmd = NONE;
			if (check_next(tmp))
				tmp->next->token_cmd = NONE;
		}
		tmp = tmp->next;
	}
}
