/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_check_tpye_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:59:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 13:13:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	check_redi_in_b(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == IN_REDEC)
		return (1);
	return (0);
}

int	check_redi_out(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == OUT_REDEC)
		return (1);
	return (0);
}

int	check_redi_gr(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == GR_REDEC)
		return (1);
	return (0);
}

int	check_redi_heredoc(t_cmd_list *exec_cmd)
{
	if (exec_cmd->str == NULL && exec_cmd->type_pipe == HEREDOC)
		return (1);
	return (0);
}
