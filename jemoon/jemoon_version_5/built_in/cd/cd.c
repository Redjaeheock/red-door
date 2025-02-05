/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:32:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 20:23:08 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_cd(t_data *meta)
{
	int	export_len;
	int	i;

	i = 1;
	if (ft_strcmp(meta->exec_cmd->str[0], "cd") != 0)
		return ;
	export_len = char_arr_len(meta->exec_cmd->str);
	if (export_len == 1)
	{
		cd_home(meta);
	}
	else
	{
		while (i < export_len)
		{
			if (i == 1)
				cd_rest(meta, meta->exec_cmd->str[i]);
			i++;
		}
	}
}
