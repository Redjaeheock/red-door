/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:29 by jahong            #+#    #+#             */
/*   Updated: 2025/03/18 16:44:23 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
