/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 18:48:34 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

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
