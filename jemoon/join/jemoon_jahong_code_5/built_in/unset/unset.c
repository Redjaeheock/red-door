/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:01:25 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/10 13:57:15 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_unset(t_data *meta, t_cmd_list *exec_cmd)
{
	int	unset_len;

	g_ws = 0;
	unset_len = sndry_arr_len((void **)exec_cmd->str);
	if (unset_len == 1)
	{
		printf("\n");
		return ;
	}
	else
		unset_export(meta, exec_cmd, unset_len);
}
