/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/15 10:24:19 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_exit(t_data *meta, t_cmd_list *exec_cmd)
{
	int	exit_len;
	int	exit_no;
	
	g_ws = 0;
	printf("exit\n");
	exit_len = sndry_arr_len((void **)exec_cmd->str);
	if (exit_len > 2)
	{
		builtin_error(NULL, 11);
		return ;
	}
	else if (exit_len == 2)
	{
		if (check_option(exec_cmd->str[1]) == 1)
			builtin_error(exec_cmd->str[1], 12);
		exit_no = atoi(exec_cmd->str[1]);
		free_meta_token(meta);
		exit(exit_no);
	}
	free_meta_token(meta);
	exit (0);
}
