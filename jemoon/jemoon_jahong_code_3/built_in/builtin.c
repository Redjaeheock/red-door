/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 12:05:09 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

void	builtin(t_data *meta)
{
	if (ft_strcmp(meta->exec_cmd->str[0], "exit") == 0)
		minishell_exit(meta);
	if (ft_strcmp(meta->exec_cmd->str[0], "echo") == 0)
		minishell_echo(&(*meta).exec_cmd);
	if (ft_strcmp(meta->exec_cmd->str[0], "pwd") == 0)
		minishell_pwd(meta);
	if (ft_strcmp(meta->exec_cmd->str[0], "env") == 0)
		minishell_env(meta);
	if (ft_strcmp(meta->exec_cmd->str[0], "export") == 0)
		minishell_export(meta);
	if (ft_strcmp(meta->exec_cmd->str[0], "unset") == 0)
		minishell_unset(meta);
	if (ft_strcmp(meta->exec_cmd->str[0], "cd") == 0)
		minishell_cd(meta);
}
