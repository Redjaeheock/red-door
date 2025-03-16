/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 17:23:38 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_export(t_data *meta)
{
	int		export_len;

	export_len = char_arr_len(meta->exec_cmd->str);
	if (ft_strcmp(meta->exec_cmd->str[0], "export") != 0)
		return ;
	if (export_len == 1)
		frist_export(meta);
	else
		rest_export(meta, export_len);
}
