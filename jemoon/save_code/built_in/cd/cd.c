/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:32:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 15:29:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_cd(t_data *meta, t_cmd_list *exec_cmd)
{
	int	export_len;
	int	i;

	i = 1;
	export_len = sndry_arr_len((void **)exec_cmd->str);
	if (export_len == 1)
	{
		cd_execute(meta, NULL);
	}
	else if (export_len == 2)
	{
		cd_execute(meta, exec_cmd->str[1]);
	}
	else
	{
		printf("-bash: cd: too many arguments\n");
	}
}
