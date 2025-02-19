/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:32:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/19 16:33:02 by jemoon           ###   ########.fr       */
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
	else if (export_len == 2)
	{
		cd_rest(meta, meta->exec_cmd->str[1]);
	}
	else
	{
		printf("-bash: cd: too many arguments\n");
	}
}
