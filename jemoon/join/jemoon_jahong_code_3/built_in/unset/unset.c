/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:01:25 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 12:06:44 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_unset(t_data *meta)
{
	int	unset_len;

	unset_len = char_arr_len(meta->exec_cmd->str);
	if (unset_len == 1)
	{
		printf("\n");
		return ;
	}
	else
		unset_export(meta, unset_len);
}
