/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/10 13:35:35 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_export(t_data *meta, t_cmd_list *exec_cmd)
{
	int		export_len;

	export_len = sndry_arr_len((void **)exec_cmd->str);
	g_ws = 0;
	if (export_len == 1)
		frist_export(meta);
	else
		rest_export(meta, exec_cmd, export_len);
}
