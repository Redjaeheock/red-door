/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/19 15:10:20 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_exit(t_data *meta, t_cmd_list *exec_cmd, int **pipes)
{
	int	exit_len;

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
		if (parsing_digit_longlong_max(exec_cmd->str[1]) == 0)
		{
			builtin_error(exec_cmd->str[1], 12);
			free_meta_token(meta);
			exit(g_ws);
		}
		free_meta_token(meta);
		exit(g_ws);
	}
	free_meta_token(meta);
	exit (0);
}
