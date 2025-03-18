/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 21:43:03 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	ft_isdigit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	minishell_exit(t_data *meta, t_cmd_list *exec_cmd, int **pipes)
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
		if (ft_isdigit_string(exec_cmd->str[1]) == 0)
		{
			builtin_error(exec_cmd->str[1], 12);
			free_meta_token(meta);
			exit(g_ws);
		}
		exit_no = ft_atoi(exec_cmd->str[1]);
		free_meta_token(meta);
		exit(exit_no);
	}
	free_meta_token(meta);
	exit (0);
}
