/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:29 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 20:53:10 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"

void	free_resources(t_data *meta, int **pipes, char *path, int exit_n)
{
	if (path != NULL)
		free(path);
	if (pipes != NULL)
		close_pipes(pipes);
	if (meta != NULL)
	{
		reset_file_descriptor(meta);
		free_meta_token(meta);
	}
	if (-1 < exit_n)
	{
		g_ws = exit_n;
		exit(exit_n);
	}
}

int	rutin_free(t_data *meta, char *str)
{
	if (meta->exec_cmd)
	{
		//printf_exec_commads(meta->exec_cmd);
		free_exec_linked_list(meta->exec_cmd);
		meta->exec_cmd = NULL;
	}
	meta->tokens = free_t_list(meta->tokens);
	add_history_and_free(&str);
	return (0);
}
