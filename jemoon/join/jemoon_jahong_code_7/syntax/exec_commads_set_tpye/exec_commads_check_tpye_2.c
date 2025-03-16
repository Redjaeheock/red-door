/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_check_tpye_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:59:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 13:12:23 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

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

int	check_and_or_branch(t_cmd_list	*exec_cmd)
{
	if (check_and_branch(exec_cmd))
		return (1);
	if (check_or_branch(exec_cmd))
		return (1);
	return (0);
}

int	is_cmd_branch(t_cmd_list	*exec_cmd)
{
	if (check_pipe_branch(exec_cmd))
		return (1);
	if (check_and_branch(exec_cmd))
		return (1);
	if (check_or_branch(exec_cmd))
		return (1);
	return (0);
}
