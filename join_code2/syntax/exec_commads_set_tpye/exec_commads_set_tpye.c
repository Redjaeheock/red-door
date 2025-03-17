/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_set_tpye.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:41:02 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/15 14:01:36 by jahong           ###   ########.fr       */
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
int	check_pipe_branch(t_cmd_list	*exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_re == NONE) 
	{
		if (exec_cmd->type_pipe == PIPE)
			return (1);
	}
	return (0);
}
int	check_and_branch(t_cmd_list	*exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == AND)
		return (1);
	return (0);
}
int	check_or_branch(t_cmd_list	*exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == OR)
		return (1);
	return (0);
}

int	is_cmd_branch(t_cmd_list	*exec_cmd)
{
	if (check_pipe_branch(exec_cmd))
		return (1);
	if (check_and_branch(exec_cmd))
		return (1);
	if	(check_or_branch(exec_cmd))
		return (1);
	return (0);
}

void	exec_cmd_set_type(t_data *meta)
{
	t_cmd_list	*tmp;

	tmp = meta->exec_cmd;
	while (tmp)
	{
		//printf_exec_commads(meta->exec_cmd);
		if (is_cmd_branch(tmp))
        {
            if (tmp->type_pipe == PIPE && tmp->str == NULL)
            {
                if (check_prev(tmp))
                    tmp->prev->type_pipe = tmp->type_pipe;
                if (check_next(tmp))
                    tmp->next->type_pipe = tmp->type_pipe;
            }
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
