/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_check_tpye.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:59:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 12:01:52 by jemoon           ###   ########.fr       */
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
