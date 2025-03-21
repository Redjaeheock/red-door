/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:29 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 15:46:46 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_resources(t_data *meta, int **pipes, char *path)
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
}
