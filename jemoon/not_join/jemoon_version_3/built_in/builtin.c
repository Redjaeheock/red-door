/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/21 22:38:21 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	builtin(t_data *meta)
{
	minishell_exit(&(*meta).exec_cmd);
	minishell_echo(&(*meta).exec_cmd);
	minishell_pwd(meta);
	minishell_env(meta);
	minishell_export(meta);
}
