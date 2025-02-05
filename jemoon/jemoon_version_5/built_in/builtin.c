/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 16:22:24 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin(t_data *meta)
{
	minishell_exit(meta);
	minishell_echo(&(*meta).exec_cmd);
	minishell_pwd(meta);
	minishell_env(meta);
	minishell_export(meta);
	minishell_unset(meta);
	minishell_cd(meta);
}
