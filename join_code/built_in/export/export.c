/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/24 13:35:21 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_export(t_data *meta, t_cmd_list *exec_cmd)
{
	int		export_len;

	export_len = char_arr_len(exec_cmd->str);
	if (export_len == 1)
		frist_export(meta);
	else
		rest_export(meta, export_len);
}
