/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_check_tpye_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:59:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/19 17:35:35 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	check_redi_in(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == IN_REDEC)
		return (1);
	return (0);
}

int	check_redi_out(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_re == OUT_REDEC)
		return (1);
	return (0);
}

int	check_redi_gr(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_re == GR_REDEC)
		return (1);
	return (0);
}

int	check_redi_heredoc(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_re == HEREDOC)
		return (1);
	return (0);
}

int	check_redi_with_pipe(t_cmd_list *exec_cmd)
{
	if (exec_cmd->type_re != NONE && exec_cmd->type_pipe == PIPE)
		return (1);
	return (0);
}
